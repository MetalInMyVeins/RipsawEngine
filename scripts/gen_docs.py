#!/usr/bin/env python3

# This script is AI generated. It has no relation to the engine
# or game code. It just works as a documentation parser to
# automatically inject them in README.md which saves a lot of
# time.

import os
import xml.etree.ElementTree as ET
import re
import subprocess

XML_DIR = "docs/xml"
TEMPLATE_MD = "README.template.md"
FINAL_MD = "README.md"

# ------------------------------------------------------------
# Helpers
# ------------------------------------------------------------

def remove_parameterlists(node):
    if node is None:
        return
    for pl in node.findall(".//parameterlist"):
        for child in list(pl):
            pl.remove(child)

def extract_text(node):
    if node is None:
        return ""
    return " ".join(t.strip() for t in node.itertext()).strip()


# ------------------------------------------------------------
# Parameter parsing
# ------------------------------------------------------------

def parse_parameters(member):
    params = []

    # Phase 1 — names & types
    for p in member.findall("param"):
        p_type = extract_text(p.find("type"))
        p_name = extract_text(p.find("declname"))
        if not p_name:
            continue
        params.append({"name": p_name, "type": p_type, "desc": ""})

    # Phase 2 — descriptions
    detailed = member.find("detaileddescription")
    if detailed is not None:
        plist = detailed.find(".//parameterlist[@kind='param']")
        if plist is not None:
            for pitem in plist.findall("parameteritem"):
                names = pitem.find("parameternamelist")
                desc_node = pitem.find("parameterdescription")

                if names is None or desc_node is None:
                    continue

                pname = extract_text(names.find("parametername"))

                # Prefer para children for a clean parameter description.
                paras = desc_node.findall("para")
                if paras:
                    pdesc = " ".join(extract_text(p) for p in paras)
                else:
                    # Remove any simplesect content (e.g. warning/note) before extracting.
                    for s in desc_node.findall(".//simplesect"):
                        # clear its children and text to avoid including them
                        for child in list(s):
                            s.remove(child)
                        s.text = ""
                    pdesc = extract_text(desc_node)

                # assign to matching parameter
                for existing in params:
                    if existing["name"] == pname:
                        existing["desc"] = pdesc

    return params


# ------------------------------------------------------------
# Member parsing
# ------------------------------------------------------------

def parse_member(member):
    kind = member.attrib.get("kind")
    name = extract_text(member.find("name"))
    definition = extract_text(member.find("definition"))
    brief = extract_text(member.find("briefdescription"))
    detailed_node = member.find("detaileddescription")
    params = parse_parameters(member)
    remove_parameterlists(detailed_node)

    detailed = ""
    return_desc = ""

    if detailed_node is not None:
        # return description
        ret_nodes = detailed_node.findall(".//simplesect[@kind='return']")
        if ret_nodes:
            return_desc = " ".join(extract_text(r) for r in ret_nodes)
            for r in ret_nodes:
                for child in list(r):
                    r.remove(child)
        # For the remaining detailed text, remove any simplesect that represent "warning"/"note"
        for s in detailed_node.findall(".//simplesect"):
            # keep simplesect structure but clear children/text so they don't pollute main detailed text
            for child in list(s):
                s.remove(child)
            s.text = ""
        detailed = extract_text(detailed_node)

    ret_type = extract_text(member.find("type"))

    return {
        "kind": kind,
        "name": name,
        "definition": definition,
        "brief": brief,
        "detailed": detailed,
        "params": params,
        "return": return_desc,
        "return_type": ret_type,
    }


# ------------------------------------------------------------
# Class parsing (now including base classes)
# ------------------------------------------------------------

def parse_class(xml_file):
    tree = ET.parse(xml_file)
    root = tree.getroot()

    comp = root.find("compounddef")
    cname = extract_text(comp.find("compoundname"))

    # NEW: extract base classes
    bases = []
    for b in comp.findall("basecompoundref"):
        bases.append(extract_text(b))

    methods = []
    variables = []

    for section in comp.findall("sectiondef"):
        kind = section.attrib.get("kind")
        for member in section.findall("memberdef"):
            data = parse_member(member)
            if kind in ("public-func", "protected-func", "private-func"):
                methods.append(data)
            elif kind.endswith("attrib"):
                variables.append(data)

    return cname, bases, methods, variables


# ------------------------------------------------------------
# Inheritance-aware ordering
# ------------------------------------------------------------

def topo_sort_classes(classes):
    name_to_tuple = {c[0]: c for c in classes}
    bases_map = {c[0]: [b for b in c[1] if b in name_to_tuple] for c in classes}

    children = {name: [] for name in name_to_tuple}
    for name, base_list in bases_map.items():
        for b in base_list:
            children[b].append(name)

    # Deterministic: sort child lists in the order we want (alphabetical)
    for k in children:
        children[k].sort()

    roots = [name for name, bs in bases_map.items() if not bs]
    roots.sort()

    visited = set()
    order = []

    def dfs(node):
        if node in visited:
            return
        visited.add(node)
        order.append(node)            # append parent before children
        for child in children.get(node, []):
            dfs(child)

    for r in roots:
        dfs(r)

    # include any remaining (external bases or cycles), deterministically
    for name in sorted(name_to_tuple.keys()):
        if name not in visited:
            dfs(name)

    return [name_to_tuple[n] for n in order]


# --------------------------
# Directory Layout
# --------------------------

def read_gitignore(path=".gitignore"):
    """Return a list of patterns from .gitignore suitable for tree -I."""
    if not os.path.exists(path):
        return []

    patterns = []
    with open(path, "r") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            # tree uses patterns like "dir1|dir2|*.o"
            patterns.append(line)
    return patterns

def generate_tree_output(ignore_patterns):
    """Run tree with ignore patterns and return its output as text."""
    if ignore_patterns:
        pattern = "|".join(ignore_patterns)
        cmd = ["tree", "-I", pattern]
    else:
        cmd = ["tree"]

    try:
        output = subprocess.check_output(cmd, text=True)
    except FileNotFoundError:
        output = "tree command not found."
    return output


# ------------------------------------------------------------
# Markdown writer
# ------------------------------------------------------------

def write_markdown(classes, out_file=None):
    f = out_file
    for cname, bases, methods, variables in classes:
        f.write(f"## {cname}\n\n")

        # Variables
        if variables:
            f.write("### Member Variables\n\n")
            for v in variables:
                name = v["name"]
                typ  = v["definition"].replace(name, "").strip()
                definition = v["definition"]
                name = v["name"]

                if typ.startswith(name):
                    typ = ""
                typ = typ or v.get("type", "")

                m = re.match(r"(.*?)(?:\w+::)*" + re.escape(name) + r"$", definition)
                if m:
                    typ = m.group(1).strip()
                else:
                    typ = definition.replace(name, "").strip()

                brief = v["brief"] or ""
                detailed_v = v.get("detailed", "") or ""

                # Write brief on the list line
                if typ:
                    f.write(f"- `{typ}` `{name}`: {brief}\n")
                else:
                    f.write(f"- `{name}`: {brief}\n")

                # If there is a detailed description for the variable (@details), print it just below
                if detailed_v and detailed_v != brief:
                    # small visual separation, make it a normal paragraph indented two spaces
                    f.write(f"  \n  {detailed_v}\n")
            f.write("\n")

        # Methods
        if methods:
            f.write("### Member Functions\n\n")
            for m in methods:
                f.write(f"#### `{m['definition']}`\n\n")

                if m["brief"]:
                    f.write(f"{m['brief']}\n\n")
                if m["detailed"]:
                    f.write(f"{m['detailed']}\n\n")

                if m["params"]:
                    f.write("#### Parameters\n\n")
                    f.write("| Name | Type | Description |\n")
                    f.write("|------|------|-------------|\n")
                    for p in m["params"]:
                        desc = p["desc"] or ""
                        f.write(f"| `{p['name']}` | `{p['type']}` | {desc} |\n")
                    f.write("\n")

                if m.get("return"):
                    f.write("#### Return\n\n")
                    f.write("| Type | Description |\n")
                    f.write("|--------|-------------|\n")
                    f.write(f"| {m['return_type']} | {m['return']} |\n\n")

        f.write("\n---\n\n")


# ------------------------------------------------------------
# Template injection
# ------------------------------------------------------------

def inject_markdown_into_template(generated_md):
    with open(TEMPLATE_MD, "r") as f:
        content = f.read()

    new_content = re.sub(
        r"<!-- AUTODOC:BEGIN -->.*?<!-- AUTODOC:END -->",
        f"<!-- AUTODOC:BEGIN -->\n\n{generated_md}\n<!-- AUTODOC:END -->",
        content,
        flags=re.DOTALL
    )

    with open(FINAL_MD, "w") as f:
        f.write(new_content)



def inject_two_blocks(tree_md, api_md):
    with open(TEMPLATE_MD, "r") as f:
        content = f.read()

    # Find both AUTODOC blocks with their spans
    pattern = r"<!-- AUTODOC:BEGIN -->.*?<!-- AUTODOC:END -->"
    matches = list(re.finditer(pattern, content, flags=re.DOTALL))

    if len(matches) != 2:
        raise RuntimeError("Expected exactly two AUTODOC blocks")

    # Inject contents in-place by slicing the string
    result = []
    last_end = 0

    # First block → directory layout
    m0 = matches[0]
    result.append(content[last_end:m0.start()])
    result.append(
        f"<!-- AUTODOC:BEGIN -->\n\n```\n{tree_md}\n```\n\n<!-- AUTODOC:END -->"
    )
    last_end = m0.end()

    # Second block → API docs
    m1 = matches[1]
    result.append(content[last_end:m1.start()])
    result.append(
        f"<!-- AUTODOC:BEGIN -->\n\n{api_md}\n<!-- AUTODOC:END -->"
    )
    last_end = m1.end()

    # Tail of the file
    result.append(content[last_end:])

    # Write final README
    with open(FINAL_MD, "w") as f:
        f.write("".join(result))



# ------------------------------------------------------------
# Main
# ------------------------------------------------------------

def main():
    print("Running Doxygen...")
    subprocess.run(["doxygen", "Doxyfile"], check=True)

    classes = []
    for file in os.listdir(XML_DIR):
        if file.startswith("class") and file.endswith(".xml"):
            cname, bases, methods, variables = parse_class(os.path.join(XML_DIR, file))
            classes.append((cname, bases, methods, variables))

    classes = topo_sort_classes(classes)

    from io import StringIO
    buffer = StringIO()
    write_markdown(classes, out_file=buffer)
    api_md = buffer.getvalue()

    # ---------------------------
    # DIRECTORY TREE GENERATION
    # ---------------------------
    ignore_patterns = read_gitignore()
    tree_output = generate_tree_output(ignore_patterns)

    # ---------------------------
    # FINAL INJECTION
    # ---------------------------
    inject_two_blocks(tree_output, api_md)

if __name__ == "__main__":
    main()


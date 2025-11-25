#!/usr/bin/env python3
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
    return "".join(node.itertext()).strip()


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
                pdesc = extract_text(desc_node)

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
    """
    Return classes sorted so that each base appears before its derived classes,
    and all derived classes appear immediately after their base (grouped).
    Deterministic: children lists are visited in alphabetical order.
    
    Input: classes: list of tuples (name, bases, methods, variables)
    Output: list of the same tuples in desired order
    """
    # Map name -> tuple and name -> bases
    name_to_tuple = {c[0]: c for c in classes}
    bases_map = {c[0]: [b for b in c[1] if b in name_to_tuple] for c in classes}  # only in-set bases

    # Build children map: base -> set of derived
    children = {name: set() for name in name_to_tuple}
    for name, base_list in bases_map.items():
        for b in base_list:
            children[b].add(name)

    # Find roots: classes that do not have any in-set bases
    roots = [name for name, bs in bases_map.items() if not bs]

    # To be deterministic, sort roots and children lists
    roots.sort()

    visited = set()
    order = []

    def dfs(node):
        if node in visited:
            return
        visited.add(node)
        # Append node now so parent appears before children
        order.append(node)
        # Visit children in sorted order so grouping/order is deterministic
        for child in sorted(children.get(node, [])):
            dfs(child)

    # Start DFS from each root (sorted)
    for r in roots:
        dfs(r)

    # There may be classes not reachable from any root (cycles or all bases are external).
    # Ensure we still include them deterministically:
    for name in sorted(name_to_tuple.keys()):
        if name not in visited:
            dfs(name)

    # Return the full tuples in the computed order
    return [name_to_tuple[n] for n in order]


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

                brief = v["brief"] or v["detailed"]

                if typ:
                    f.write(f"- `{typ}` `{name}`: {brief}\n")
                else:
                    f.write(f"- `{name}`: {brief}\n")
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

    # Replace AUTODOC block exactly
    new_content = re.sub(
        r"<!-- AUTODOC:BEGIN -->.*?<!-- AUTODOC:END -->",
        f"<!-- AUTODOC:BEGIN -->\n\n{generated_md}\n<!-- AUTODOC:END -->",
        content,
        flags=re.DOTALL
    )

    with open(FINAL_MD, "w") as f:
        f.write(new_content)


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

    # NEW: inheritance-aware sorting
    classes = topo_sort_classes(classes)

    # Generate markdown into buffer
    from io import StringIO
    buffer = StringIO()
    write_markdown(classes, out_file=buffer)
    generated_md = buffer.getvalue()

    inject_markdown_into_template(generated_md)


if __name__ == "__main__":
    main()

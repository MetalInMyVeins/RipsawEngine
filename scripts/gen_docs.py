#!/usr/bin/env python3
import os
import xml.etree.ElementTree as ET
import re
import subprocess

XML_DIR = "docs/xml"
TEMPLATE_MD = "README.template.md"
FINAL_MD = "README.md"

def remove_parameterlists(node):
    """Remove all <parameterlist> blocks so they don't leak into detailed text."""
    if node is None:
        return
    for pl in node.findall(".//parameterlist"):
        parent = pl.getparent() if hasattr(pl, "getparent") else None
        if parent is not None:
            parent.remove(pl)
        else:
            # fallback for xml.etree.ElementTree (no parent)
            for p in node.findall(".//parameterlist"):
                p.clear()

def extract_text(node):
    if node is None:
        return ""
    return "".join(node.itertext()).strip()


def parse_parameters(member):
    """
    Extract parameters in two phases:
    1. Extract names & types from <param> nodes.
    2. Extract descriptions from <detaileddescription> <parameterlist>.
    """
    params = []

    # Phase 1 — names & types
    for p in member.findall("param"):
        p_type = extract_text(p.find("type"))
        p_name = extract_text(p.find("declname"))
        if not p_name:
            continue  # skip unnamed parameters
        params.append({"name": p_name, "type": p_type, "desc": ""})

    # Phase 2 — detailed descriptions
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

                # assign to matching parameter
                for existing in params:
                    if existing["name"] == pname:
                        existing["desc"] = pdesc

    return params


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
        # Extract return description
        ret_nodes = detailed_node.findall(".//simplesect[@kind='return']")
        if ret_nodes:
            return_desc = " ".join(extract_text(r) for r in ret_nodes)
            # Clear the return nodes so they don't appear in detailed
            for r in ret_nodes:
                for child in list(r):
                    r.remove(child)

        detailed = extract_text(detailed_node)
    # Extract return type
    ret_type = extract_text(member.find("type"))  # <type> contains the return type
    
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


def parse_class(xml_file):
    tree = ET.parse(xml_file)
    root = tree.getroot()

    comp = root.find("compounddef")
    cname = extract_text(comp.find("compoundname"))

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

    return cname, methods, variables


def write_markdown(classes, out_file=None):
    f = out_file or open(OUT_MD, "w")
    close_file = out_file is None
    for cname, methods, variables in classes:
        f.write(f"## {cname}\n\n")

        # Variables
        if variables:
            f.write("### Member Variables\n\n")
            for v in variables:
                name = v["name"]
                typ  = v["definition"].replace(name, "").strip()  # fallback if needed
                brief = v["brief"] or v["detailed"]
                definition = v["definition"]  # e.g., "int Engine::mScreenWidth"
                name = v["name"]

                # clean type (remove class prefixes, compress spaces)
                if typ.startswith(name):
                    typ = ""
                typ = typ or v.get("type", "")
                # regex to remove class prefixes
                # matches optional words + :: before the variable name
                m = re.match(r"(.*?)(?:\w+::)*" + re.escape(name) + r"$", definition)
                if m:
                    typ = m.group(1).strip()  # this is just the type part
                else:
                    typ = definition.replace(name, "").strip()

                brief = v["brief"] or v["detailed"]
                
                if typ:
                    f.write(f"- `{typ}`  `{name}`: {brief}\n")
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

                # parameters
                if m["params"]:
                    f.write("#### Parameters\n\n")
                    f.write("| Name | Type | Description |\n")
                    f.write("|------|------|-------------|\n")

                    for p in m["params"]:
                        desc = p["desc"] or ""
                        name = p["name"]
                        typ  = p["type"]
                        f.write(f"| `{name}` | `{typ}` | {desc} |\n")

                    f.write("\n")

                # standalone return table
                if m.get("return"):
                    f.write("#### Return\n\n")
                    f.write("| Type | Description |\n")
                    f.write("|--------|-------------|\n")
                    f.write(f"| {m['return_type']} | {m['return']} |\n\n")

        f.write("\n---\n\n")


def inject_markdown_into_template(generated_md):
    """Replace AUTODOC block in template with generated markdown."""
    with open(TEMPLATE_MD, "r") as f:
        content = f.read()

    # regex to replace everything between AUTODOC markers
    new_content = re.sub(
        r"(<!-- AUTODOC:BEGIN -->).*?(<!-- AUTODOC:END -->)",
        rf"\1\n\n{generated_md}\n\2",
        content,
        flags=re.DOTALL
    )

    with open(FINAL_MD, "w") as f:
        f.write(new_content)

def main():
    print("Running Doxygen...")
    subprocess.run(["doxygen", "Doxyfile"], check=True)
    classes = []
    for file in os.listdir(XML_DIR):
        if file.startswith("class") and file.endswith(".xml"):
            cname, methods, variables = parse_class(os.path.join(XML_DIR, file))
            classes.append((cname, methods, variables))

    # generate markdown into a string
    from io import StringIO
    buffer = StringIO()
    write_markdown(classes, out_file=buffer)
    generated_md = buffer.getvalue()

    # inject into template
    inject_markdown_into_template(generated_md)

if __name__ == "__main__":
    main()


# export_clean_xrefs.py
# Usage in IDA Python console:
#   import export_clean_xrefs
#   export_clean_xrefs.export_xrefs_pseudocode('YourFuncName', max_depth=3)

import os
import idautils
import idaapi
import ida_funcs
import ida_hexrays
import ida_lines

def export_path(path, outdir, counter):
    """
    Write a .c file containing clean pseudocode for a call-path.
    """
    # Derive filename key from function names
    names = [nm for nm, _, _ in path]
    key = "_".join(names)
    count = counter.get(key, 0) + 1
    counter[key] = count
    fname = f"{key}{'' if count==1 else f'_{count}'}.c"
    os.makedirs(outdir, exist_ok=True)
    full = os.path.join(outdir, fname)

    with open(full, "w") as f:
        f.write(f"/* Call path: {' <- '.join(names)} */\n\n")
        for nm, ea, cfunc in path:
            f.write(f"/* ===== Function: {nm} @ {ea:#x} ===== */\n")
            # Clean each simpleline_t via tag_remove
            for sl in cfunc.get_pseudocode():
                clean = ida_lines.tag_remove(sl.line)
                f.write(clean.rstrip() + "\n")
            f.write("\n")
    print(f"[+] Exported {full}")

def recurse(func_ea, path, visited, outdir, max_depth, counter, depth=0):
    # Stop on depth or cycle
    if depth > max_depth or func_ea in visited:
        export_path(path, outdir, counter)
        return

    visited.add(func_ea)
    func = ida_funcs.get_func(func_ea)
    if not func:
        export_path(path, outdir, counter)
        return

    try:
        cfunc = ida_hexrays.decompile(func)
    except ida_hexrays.DecompilationFailure:
        export_path(path, outdir, counter)
        return

    name = ida_funcs.get_func_name(func_ea)
    new_path = path + [(name, func_ea, cfunc)]

    # Gather unique caller-function EAs
    callers = {}
    for xr in idautils.XrefsTo(func_ea, flags=0):
        cf = ida_funcs.get_func(xr.frm)
        if cf:
            callers[cf.start_ea] = cf

    if not callers:
        export_path(new_path, outdir, counter)
    else:
        for ea in callers:
            recurse(ea, new_path, set(visited), outdir, max_depth, counter, depth+1)

def export_xrefs_pseudocode(root_name, max_depth=3):
    """
    Entry: root function name and recursion max depth.
    """
    root = idaapi.get_name_ea(idaapi.BADADDR, root_name)
    if root == idaapi.BADADDR:
        print(f"[-] Function '{root_name}' not found!")
        return
    outdir = os.path.join(idaapi.get_user_idadir(), "xref_exports")
    recurse(root, [], set(), outdir, max_depth, {})
    print(f"[*] Done exporting call-paths for '{root_name}'")

# Usage: in IDA Python console:
#   import export_each_func
#   export_each_func.export_xrefs_pseudocode('YourRootFunc', max_depth=3)

import os
import idautils
import idaapi
import ida_funcs
import ida_hexrays
import ida_lines

def export_func(name, ea, cfunc, depth, outdir):
    """
    Write a single function's pseudocode to its own .c file.
    Prefix filename with depth to preserve call order.
    """
    # Depth prefix as two digits
    prefix = f"{depth:02d}"
    fname = f"{prefix}_{name}_{ea:08x}.c"
    os.makedirs(outdir, exist_ok=True)
    path = os.path.join(outdir, fname)

    with open(path, "w") as f:
        f.write(f"/* Function: {name} @ {ea:#x} (call depth {depth}) */\n\n")
        for simple in cfunc.get_pseudocode():
            clean_line = ida_lines.tag_remove(simple.line)
            f.write(clean_line.rstrip() + "\n")
    print(f"[+] Exported {path}")

def recurse(func_ea, depth, visited, outdir, max_depth):
    """
    Recursively walk callers up to max_depth, export each function individually.
    """
    if depth > max_depth or func_ea in visited:
        return
    visited.add(func_ea)

    func = ida_funcs.get_func(func_ea)
    if not func:
        return

    try:
        cfunc = ida_hexrays.decompile(func)
    except ida_hexrays.DecompilationFailure:
        return

    name = ida_funcs.get_func_name(func_ea)
    # Export this function at current depth
    export_func(name, func_ea, cfunc, depth, outdir)

    # Recurse into unique caller functions
    callers = {}
    for xr in idautils.XrefsTo(func_ea, flags=0):
        cf = ida_funcs.get_func(xr.frm)
        if cf:
            callers[cf.start_ea] = cf

    for caller_ea in callers:
        recurse(caller_ea, depth + 1, visited, outdir, max_depth)

def export_xrefs_pseudocode(root_name, max_depth=3):
    """
    Entry point: specify the root function and max recursion depth.
    """
    root_ea = idaapi.get_name_ea(idaapi.BADADDR, root_name)
    if root_ea == idaapi.BADADDR:
        print(f"[-] Function '{root_name}' not found!") 
        return

    outdir = os.path.join(idaapi.get_user_idadir(), "xref_func_exports")
    recurse(root_ea, depth=0, visited=set(), outdir=outdir, max_depth=max_depth)
    print(f"[*] Done exporting functions from '{root_name}'")

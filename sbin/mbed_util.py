import re, glob, sys, os

def parse_include_libs(include_libs):
    ext_o = []
    ext_i = []
    for lib_path in include_libs:
        ext_i.append("-I" + lib_path)
        r = re.compile(".*[\\/]([^\\/]+)\.\w+")
        files_h = glob.glob(os.path.realpath(lib_path + "/*.h"))
        files_cpp = glob.glob(os.path.realpath(lib_path + "/*.cpp"))
        files_c = glob.glob(os.path.realpath(lib_path + "/*.c"))
        files_o_h = []
        files_o_cpp = []
        files_o_c = []
        for f_path in files_h:
            m = r.match(f_path)
            if not m: continue
            o_name = m.group(1)
            files_o_h.append(o_name)
        for f_path in files_cpp:
            m = r.match(f_path)
            if not m: continue
            o_name = m.group(1)
            if o_name in files_o_h: files_o_cpp.append(o_name)
        for f_path in files_c:
            m = r.match(f_path)
            if not m: continue
            o_name = m.group(1)
            files_o_c.append(o_name)
        files_o = files_o_c + files_o_cpp
        ext_o = [os.path.realpath(lib_path + "/" + file_o_name + ".o") for file_o_name in files_o]
    return (ext_i, ext_o)






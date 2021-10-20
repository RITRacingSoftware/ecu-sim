import SCons
from pathlib import Path

REPO_ROOT_DIR = Dir(".")

"""
SCons entry point for ecusim project.

This file contains instructions, in python, for SCons to build all targets in this project.
"""
to_return = {}

SRC_DIR = REPO_ROOT_DIR.Dir('src')
EXAMPLES_DIR = SRC_DIR.Dir('examples')
MODULES_DIR = SRC_DIR.Dir('modules')

module_src_files = []
example_src_files = []
src_dirs = [EXAMPLES_DIR, MODULES_DIR, SRC_DIR]
to_return['src_dirs'] = src_dirs
# module_src_files.extend(Glob(Path(SRC_DIR.abspath) / "*.cpp"))

# get a list of all source modules and locations
# for directory in (d for d in Path(str(MODULES_DIR)).iterdir() if d.is_dir()):
#     module = REPO_ROOT_DIR.Dir(str(directory))
#     src_dirs.append(module)
#     module_src_files.extend(Glob(Path(module.abspath) / "*.cpp"))

module_src_files.extend(Glob(Path(MODULES_DIR.abspath) / "*.cpp"))
example_src_files.extend(Glob(Path(EXAMPLES_DIR.abspath) / "*.cpp"))

# for directory in (d for d in Path(str(EXAMPLES_DIR)).iterdir() if d.is_dir()):
#     module = REPO_ROOT_DIR.Dir(str(directory))
#     src_dirs.append(module)
#     example_src_files.extend(Glob(Path(module.abspath) / "*.cpp"))



cpp_env = Environment(
    CC='g++',
    CPPPATH=src_dirs,
    CCFLAGS=["-ggdb", "-fPIC"]
)

# build C++ library wrapper (BlfWriter) and c++ library (vector_blf)

vector_blf_so = File('/usr/local/lib/libVector_BLF.so.2')

vector_blf_lib = Command(
    [vector_blf_so],
    [],
    [f"cd {REPO_ROOT_DIR.abspath}/libs/vector_blf && mkdir -p build && cd build && cmake .. && make && make install DESTDIR=.. && make install && /usr/sbin/ldconfig"]
)

# blf_o = cpp_env.SharedObject(MODULES_DIR.File('BlfWriter.cpp'))
# Depends(blf_o, vector_blf_so)

# janky
# cpp_env['STATIC_AND_SHARED_OBJECTS_ARE_THE_SAME']=1

# build the library

"""
Instructions for building ecusim modules.
"""

ecusim_objs = []

for src_file in module_src_files + example_src_files:
    ecusim_objs.append(cpp_env.Object(src_file))

to_return['ecusim_objs'] = ecusim_objs
to_return['blf_lib'] = vector_blf_so

"""
Instructions for building ecusim test program.
"""

# build example and test main objects
test_prog_objs = []
test_prog_objs.extend(ecusim_objs)
for src_file in example_src_files:
    test_prog_objs.append(cpp_env.Object(src_file))

test_prog_objs.append(cpp_env.Object(SRC_DIR.File('test_main.cpp')))

test_prog = cpp_env.Program("test-prog", test_prog_objs)

Alias('test-prog', test_prog)

Return('to_return')
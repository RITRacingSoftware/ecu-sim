import SCons
from pathlib import Path

REPO_ROOT_DIR = Dir(".")

"""
SCons entry point for ecusim project.

This file contains instructions, in python, for SCons to build all targets in this project.
"""

SRC_DIR = REPO_ROOT_DIR.Dir('src')

src_files = []
src_dirs = [SRC_DIR]

src_files.extend(Glob(Path(SRC_DIR.abspath) / "*.cpp"))

# get a list of all source modules and locations
for directory in (d for d in Path(str(SRC_DIR)).iterdir() if d.is_dir()):
    module = REPO_ROOT_DIR.Dir(str(directory))
    src_dirs.append(module)
    src_files.extend(Glob(Path(module.abspath) / "*.cpp"))

cpp_env = Environment(
    CC='g++',
    CPPPATH=src_dirs,
    CCFLAGS=["-ggdb"]
)


"""
Instructions for building ecusim modules.
"""

obj_files = []

for src_file in src_files:
    print(src_file)
    obj_files.append(cpp_env.Object(src_file))

Alias('objs', obj_files)

"""
Instructions for building ecusim test program.
"""

test_prog = cpp_env.Program("test-prog", obj_files)

Alias('test-prog', test_prog)



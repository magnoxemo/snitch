import argparse
import os

_parser = argparse.ArgumentParser()
_parser.add_argument("--cpp", help = " name of the cpp src file ")
_parser.add_argument("--exe", help = " name of the cpp exe file ")
_parser.add_argument("--rebuild", help = "If the program needs to be rebuild",default = True)
_parser.add_argument("--dbg",help = " Debugger mode",default = False)

_libmesh_include_path = "/home/ebny_walid/libmesh_opt/include"
_libmesh_link_path = "/home/ebny_walid/libmesh_opt/lib"
_eigen_path ="/usr/include/eigen3"
_snitch_include_path = "/home/ebny_walid/Documents/github/snitch/include"
_snitch_src_path = "/home/ebny_walid/Documents/github/snitch/src"
_args = _parser.parse_args()

if _args.dbg:
    _run_command = (
        f"mpicxx {_args.cpp} -g -oo -o {_args.exe} "
        f"-I{_libmesh_include_path} "
        f"-I{_eigen_path} "
        f"-I{_snitch_include_path} "
        f"-Wl,-rpath,{_libmesh_link_path} "
        f"{_snitch_src_path}/*.cpp "
        f"-L{_libmesh_link_path} "
        f"-lmesh_opt -ltimpi_opt -lnglib -lngcore -lz -ltirpc "
        f"-O2 -felide-constructors -fstrict-aliasing -Wdisabled-optimization "
        f"-funroll-loops -ftrapping-math -fopenmp"
    )

    _executable_command = "gdb ./" +_args.exe
else:
    _run_command = (
        f"mpicxx {_args.cpp} -o {_args.exe} "
        f"-I{_libmesh_include_path} "
        f"-I{_eigen_path} "
        f"-I{_snitch_include_path} "
        f"-Wl,-rpath,{_libmesh_link_path} "
        f"{_snitch_src_path}/*.cpp "
        f"-L{_libmesh_link_path} "
        f"-lmesh_opt -ltimpi_opt -lnglib -lngcore -lz -ltirpc "
        f"-O2 -felide-constructors -fstrict-aliasing -Wdisabled-optimization "
        f"-funroll-loops -ftrapping-math -fopenmp"
    )

    _executable_command = "./" +_args.exe
if os.path.exists(_args.exe) and _args.rebuild :

    print("===================================================")
    print("=== removing existing executable and rebuilding ===")
    print("===================================================")
    os.system(f"rm {_args.exe}")
    os.system(_run_command)
    if os.path.exists(_args.exe):
        print(f"running the new {_args.exe}")
        os.system(_executable_command)
    else:
        raise Exception (f"\n\n\n{_args.cpp} file didn't compile. See the compile message and fix them.")
else:
    if os.path.exists(_args.exe):
        os.system(_executable_command)
    else:
        print( "===================================================")
        print(f"===== {_args.exe} doesn't exists so building it  =======")
        print( "===================================================")
        os.system(_run_command)
        if os.path.exists(_args.exe):
            print(f"running the new {_args.exe}")
            os.system(_executable_command)
        else:
            raise Exception (f"\n\n\n{_args.cpp} file didn't compile. See the compile message and fix them.")

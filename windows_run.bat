cl windows_int_vs_uint.c /O2 -D BASE && windows_int_vs_uint.exe > WINDOWS_BASE.txt
cl windows_int_vs_uint.c /O2 -D NODIV && windows_int_vs_uint.exe > WINDOWS_NODIV.txt
cl windows_int_vs_uint.c /O2 -D NODIVMULT && windows_int_vs_uint.exe > WINDOWS_NODIVMULT.txt

del windows_int_vs_uint.exe
del windows_int_vs_uint.obj
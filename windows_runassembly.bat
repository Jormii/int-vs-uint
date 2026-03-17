cl windows_int_vs_uint.c /O2 /c /Fa"windows_int_vs_uint-BASE.asm" /FAs -D BASE
cl windows_int_vs_uint.c /O2 /c /Fa"windows_int_vs_uint-NODIV.asm" /FAs -D NODIV
cl windows_int_vs_uint.c /O2 /c /Fa"windows_int_vs_uint-NODIVMULT.asm" /FAs -D NODIVMULT

del windows_int_vs_uint.obj
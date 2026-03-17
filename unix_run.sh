gcc unix_int_vs_uint.c -O2 -Wall -Wextra -Wpedantic -D BASE && ./a.out > UNIX_BASE.txt
gcc unix_int_vs_uint.c -O2 -Wall -Wextra -Wpedantic -D NODIV && ./a.out > UNIX_NODIV.txt
gcc unix_int_vs_uint.c -O2 -Wall -Wextra -Wpedantic -D NODIVMULT && ./a.out > UNIX_NODIVMULT.txt

rm ./a.out

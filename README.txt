gcc -std=c11 -static-libgcc -static-libstdc++ -lrt -O3 passwordgen.c
clang -std=c11 -static-libgcc -lrt -O3 -D_FORTIFY_SOURCE=2 passwordgen.c

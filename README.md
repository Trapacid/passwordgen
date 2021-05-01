# passwordgen
### A password generator written in C that _should_ be compatible on Windows, macOS, and Linux.
<sup>and only works on 64 bit due to 64 bit unsigned integers used.</sup>


# Seed Calculation
This is _not_ meant to be a secure generator because:
1. This relies on UNIX epoch.
2. This uses the amount of CPU threads you have.
3. And the seed you enter.

However if you're interested, here it is in a formula:
```
SEED = (UNIX_EPOCH_NANOSECONDS * CPU_THREADS % UNIX_EPOCH_SECONDS) * USER_INPUT_SEED 
```
- `*` - multiplication
- `%` - modulus (remainder of)

If you're on Windows (for now), your seed is calculated as:
```
SEED = (CPU_THREADS % 69420) * USER_INPUT_SEED
```

# Compiling
```
gcc -std=c17 -static-libgcc -static-libstdc++ -lrt -O3 passwordgen.c

clang -std=c17 -static-libgcc -lrt -O3 -D_FORTIFY_SOURCE=2 passwordgen.c
```
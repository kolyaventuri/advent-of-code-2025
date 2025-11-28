# Reports

Reports of each day run three commands:

1. `NodeJS child_process#spawn and performance.now()`
    - Measures execution speed
2. `/usr/bin/time -l ./out/{PROG}`
    - Measures the total memory usage.
3. `leaks --atExit --list -- ./out/{PROG}`
    - Bsaic memory leak check

Memory + execution speed baseline available in [0_baseline.md](0_baseline.md), for the following program:
```c
int main(void) {
  return 0;
}
```

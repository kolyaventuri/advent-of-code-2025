# Report for day0

## Performance over 5 runs, measured via node spawn + `performance.now()`
- **Average**: 10.71ms

## Memory over 5 runs, measured by `time -l ./out/day0`
- **Peak**: 1.66 MB

## Leak Report measured by `leaks --atExit --list -- ./out/day0`
```
leaks Report Version: 3.0
Process 73059: 169 nodes malloced for 16 KB
Process 73059: 0 leaks for 0 total leaked bytes.
```


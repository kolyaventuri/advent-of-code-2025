_This report automatically generated via `make report FILE=0_baseline`_

# Report for 0_baseline

## Performance over 5 runs, measured via node spawn + `performance.now()`
- **Average**: 7.80ms

## Memory over 5 runs, measured by `time -l ./out/0_baseline`
- **Peak**: 1.05 MB

## Leak Report measured by `leaks --atExit --list -- ./out/0_baseline`
```
leaks Report Version: 3.0
Process 73496: 168 nodes malloced for 8 KB
Process 73496: 0 leaks for 0 total leaked bytes.
```


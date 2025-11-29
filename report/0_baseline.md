_This report automatically generated via `make report FILE=0_baseline`_

# Report for 0_baseline

## Performance over 5 runs, measured via node spawn + `performance.now()`
- **Average**: 7.65ms

## Memory over 5 runs, measured by `time -l ./out/0_baseline`
- **Peak**: 1,070.81 KB

## Leak Report measured by `leaks --atExit --list -- ./out/0_baseline`
```
leaks Report Version: 3.0
Process 76794: 168 nodes malloced for 8 KB
Process 76794: 0 leaks for 0 total leaked bytes.
```


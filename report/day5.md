_This report automatically generated via `make report FILE=day5`_

# Report for day5

## Performance over 5 runs, measured via node spawn + `performance.now()`
- **Average**: 7.48ms

## Memory over 5 runs, measured by `time -l ./out/day5`
- **Peak**: 1,129.33 KB

## Leak Report measured by `leaks --atExit --list -- ./out/day5`
```
leaks Report Version: 3.0
Process 32984: 269 nodes malloced for 19 KB
Process 32984: 100 leaks for 3200 total leaked bytes.

Leak: 0x7fb1cac05a20  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05a40  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05a60  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05a80  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05ae0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05b00  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05b40  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05b60  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05b80  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05bc0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05be0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05c00  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05c20  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05c40  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05cc0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05d60  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05d80  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05da0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05de0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05e20  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05e40  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05ec0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05ee0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05f00  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05f40  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05f60  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05f80  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac05fe0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac060c0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac060e0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac061c0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac061e0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06260  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06280  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac062a0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac062e0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06320  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06360  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06380  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac063e0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06400  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06420  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06440  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06460  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06480  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac064a0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06560  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06580  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac065c0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac065e0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06600  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06620  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06680  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06700  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06720  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06760  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06780  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac067a0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac067c0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06800  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06820  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06840  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06860  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac068a0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac068c0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06900  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06920  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06940  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06960  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06980  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac069a0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06a00  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06a20  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06a40  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06ac0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06b60  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06b80  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06bc0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06be0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06c00  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06ca0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06ce0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06d00  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06d20  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06d40  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06d60  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06dc0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06e20  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06e40  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06e80  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06ec0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06ee0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06f00  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06f60  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06fa0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac06fe0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac07020  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac07060  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac070a0  size=32  zone: DefaultMallocZone_0x10d72f000
Leak: 0x7fb1cac07120  size=32  zone: DefaultMallocZone_0x10d72f000```


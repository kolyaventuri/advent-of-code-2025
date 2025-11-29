# advent-of-code-2025

## AI DISCLOSURE
Artificial intelligence tools were used to generate or fix issues with helper files in this repository. This includes (in its entirety):
- [`.githooks/pre-commit`](.githooks/pre-commit) To scan `reports/*.md` files for leaked puzzle inputs.
- [`generate-report.js`](generate-report.js) To generate perf. / mem. / leak reports in `reports/*.md`

**_NO AI USED FOR PUZZLE ANALYSIS OR SOLUTIONS_**

## Git Hooks

To enable the repo’s bundled pre-commit hook (runs a check for leaked puzzle inputs):

```sh
git config core.hooksPath .githooks
```

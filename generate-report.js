import process from "node:process";
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import { promisify } from 'node:util';
import { spawn, exec as execSync } from 'node:child_process';
const exec = promisify(execSync);

const argv = process.argv;
const fileName = argv[2];

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const execPath = path.join(__dirname, './out/', fileName ?? '');

if (!fileName) {
  throw new Error('No filename supplied')
}

if (!fs.existsSync(execPath)) {
  throw new Error(`No build ${execPath} exists`);
}

const command = `/usr/bin/time -l "${execPath}"`;
const rssRegex = /\s*([\d.]+)\s+maximum resident set size/m;

const measure = async () => {
  return new Promise(async (resolve) => {
    const { stderr } = await exec(command);
    const rss = (stderr.match(rssRegex)?.[1] / 1e3) ?? null;

    const start = performance.now();
    const child = spawn(execPath, [], { stdio: 'ignore' });
    child.on('exit', () => {
      const time = performance.now() - start;

      resolve({
        rss,
        time
      });
    });
  });
};

const RUNS = 5;

const promises = [];
// Run 2 more than we want so we can throw out min / max
for (let i = 0; i < RUNS + 2; i++) {
  promises.push(measure());
}

const getAverages = (array) => {
  if (!array.length) {
    return null;
  }
  if (array.length === 1) {
    return array[0];
  }

  const keys = Object.keys(array[0]);
  const result = {};

  for (const key of keys) {
    let min = 0;
    let max = 0;
    let total = 0;

    if (array.length > 2) {
      min = Infinity;
      max = -Infinity;
      for (const entry of array) {
        total += entry[key];
        if (entry[key] < min) {
          min = entry[key];
        }

        if (entry[key] > max) {
          max = entry[key];
        }
      }
    }

    const avg = (total - min - max) / (array.length / 2);
    result[key] = avg.toLocaleString('en-US', { maximumFractionDigits: 2 });
  }

  return result;
}

const results = await Promise.all(promises);

const avg = getAverages(results);

const perfOutput = `## Performance over ${RUNS} runs, measured via node spawn + \`performance.now()\`
- **Average**: ${avg.time}ms\n`;

const memOutput = `## Memory over ${RUNS} runs, measured by \`time -l ./out/${fileName}\`
- **Peak**: ${avg.rss} KB`;

const leakCmd = `leaks -q --atExit --list -- ./out/${fileName}`;
let leakResult;
try {
  const { stdout } = await exec(leakCmd);
  leakResult = stdout;
} catch (error) {
  leakResult = error.stdout;
}

const parts = leakResult.split('\n');
let leakCodeBlock = '';
for (let i = 0; i < parts.length; i++) {
  if (parts[i].match(/^leaks Report Version: \d+\.\d+$/)) {
    const data = parts.splice(i, parts.length - i - 1);
    leakCodeBlock = data.join('\n');
    break;
  }
}

const leakOutput = leakCodeBlock.length > 0 ?
  `\n## Leak Report measured by \`leaks --atExit --list -- ./out/${fileName}\`
\`\`\`
${leakCodeBlock}\`\`\`
` : '';

const output = `_This report automatically generated via \`make report FILE=${fileName}\`_

# Report for ${fileName}

${perfOutput}
${memOutput}
${leakOutput}
`;

let puzzleInput = null;
try {
  const input = path.join(__dirname, './input/', `${fileName}.txt`);
  puzzleInput = fs.readFileSync(input).toString();
} catch (error) {
  console.log(error);
  console.warn('!! Unable to scrub puzzle input');
}

const scrubbedOutput = puzzleInput ? output.replace(new RegExp(puzzleInput, 'gi'), '<Puzzle Input Scrubbed Automatically>') : output;

const reportFile = path.join(__dirname, './report/', `${fileName}.md`);
fs.writeFileSync(reportFile, scrubbedOutput, { encoding: 'utf-8' });

import json
import sys

with open(sys.argv[1]) as report:
    data = json.load(report)

lines = [line for source_file in data["source_files"] for line in source_file["coverage"] if line is not None]
branches = [
    branch
    for source_file in data["source_files"]
    for branch in zip(*(iter(source_file.get("branches", [])),) * 4, strict=True)
]
covered_lines = sum(line > 0 for line in lines)
covered_branches = sum(branch[3] > 0 for branch in branches)
coverage = (covered_lines + covered_branches) / (len(lines) + len(branches))
line_coverage = covered_lines / len(lines)
branch_coverage = covered_branches / len(branches)

print(f"Coveralls: {coverage:.1%} (lines {line_coverage:.1%}, branches {branch_coverage:.1%})")

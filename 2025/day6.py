import pathlib
import re

method_dict = {
    "*": lambda x, y: x*y,
    "+": lambda x, y: x+y,
}

input = pathlib.Path(pathlib.Path.cwd()) / "day6-input.txt"
sum = 0
with input.open() as f:
    lines = list()
    while True:
        line = f.readline().replace("\n", "")
        if not line: break
        lines.append(re.findall(r"\d+|\*|\+", line))
    
    for x in range(len(lines[0])):
        col_res = list();
        for y in range(len(lines)):
            col_res.append(lines[y][x])

        method = col_res[-1]
        res = int(col_res[0])
        for d in col_res[1:-1]:
            res = method_dict[method](res, int(d))
        sum += res


print("The total of all the math problems is", sum)

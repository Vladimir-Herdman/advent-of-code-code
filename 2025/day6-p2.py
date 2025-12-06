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
        lines.append(line)
    
    col_list = list()
    for x in range(len(lines[0])-1, -1, -1):
        cur_num = "";
        method = None
        for y in range(len(lines)):
            c = lines[y][x]
            if c in ["*", "+"]:
                method = method_dict[c]
                break
            if c != " ":
                cur_num += c
        if cur_num != "": col_list.append(cur_num)
        if method:
            res = int(col_list[0])
            for d in col_list[1:]:
                res = method(res, int(d))
            sum += res
            col_list.clear()

print("The total of all the math problems is", sum)

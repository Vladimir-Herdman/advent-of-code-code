"""For day 1, take a list of R41, L22, and such as input. 0-99 on rotation lock, every time
you hit 0 (pass or land on), add to counter
"""

import pathlib
import math

# First
#input = pathlib.Path(pathlib.Path.cwd()) / "day1-input.txt"
#cur = 50
#count = 0
#
#with input.open() as f:
#    while True:
#        line = f.readline().replace("\n", "")
#        if not line: break
#
#        direction = line[0]
#        movement = int(line[1:])
#
#        if direction == "L": movement = -movement
#        cur += movement
##        #print("bef:",cur)
#        if cur < 0 or cur >= 100: cur = abs(cur % 100)
#        if cur == 0: count += 1
#
##print(f"Your secret code answer (num times 0 happens) is: {count}")

# Second
input = pathlib.Path(pathlib.Path.cwd()) / "day1-input.txt"
cur = 50
count = 0

with input.open() as f:
    while True:
        line = f.readline().replace("\n", "")
        if not line: break

        direction = line[0]
        movement = int(line[1:])

        if direction == "L": movement = -movement
        print("bef:",cur)
        print("move:", movement)
        cur += movement
        if (cur <= 0 or cur >= 100):
            passed_zero = (math.floor(abs(cur) / 100) if direction == "R" else math.floor(abs(cur) / 100)+1)
            print("passed:", passed_zero)
            count += (passed_zero if passed_zero != 0 else 1)
            if cur - movement == 0 and direction == "L" and abs(cur % 100) != 0: count -= 1
            cur = abs(cur % 100)
        print("aft:",cur)

        print("count:",count,"\n")

print(f"Your secret code answer (num times 0 happens) is: {count}")

import pathlib

input = pathlib.Path(pathlib.Path.cwd()) / "day3-input.txt"
sum = 0
with input.open() as f:
    while True:
        pack = f.readline().replace("\n", "").replace(" ", "")
        if not pack: break
        digit = ""

        pack_list = list(pack)
        for i in range(11, -1, -1):
            ld = (sorted(pack_list[:-i])[-1] if i>0 else sorted(pack_list[:])[-1])
            pack_list = pack_list[pack_list.index(ld)+1:]
            digit += ld

        sum += int(digit)

print("The total sum of each pack's largest is:", sum)

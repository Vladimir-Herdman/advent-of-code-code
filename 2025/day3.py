import pathlib

input = pathlib.Path(pathlib.Path.cwd()) / "day3-input.txt"
sum = 0
with input.open() as f:
    while True:
        pack = f.readline().replace("\n", "").replace(" ", "")
        if not pack: break

        pack_list = list(pack)
        ld = sorted(pack_list[:-1])[-1]
        print("pack:", pack, "\nld:", ld)
        rd = sorted(pack.split(str(ld), 1)[1])[-1]
        print("rd:", rd)
        digit = int(ld + rd)
        sum += digit

print("The total sum of each pack's largest is:", sum)

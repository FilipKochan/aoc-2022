import sys

def solve():
  res1 = 0
  cycle = 0
  reg_x = 1
  lines = [["." for _ in range(40)] for _ in range(6)]
  for line in sys.stdin:
    if line == "noop\n":
      if abs(reg_x - (cycle % 40)) <= 1:
        lines[cycle // 40][cycle % 40] = "#"
      cycle += 1
      if (cycle + 20) % 40 == 0:
        res1 += cycle * reg_x
      continue

    [op, arg] = line.split()
    assert op == "addx"
    if abs(reg_x - (cycle % 40)) <= 1:
      lines[cycle // 40][cycle % 40] = "#"
    cycle += 1
    if (cycle + 20) % 40 == 0:
        res1 += cycle * reg_x
    if abs(reg_x - (cycle % 40)) <= 1:
      lines[cycle // 40][cycle % 40] = "#"
    cycle += 1
    if (cycle + 20) % 40 == 0:
        res1 += cycle * reg_x
    reg_x += int(arg)

  return res1, lines

res1, lines = solve()
print(f"part 1:{res1}\npart 2:")
[print("".join(line)) for line in lines]
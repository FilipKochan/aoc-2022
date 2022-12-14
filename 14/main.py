import os
import sys
import time
from typing import List, Dict, Tuple

AIR = ' '
ROCK = '#'
SAND = '0'
INPUT = '+'
INPUT_X = 500
INPUT_Y = 0
FPS = 15
CLOCK_PT1 = 0
CLOCK_PT2 = 0
VISUAL = False
BEDROCK_LEVEL = 0


def main():
    global INPUT_X, INPUT_Y, CLOCK_PT1, CLOCK_PT2, VISUAL, BEDROCK_LEVEL
    if len(sys.argv) == 2 and sys.argv[1] == "--visual":
        VISUAL = True

    min_x = INPUT_X
    max_x = INPUT_X
    min_y = 0
    max_y = 0

    lines = []
    for line in sys.stdin:
        ln = []
        for coord in line.split(" -> "):
            x, y = list(map(int, coord.split(",")))
            min_x = min(x, min_x)
            max_x = max(x, max_x)
            max_y = max(y, max_y)
            ln.append((x, y))
        lines.append(ln)

    grid = [[AIR for _ in range(int(max_x - min_x + 3))] for _ in range(int(max_y - min_y + 1))]

    BEDROCK_LEVEL = max_y + 2

    reduced = []
    for line in lines:
        r = []
        for x, y in line:
            r.append((x - min_x + 1, y))
        reduced.append(r)
    INPUT_X -= min_x - 1

    for line in reduced:
        for i in range(1, len(line)):
            x, y = line[i]
            sx, sy = line[i - 1]
            xdiff = 0
            ydiff = 0
            if sx > x:
                xdiff = -1
            elif sx < x:
                xdiff = 1
            elif sy > y:
                ydiff = -1
            elif sy < y:
                ydiff = 1

            while x != sx or y != sy:
                grid[sy][sx] = ROCK
                sx += xdiff
                sy += ydiff
            grid[sy][sx] = ROCK

    grid[INPUT_Y][INPUT_X] = INPUT
    grid_pt2: Dict[Tuple[int, int], str] = {}

    for i, line in enumerate(grid):
        for j, char in enumerate(line):
            grid_pt2[i, j] = char

    # part 1
    while generate_sand_part_1(grid):
        CLOCK_PT1 += 1

    # part 2
    for j in range(len(grid[0])):
        grid_pt2[len(grid), j] = AIR
        grid_pt2[len(grid) + 1, j] = ROCK

    show_grid_part_2(grid_pt2)

    while grid_pt2[INPUT_Y, INPUT_X] != SAND:
        CLOCK_PT2 += 1
        generate_sand_part_2(grid_pt2)

    print("part 1:", CLOCK_PT1)
    print("part 2:", CLOCK_PT2)


def generate_sand_part_2(grid: Dict[Tuple[int, int], str]):
    px, py = INPUT_X, INPUT_Y

    grid[py, px] = SAND
    while True:
        show_grid_part_2(grid)
        if py + 1 == BEDROCK_LEVEL:
            return
        elif grid.get((py + 1, px), AIR) == AIR:
            grid[py, px] = AIR
            py += 1
            grid[py, px] = SAND
        elif grid.get((py + 1, px - 1), AIR) == AIR:
            grid[py, px] = AIR
            py += 1
            px -= 1
            grid[py, px] = SAND
        elif grid.get((py + 1, px + 1), AIR) == AIR:
            grid[py, px] = AIR
            py += 1
            px += 1
            grid[py, px] = SAND
        else:
            return


def generate_sand_part_1(grid: List[List[str]]) -> bool:
    px, py = INPUT_X, INPUT_Y

    while True:
        show_grid_part_1(grid)
        if py >= len(grid) - 1:
            grid[py][px] = AIR
            return False
        if grid[py + 1][px] == AIR:
            grid[py][px] = AIR
            py += 1
            grid[py][px] = SAND
        elif grid[py + 1][px - 1] == AIR:
            grid[py][px] = AIR
            py += 1
            px -= 1
            grid[py][px] = SAND
        elif grid[py + 1][px + 1] == AIR:
            grid[py][px] = AIR
            py += 1
            px += 1
            grid[py][px] = SAND
        else:
            return True


def show_grid_part_2(grid: Dict[Tuple[int, int], str]):
    if not VISUAL:
        return
    os.system("clear")
    prev = grid[INPUT_Y, INPUT_X]
    grid[INPUT_Y, INPUT_X] = INPUT
    min_x = min([x for (_, x) in grid.keys()]) - 1
    max_x = max([x for (_, x) in grid.keys()]) + 1
    min_y = 0

    print("=== part 2 ===")
    for y in range(min_y, BEDROCK_LEVEL + 1):
        line = ""
        for x in range(min_x, max_x + 1):
            if y == BEDROCK_LEVEL:
                line += ROCK
            else:
                line += grid.get((y, x), AIR)
        print(line)
    grid[INPUT_Y, INPUT_X] = prev
    print("time:", CLOCK_PT2)
    time.sleep(1 / FPS)


def show_grid_part_1(grid: List[List[str]]):
    if not VISUAL:
        return
    os.system("clear")
    prev = grid[INPUT_Y][INPUT_X]
    grid[INPUT_Y][INPUT_X] = INPUT
    print("=== part 1 ===")
    for line in grid:
        print("".join(line))
    print("time:", CLOCK_PT1)
    grid[INPUT_Y][INPUT_X] = prev
    time.sleep(1 / FPS)


if __name__ == '__main__':
    main()

import sys
from collections import deque


class Node:
    def __int__(self, x, y, h):
        self.x: int = x
        self.y: int = y
        self.h: int = h


class Edge:
    def __init__(self, start: Node, end: Node, weight: int):
        self.start = start
        self.end = end
        self.weight = weight


def part1(lines):
    q = deque()
    visited = set()

    startx = None
    starty = None
    for i, line in enumerate(lines):
        for j, char in enumerate(line.strip()):
            if char == 'S':
                starty = i
                startx = j

    assert startx is not None
    assert starty is not None

    q.append((startx, starty, 0))
    visited.add((startx, starty))
    while q:
        x, y, cost = q.popleft()

        for xoff, yoff in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
            newx = x + xoff
            newy = y + yoff
            if 0 <= newx < len(lines[0]) and 0 <= newy < len(lines):
                h: int = ord(lines[newy][newx])

                if (newx, newy) not in visited:
                    c = lines[y][x]
                    if c == 'S':
                        c = 'a'
                    if ord(c) + 1 >= h:
                        visited.add((newx, newy))
                        q.append((newx, newy, cost + 1))

                if lines[newy][newx] == 'E':
                    if ord(lines[y][x]) + 1 >= ord('z'):
                        return cost + 1


def part2(lines):
    q = deque()
    visited = set()

    startx = None
    starty = None
    for i, line in enumerate(lines):
        for j, char in enumerate(line.strip()):
            if char == 'E':
                starty = i
                startx = j

    lines = list(map(lambda l: l.replace('E', 'z').replace('S', 'a'), lines))
    assert startx is not None
    assert starty is not None

    visited.add((startx, starty))
    q.append((startx, starty, 0))
    while q:
        x, y, cost = q.popleft()

        for xoff, yoff in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
            newx = x + xoff
            newy = y + yoff
            if 0 <= newx < len(lines[0]) and 0 <= newy < len(lines):
                c: int = ord(lines[newy][newx])

                if (newx, newy) not in visited:
                    h = ord(lines[y][x])

                    if c + 1 >= h:
                        visited.add((newx, newy))
                        q.append((newx, newy, cost + 1))

                        if c == ord('a'):
                            return cost + 1


def main():
    lines = list(map(lambda l: l.strip(), sys.stdin.readlines()))
    print("part 1", part1(lines))
    print("part 2", part2(lines))


if __name__ == '__main__':
    main()

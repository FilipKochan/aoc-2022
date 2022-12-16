import re
import sys
from typing import List, Dict, Set
from collections import deque


VALVES: Dict[str, 'Node'] = {}


class Node:
    def __init__(self, name: str, rate: int):
        self.name = name
        self.rate = rate
        self.children: List['Node'] = []
        self.distance_to: Dict[str, int] = dict()


def main():
    global VALVES
    children: Dict[str, str] = {}

    exp = re.compile("^Valve ([^ ]+) has flow rate=([0-9]+); tunnels? leads? to valves? (.+)\n?$")
    for line in sys.stdin:
        res = exp.match(line)
        if not res:
            raise Exception("invalid format")
        name, rate, _children = res.groups()
        VALVES[name] = Node(name, int(rate))
        children[name] = _children

    for key in children:
        for child in children[key].split(", "):
            VALVES[key].children.append(VALVES[child])

    for k in VALVES:
        q = deque()
        q.append((k, 0))
        visited = set()
        if VALVES[k].rate == 0 and k != 'AA':
            continue

        while q:
            name, prev_d = q.popleft()
            if name in visited:
                continue
            if k != name and VALVES[name].rate > 0:
                VALVES[k].distance_to[name] = prev_d
            for child in VALVES[name].children:
                q.append((child.name, prev_d + 1))
            visited.add(name)

    remaining = {v for v in VALVES if VALVES[v].rate > 0} - {'AA'}
    print("part 1:", find_permutation(VALVES['AA'], 30, remaining))


def find_permutation(start: Node, remaining_time: int, remaining: Set[str]):
    if remaining_time <= 0:
        return 0

    m = 0 if start.name == "AA" else 1
    res = [0]
    for v in remaining:
        r = find_permutation(VALVES[v], remaining_time - start.distance_to[v] - m, remaining - {v})
        res.append(r)

    return (remaining_time - m) * start.rate + max(res)


if __name__ == '__main__':
    main()

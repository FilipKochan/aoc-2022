import sys
from typing import List, Tuple

MONKEY_INPUT_LINES = 7
ITERATIONS_PART1 = 20
ITERATIONS_PART2 = 10000


class Monkey:
    def __init__(self, items, operation, test, throw_if_true, throw_if_false):
        self.items: List[int] = items
        self.operation: str = operation
        self.test: int = test
        self.throw_if_true: int = throw_if_true
        self.throw_if_false: int = throw_if_false
        self.items_processed = 0
        self.reduce_factor = None

    def iterate(self, monkeys: List['Monkey']):
        for item in self.items:
            self.items_processed += 1
            new_value = eval(f"(lambda old: {self.operation})({item})")
            if self.reduce_factor is None:
                new_value = new_value // 3
            else:
                new_value = new_value % self.reduce_factor

            if new_value % self.test == 0:
                monkeys[self.throw_if_true].items.append(new_value)
            else:
                monkeys[self.throw_if_false].items.append(new_value)
        self.items.clear()


def parse() -> Tuple[List[Monkey], List[Monkey]]:
    monkeys_pt1: List[Monkey] = []
    monkeys_pt2: List[Monkey] = []
    items = []
    operation = ""
    test = 0
    throw_to_if_true = 0
    test_primes = []

    for i, line in enumerate(sys.stdin):
        if i % MONKEY_INPUT_LINES == 1:
            items = list(map(int, line.split(": ")[1].split(", ")))
        elif i % MONKEY_INPUT_LINES == 2:
            operation = (line.split(" = ")[1]).strip()
        elif i % MONKEY_INPUT_LINES == 3:
            test = int(line.split()[-1])
            test_primes.append(test)
        elif i % MONKEY_INPUT_LINES == 4:
            throw_to_if_true = int(line.split()[-1])
        elif i % MONKEY_INPUT_LINES == 5:
            throw_to_if_false = int(line.split()[-1])
            monkeys_pt1.append(Monkey(items[:], operation, test, throw_to_if_true, throw_to_if_false))
            monkeys_pt2.append(Monkey(items[:], operation, test, throw_to_if_true, throw_to_if_false))

    lcm = 1
    for p in set(test_primes):
        lcm *= p

    for m in monkeys_pt2:
        m.reduce_factor = lcm

    return monkeys_pt1, monkeys_pt2


def print_res(monkeys: List[Monkey]):
    [m1, m2] = sorted([m.items_processed for m in monkeys], key=lambda x: -x)[0:2]
    print("part 1:", m1 * m2)


def main():
    monkeys_pt1, monkeys_pt2 = parse()

    for i in range(ITERATIONS_PART1):
        for monkey in monkeys_pt1:
            monkey.iterate(monkeys_pt1)

    for i in range(ITERATIONS_PART2):
        for monkey in monkeys_pt2:
            monkey.iterate(monkeys_pt2)

    print_res(monkeys_pt1)
    print_res(monkeys_pt2)


if __name__ == "__main__":
    main()

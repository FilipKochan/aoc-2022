import re
import sys
from typing import Dict
from functools import lru_cache


MONKEYS: Dict[str, str] = dict()


def main():
    global MONKEYS
    exp = re.compile("^([^:]+): (.+)\n?$")
    for line in sys.stdin:
        monkey, op = exp.match(line).groups()
        MONKEYS[monkey] = op

    print("part 1:", calculate('root'))
    print("part 2:", calculate_back())


@lru_cache()
def is_human_dependant(monkey: str):
    if monkey == 'humn':
        return True

    try:
        int(MONKEYS[monkey])
        return False
    except ValueError:
        left, _, right = MONKEYS[monkey].split()
        return is_human_dependant(left) or is_human_dependant(right)


def calculate_back(monkey="root", should_equal=None):
    if monkey == "humn":
        return should_equal

    left, op, right = MONKEYS[monkey].split()
    is_left = is_human_dependant(left)
    is_right = is_human_dependant(right)
    if is_left and is_right:
        raise Exception("both sides human dependant")
    if is_left or op in ["+", '*']:
        if not is_left:
            left, right = right, left
        return calculate_back(left, calculate(right) if should_equal is None else eval(f"{should_equal} "
                                                                                       f"{reverse_op(op)} "
                                                                                       f"{calculate(right)}"))
    if is_right:
        return calculate_back(right, calculate(left) if should_equal is None else eval(f"{calculate(left)} "
                                                                                       f"{op} "
                                                                                       f"{should_equal}"))
    raise Exception("neither sides are human dependant")


def reverse_op(op: str):
    if op == "+":
        return "-"
    if op == "-":
        return "+"
    if op == "*":
        return "//"
    if op == "/":
        return "*"
    raise Exception(f"unknown operation: '{op}'")


@lru_cache()
def calculate(monkey: str) -> int:
    try:
        return int(MONKEYS[monkey])
    except ValueError:
        left, op, right = MONKEYS[monkey].split()
        if op == '/':
            op = "//"
        return eval(f"{calculate(left)} {op} {calculate(right)}")


if __name__ == "__main__":
    main()

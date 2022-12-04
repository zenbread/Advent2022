import argparse
import os
import pytest

INPUT_TEXT = os.path.join(
    os.path.split(os.path.dirname(__file__))[0], 'input.txt')

TEST_INPUT = """\
vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw
"""
TEST_EXPECTED = 157


def score(s: str) -> int:
    s = ord(s)
    if s > 97:
        points = 1 + s - 97
    else:
        points = 27 + s - 65
    return points


def compute(s: str) -> int:
    s = s.splitlines()
    total = 0
    common = ''
    for line in s:
        mid = len(line) // 2
        first = set(line[:mid])
        second = set(line[mid:])
        common = first.intersection(second)
        total += score(common.pop())

    return total


@pytest.mark.parametrize(
    ('input_s', 'expected'),
    ((TEST_INPUT, TEST_EXPECTED), ),
)
def test(input_s: str, expected: int) -> None:
    assert compute(input_s) == expected


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument('data_file', nargs='?', default=INPUT_TEXT)
    args = parser.parse_args()

    with open(args.data_file) as f:
        print(compute(f.read()))

    return 0


if __name__ == '__main__':
    raise SystemExit(main())

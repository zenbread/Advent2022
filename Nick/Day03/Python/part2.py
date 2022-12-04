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
TEST_EXPECTED = 70


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
    index = 0
    while (index < len(s)):
        one, two, three = set(s[index]), set(s[index + 1]), set(s[index + 2])
        common = one.intersection(two, three)
        total += score(common.pop())
        index += 3

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

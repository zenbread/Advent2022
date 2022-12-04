import argparse
import os
import pytest

INPUT_TEXT = os.path.join(
    os.path.split(os.path.dirname(__file__))[0], 'input.txt')

TEST_INPUT = """\
2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8
"""
TEST_EXPECTED = 4


def compute(s: str) -> int:
    s = s.splitlines()
    matching = 0
    for line in s:
        first, _, second = line.partition(',')
        check = 0
        num1, _, num2 = first.partition('-')
        min = int(num1)
        max = int(num2) + 1
        for x in range(min, max):
            check |= 2**(x - 1)

        num1, _, num2 = second.partition('-')
        min = int(num1)
        max = int(num2) + 1
        last = check
        for x in range(min, max):
            check |= 2**(x - 1)
            if last == check:
                matching += 1
                break
            last = check

    return matching


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

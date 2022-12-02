import argparse
import os
import pytest

INPUT_TEXT = os.path.join(
    os.path.split(os.path.dirname(__file__))[0], 'input.txt')

TEST_INPUT = """\
A Y
B X
C Z
"""
TEST_EXPECTED = 15


def compute(s: str) -> int:
    scores = {
        "A": 1,
        "B": 2,
        "C": 3,
    }
    wins = {
        "AA": 3,
        "AB": 6,
        "AC": 0,
        "BB": 3,
        "BA": 0,
        "BC": 6,
        "CC": 3,
        "CA": 6,
        "CB": 0,
    }
    s = s.splitlines()

    total = 0
    for item in s:
        combined = f'{item[0]}{chr(ord(item[2]) - 23)}'
        value = wins[combined] + scores[combined[1]]
        total += value

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

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
TEST_EXPECTED = 12


def compute(s: str) -> int:
    scores = {
        "A": 1,
        "B": 2,
        "C": 3,
    }
    wins = {
        "A": {
            3: "AA",
            6: "AB",
            0: "AC"
        },
        "B": {
            3: "BB",
            0: "BA",
            6: "BC"
        },
        "C": {
            3: "CC",
            6: "CA",
            0: "CB"
        },
    }
    s = s.splitlines()

    total = 0
    for item in s:
        player1, outcome = item[0], (ord(item[2]) - 88) * 3
        play = wins[player1][outcome]
        value = outcome + scores[play[1]]
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

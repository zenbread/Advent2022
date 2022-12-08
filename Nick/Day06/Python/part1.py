import argparse
import os
import pytest

INPUT_TEXT = os.path.join(
    os.path.split(os.path.dirname(__file__))[0], 'input.txt')

TEST_INPUT = """\
mjqjpqmgbljsphdztnvjfqwrcgsmlb
"""
TEST_EXPECTED = 7


def compute(s: str) -> int:
    s = s.strip()
    for index in range(3, len(s)):
        a, b, c, d = s[index - 3], s[index - 2], s[index - 1], s[index]
        test = set([a, b, c, d])
        if len(test) == 4:
            return index + 1


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

import argparse
import os
import pytest

INPUT_TEXT = os.path.join(
    os.path.split(os.path.dirname(__file__))[0], 'input.txt')

TEST_INPUT = """\
mjqjpqmgbljsphdztnvjfqwrcgsmlb
"""
TEST_EXPECTED = 19


def compute(s: str) -> int:
    s = s.splitlines()
    s = s[0]
    distinct = set()
    index = 0
    backtrack = 0
    while index < len(s):
        if s[index] not in distinct:
            distinct.add(s[index])
            if len(distinct) == 14:
                break
            index += 1
            continue
        distinct = set()
        backtrack += 1
        index = backtrack
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

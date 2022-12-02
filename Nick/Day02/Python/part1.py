import argparse
import os
import pytest

INPUT_TEXT = os.path.join(
    os.path.split(os.path.dirname(__file__))[0], 'input.txt')

TEST_INPUT = """\
1000
2000
3000

4000

5000
6000

7000
8000
9000

10000
"""
TEST_EXPECTED = 24_000


def compute(s: str) -> int:
    s = s.splitlines()
    highest = 0
    counter = 0
    for item in s:
        if item == '':
            if counter >= highest:
                highest = counter
            counter = 0
            continue
        counter += int(item)

    # Grab last line
    if highest < counter:
        highest = counter
    return highest


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

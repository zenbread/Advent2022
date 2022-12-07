import argparse
import os
import pytest

INPUT_TEXT = os.path.join(
    os.path.split(os.path.dirname(__file__))[0], 'input.txt')

TEST_INPUT = """\
    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2
"""
TEST_EXPECTED = "CMZ"


def compute(s: str) -> int:
    s = s.splitlines()
    mid_point = 0
    for line in s:
        if line == '':
            mid_point -= 1
            break
        mid_point += 1
    stacks_count = int(s[mid_point].split()[-1])
    stacks = [[] for _ in range(stacks_count)]
    # Make stacks
    for line in s[mid_point - 1::-1]:
        stack_index = 0
        for index in range(1, stacks_count * 4, 4):
            if line[index] != ' ':
                stacks[stack_index].append(line[index])
            stack_index += 1

    # Parse instructions
    instruction_point = mid_point + 2
    for ins in s[instruction_point:]:
        ins_list = ins.split()
        count = int(ins_list[1])
        from_s = int(ins_list[3]) - 1
        to_s = int(ins_list[5]) - 1

        for _ in range(count):
            tmp = stacks[from_s].pop()
            stacks[to_s].append(tmp)

    answers = ''.join([stack[-1] for stack in stacks])

    return answers


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

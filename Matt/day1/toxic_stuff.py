lines = ["if (add_amt == '0'):\n", "    return cur_amt + 0\n"]
for i in range(0, 99999):
    lines.append("if (add_amt == '%s'):\n" % i)
    lines.append("    return cur_amt + %s\n" % i)

file1 = open('effecient.txt', 'w')
file1.writelines(lines)
file1.close()
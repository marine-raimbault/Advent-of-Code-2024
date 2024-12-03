import re

def read_file(filename):
    with open(filename) as f:
        return f.read() # everything in one big string
    
# 0) Read the file
# 1) recognize all the patterns in the code with the format mul(x,y)
    # We are going to use regex. We want mult, ( then a number, then a comma, then a number, then )
    # It looks like all the number have one to three digits
    # using https://docs.python.org/2/library/re.html 
    # using https://pythex.org/ we can see that the pattern is mul\((\d{1,3}),(\d{1,3})\)
# 2) sum all the values of x times y

def recognize_patterns(corrupted_memory):
    pattern = r"mul\((\d{1,3}),(\d{1,3})\)"
    return re.findall(pattern, corrupted_memory)


def sum_of_product(matches):
    return sum(int(x) * int(y) for x, y in matches)


def test_recognize_patterns():
    assert recognize_patterns("mul(2,3)") == [('2', '3')]

def test_sum_of_product():
    assert sum_of_product([('2', '3')]) == 6

def answer_part1(filename):
    corrupted_memory = read_file(filename)
    matches = recognize_patterns(corrupted_memory)
    return sum_of_product(matches)

def test_answer_part1():
    assert answer_part1("../input/input3_test.txt") == 161
    # assert answer("../input/input3.txt") == ""


## Part 2 

def recognize_patterns_enabled_or_disabled(corrupted_memory):
    mul_pattern = r"mul\((\d{1,3}),(\d{1,3})\)"
    control_pattern = r"(do\(\)|don't\(\))"
    return re.findall(f"{mul_pattern}|{control_pattern}", corrupted_memory)
# I tried to put the "control_pattern" first but it didn't work. 
# So I put the mul_pattern first and it worked.

def calculate_enabled_mul_sum(matches):
    enabled = True
    total_sum = 0
    
    for match in matches:
        if match[0] and match[1]:  # This is a mul(X,Y) instruction
            if enabled:
                x, y = int(match[0]), int(match[1])
                total_sum += x * y
        elif match[2] == "do()":  # This is a do() instruction
            enabled = True
        elif match[2] == "don't()":  # This is a don't() instruction
            enabled = False
    
    return total_sum


def answer_part2(filename):
    corrupted_memory = read_file(filename)
    matches = recognize_patterns_enabled_or_disabled(corrupted_memory)
    return calculate_enabled_mul_sum(matches)

def test_answer_part2():
    assert answer_part2("../input/input3_2_test.txt") == 48
    # assert answer_part2("../input/input3.txt") == ""

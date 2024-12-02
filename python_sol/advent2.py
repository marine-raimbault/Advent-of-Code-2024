# A report is safe if both:
# The levels are either all increasing or all decreasing.
# Any two adjacent levels differ by at least one and at most three.

# Step 1: Read the file
def readFile(filename):
    with open(filename) as f:
        return f.readlines()

# Step 2: Convert each report to a list of integers
def convert_to_ints(report):
    report = report.split()
    return [int(level) for level in report]

# Step 3: Check if a report is safe
def is_safe(report):
    # Check if all levels are either increasing or decreasing
    is_increasing = all(1 <= report[i+1] - report[i] <= 3 for i in range(len(report) - 1))
    is_decreasing = all(1 <= report[i] - report[i+1] <= 3 for i in range(len(report) - 1))
    return is_increasing or is_decreasing

# Step 4: Count safe reports
def count_safe_reports(reports):
    safe_count = 0
    for report in reports:
        levels = convert_to_ints(report)
        if is_safe(levels):
            safe_count += 1
    return safe_count

# Step 5: Main function
def check_reports(filename):
    reports = readFile(filename)
    safe_reports = count_safe_reports(reports)
    return safe_reports


def test_readFile():
    expected_output = [
        "7 6 4 2 1\n",
        "1 2 7 8 9\n",
        "9 7 6 2 1\n",
        "1 3 2 4 5\n",
        "8 6 4 4 1\n",
        "1 3 6 7 9"
    ]
    assert readFile("input2_test.txt") == expected_output

def test_convert_to_ints():
    assert convert_to_ints("1 2 3 4 5") == [1, 2, 3, 4, 5]


def test_is_safe():
    assert is_safe([7, 6, 4, 2, 1]) == True
    assert is_safe([1, 2, 7, 8, 9]) == False


def test_count_safe_reports():
    reports = [
        "7 6 4 2 1\n",
        "1 2 7 8 9\n",
        "9 7 6 2 1\n",
        "1 3 2 4 5\n",
        "8 6 4 4 1\n",
        "1 3 6 7 9"
    ]
    assert count_safe_reports(reports) == 2

# Test Part 1
def test_check_reports():
    assert check_reports("input2_test.txt") == 2
    # assert check_reports("input2.txt") 


## Part 2
def test_is_almost_safe():
    assert is_almost_safe([1, 3, 2, 4, 5]) == True

def is_increasing(report):
    return all(1 <= report[i+1] - report[i] <= 3 for i in range(len(report) - 1))

def is_decreasing(report):
    return all(1 <= report[i] - report[i+1] <= 3 for i in range(len(report) - 1))

def is_almost_safe(report):
    for j in range (len(report)):
        sub_report = report[:j] + report[j+1:]
        if is_increasing(sub_report) or is_decreasing(sub_report):
          return True
    return False

def count_almost_safe_reports(reports):
    safe_count = 0
    for report in reports:
        levels = convert_to_ints(report)
        if is_safe(levels) or is_almost_safe(levels):
            safe_count += 1
    return safe_count


# for advent 2 part 2
def check_reports2(filename):
    reports = readFile(filename)
    return count_almost_safe_reports(reports)

def test_check_reports2():
    assert check_reports2("input2_test.txt") == 4
    # assert check_reports2("input2.txt") 
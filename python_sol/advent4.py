def parse_grid(filename):
    """Reads the file and parses the word search into a 2D grid."""
    with open(filename) as f:
        return [list(line.strip()) for line in f.readlines()]
    

def in_bounds(x, y, grid):
    """Checks if the position is within grid bounds."""
    rows, cols = len(grid), len(grid[0])
    return 0 <= x < rows and 0 <= y < cols

def check_direction(x, y, dx, dy, word, grid):
    """Checks if the word exists starting from (x, y) in direction (dx, dy)."""
    word_len = len(word)
    for i in range(word_len):
        nx, ny = x + i * dx, y + i * dy
        if not in_bounds(nx, ny, grid) or grid[nx][ny] != word[i]:
            return False
    return True

directions = [
    (0, 1),  # Horizontal right
    (0, -1), # Horizontal left
    (1, 0),  # Vertical down
    (-1, 0), # Vertical up
    (1, 1),  # Diagonal down-right
    (1, -1), # Diagonal down-left
    (-1, 1), # Diagonal up-right
    (-1, -1) # Diagonal up-left
]

def count_word(grid, word):
    """Counts occurrences of a word in all directions in the 2D grid."""
    count = 0
    rows, cols = len(grid), len(grid[0])
    for x in range(rows):
        for y in range(cols):
            for dx, dy in directions:
                if check_direction(x, y, dx, dy, word, grid):
                    count += 1

    return count

def solve1(filename):
    grid = parse_grid(filename)
    return count_word(grid, "XMAS")

def test_answer1():
    assert solve1("../input/input4_test.txt") == 18
    # assert solve1("../input/input4.txt") 


def parse_grid(filename):
    """Reads the file and parses the word search into a 2D grid."""
    with open(filename) as f:
        return [list(line.strip()) for line in f.readlines()]

def find_guard_start(grid):
    """Finds the guard's starting position and direction."""
    directions = '^>v<'
    for x, row in enumerate(grid):
        for y, cell in enumerate(row):
            if cell in directions:
                return (x, y, cell)
    return None

def simulate_guard_path(grid):
    # Parse grid and locate the guard's initial position and direction
    directions = {'^': (-1, 0), '>': (0, 1), 'v': (1, 0), '<': (0, -1)}
    turns = {'^': '>', '>': 'v', 'v': '<', '<': '^'}
    rows = len(grid)
    cols = len(grid[0])
    
    (x, y, cell) = find_guard_start(grid)

    guard_pos = (x, y)
    guard_dir = cell
    
    visited = set()
    visited.add(guard_pos)
    
    while True:
        # Determine the next position
        dr, dc = directions[guard_dir]
        next_pos = (guard_pos[0] + dr, guard_pos[1] + dc)
        
        # Check if the next position is within bounds
        if not (0 <= next_pos[0] < rows and 0 <= next_pos[1] < cols):
            break
        
        # Check for an obstacle
        if grid[next_pos[0]][next_pos[1]] == '#':
            # Turn right
            guard_dir = turns[guard_dir]
        else:
            # Move forward
            guard_pos = next_pos
            visited.add(guard_pos)
    
    return len(visited)



def solve1(filename):
    grid = parse_grid(filename)
    return simulate_guard_path(grid)

# def solve2(filename):
#     """Solves Part Two of the problem."""
#     grid = parse_grid(filename)
#     valid_positions = find_valid_obstruction_positions(grid)
#     return len(valid_positions)

def test_answer():
    assert solve1("../input/input6_test.txt") == 41
    assert solve1("../input/input6.txt") == 5199
    # assert solve2("../input/input6_test.txt") == 6
    # assert solve2("../input/input6.txt") == 
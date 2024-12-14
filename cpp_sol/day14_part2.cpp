#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <thread>   // For sleep functionality
#include <chrono>   // For duration
#include <map>

struct Robot {
    int x, y;  // Position
    int vx, vy; // Velocity
};

// Define ASCII art for numbers
std::map<char, std::vector<std::string>> big_digits = {
    {'0', {"  ###  ", " #   # ", "#     #", "#     #", "#     #", " #   # ", "  ###  "}},
    {'1', {"   #   ", "  ##   ", "   #   ", "   #   ", "   #   ", "   #   ", "  ###  "}},
    {'2', {"  ###  ", " #   # ", "     # ", "   ##  ", "  #    ", " #     ", " ##### "}},
    {'3', {"  ###  ", " #   # ", "     # ", "  ###  ", "     # ", " #   # ", "  ###  "}},
    {'4', {"    #  ", "   ##  ", "  # #  ", " #  #  ", " ##### ", "    #  ", "    #  "}},
    {'5', {" ##### ", " #     ", " #     ", "  ###  ", "     # ", " #   # ", "  ###  "}},
    {'6', {"  ###  ", " #     ", " #     ", " ##### ", " #   # ", " #   # ", "  ###  "}},
    {'7', {" ##### ", "     # ", "    #  ", "   #   ", "  #    ", "  #    ", "  #    "}},
    {'8', {"  ###  ", " #   # ", " #   # ", "  ###  ", " #   # ", " #   # ", "  ###  "}},
    {'9', {"  ###  ", " #   # ", " #   # ", "  #### ", "     # ", " #   # ", "  ###  "}}
};

// Function to display large ASCII seconds
void print_big_seconds(int seconds) {
    std::string seconds_str = std::to_string(seconds);
    std::vector<std::string> big_output(7, ""); // Each digit has 7 rows

    for (char digit : seconds_str) {
        const auto& ascii_digit = big_digits[digit];
        for (int i = 0; i < 7; ++i) {
            big_output[i] += ascii_digit[i] + "  ";
        }
    }

    for (const auto& line : big_output) {
        std::cout << line << '\n';
    }
    std::cout << '\n';
}

void print_grid(const std::vector<Robot>& robots) {
    int min_x = INT_MAX, max_x = INT_MIN;
    int min_y = INT_MAX, max_y = INT_MIN;

    for (const auto& robot : robots) {
        min_x = std::min(min_x, robot.x);
        max_x = std::max(max_x, robot.x);
        min_y = std::min(min_y, robot.y);
        max_y = std::max(max_y, robot.y);
    }

    std::vector<std::string> grid(max_y - min_y + 1, std::string(max_x - min_x + 1, '.'));
    for (const auto& robot : robots) {
        grid[robot.y - min_y][robot.x - min_x] = '#';
    }

    for (const auto& row : grid) {
        std::cout << row << '\n';
    }
    std::cout << '\n';
}

int main() {
    std::vector<Robot> robots;
    std::string line;

    // Parse input
    while (std::getline(std::cin, line) && !line.empty()) {
        Robot r;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &r.x, &r.y, &r.vx, &r.vy);
        robots.push_back(r);
    }

    int seconds = 0;
    while (true) {
        // Print current time and grid
        print_grid(robots);
        // Display seconds in big ASCII art
        print_big_seconds(seconds);


        // Pause for 1 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));


        // Update robot positions
        for (auto& robot : robots) {
            robot.x = (robot.x + robot.vx + 101) % 101;
            robot.y = (robot.y + robot.vy + 103) % 103;
        }

        ++seconds;
    }

    return 0;
}

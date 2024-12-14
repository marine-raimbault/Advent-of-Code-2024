#include <iostream>
#include <vector>
#include <sstream>
#include <string>

struct Robot {
    int x, y;  // Position
    int vx, vy; // Velocity
};

int main() {
    const int width = 101;
    const int height = 103;
    const int seconds = 100;
    
    std::vector<Robot> robots;
    std::string line;
    
    // Parse input
    while (std::getline(std::cin, line) && !line.empty()) {
        Robot r;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &r.x, &r.y, &r.vx, &r.vy);
        robots.push_back(r);
    }
    
    // Simulate movement
    for (int t = 0; t < seconds; ++t) {
        for (auto& robot : robots) {
            robot.x = (robot.x + robot.vx + width) % width;
            robot.y = (robot.y + robot.vy + height) % height;
        }
    }
    
    // Determine quadrants
    int center_x = width / 2;
    int center_y = height / 2;
    int quadrant_counts[4] = {0}; // Q1, Q2, Q3, Q4
    
    for (const auto& robot : robots) {
        if (robot.x == center_x || robot.y == center_y) continue;
        if (robot.x < center_x && robot.y < center_y) ++quadrant_counts[0]; // Q1
        if (robot.x >= center_x && robot.y < center_y) ++quadrant_counts[1]; // Q2
        if (robot.x < center_x && robot.y >= center_y) ++quadrant_counts[2]; // Q3
        if (robot.x >= center_x && robot.y >= center_y) ++quadrant_counts[3]; // Q4
    }
    
    // Calculate safety factor
    int safety_factor = quadrant_counts[0] * quadrant_counts[1] * quadrant_counts[2] * quadrant_counts[3];
    
    std::cout << "Safety Factor: " << safety_factor << std::endl;
    return 0;
}

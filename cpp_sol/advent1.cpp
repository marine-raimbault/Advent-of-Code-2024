
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib> // For abs()

using namespace std;

    int main() {
        // Step 1: Read input from a file
        // std::ifstream file("input1.txt"); // test input file
        std::ifstream file("realInput1.txt");
        if (!file) {
            std::cerr << "Error: Cannot open input file!" << std::endl;
            return 1;
        }

        std::vector<int> leftList, rightList;
        int leftValue, rightValue;

        // The input file has two columns of integers
        while (file >> leftValue >> rightValue) {
            leftList.push_back(leftValue);
            rightList.push_back(rightValue);
        }
        file.close();

        // Step 2: Sort both lists
        std::sort(leftList.begin(), leftList.end());
        std::sort(rightList.begin(), rightList.end());

        // Step 3: Calculate the total distance
        int totalDistance{0};
        for (size_t i = 0; i < leftList.size(); ++i) {
            totalDistance += std::abs(leftList[i] - rightList[i]);
        }

        // Step 4: Output the result
        std::cout << "Total Distance: " << totalDistance << std::endl;

        // Advent 1 question 2
        
        // Step 1: Calculate the frequency of each number in the right list
        std::vector<int> rightFreq(100000,0);
        for (int i : rightList) {
            ++rightFreq[i];
        }
        
        int simScore{0};

        // Step 2: Calculate the similarity score
        for(int i : leftList){
            simScore += i * rightFreq[i];
        }

        // Step 3: Output the result
        std::cout << "Similarity Score: " << simScore << std::endl;

        return 0;
    }


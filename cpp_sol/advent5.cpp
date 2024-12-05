#include <iostream>
#include <fstream>
#include <sstream> // For stringstream, which allows string manipulation and parsing, and getline for line-by-line string reading.
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm> // for find, sort

using namespace std;

// Function to check if an update is valid
bool isValidUpdate(const vector<int>& update, const unordered_map<int, unordered_set<int>>& rules) {
    for (const auto& [page, dependencies] : rules) {
        auto itPage = find(update.begin(), update.end(), page);
        for (int dep : dependencies) {
            auto itDep = find(update.begin(), update.end(), dep);
            if (itPage != update.end() && itDep != update.end() && itPage > itDep) {
                return false; // Rule violated
            }
        }
    }
    return true;
}

// Function for PART 2 to reorder an update based on rules
vector<int> reorderUpdate(vector<int> update, const unordered_map<int, unordered_set<int>>& rules) {
    sort(update.begin(), update.end(), [&rules](int a, int b) {
        // If there is a rule that 'a' must come before 'b', respect it
        if (rules.find(a) != rules.end() && rules.at(a).count(b)) return true;
        if (rules.find(b) != rules.end() && rules.at(b).count(a)) return false;
        // Otherwise, sort by natural order
        return a < b;
    });
    return update;
}

pair<unordered_map<int, unordered_set<int>>, vector<vector<int>>> readRulesAndUpdates(ifstream& file) {
    unordered_map<int, unordered_set<int>> rules;
    vector<vector<int>> updates;

    string line;
    bool readingRules = true;
    while (getline(file, line)) {
        if (line.empty()) {
            readingRules = false; // Switch to reading updates after an empty line
            continue;
        }

        if (readingRules) {
            int x, y;
            sscanf(line.c_str(), "%d|%d", &x, &y); // read the line, find a double digit pattern, store the first digit in x and the second in y
            rules[x].insert(y);
        } else {
            vector<int> update;
            stringstream lineStream(line);
            string page;
            while (getline(lineStream, page, ',')) {
                update.push_back(stoi(page)); //  to convert a std::string to an int
            }
            updates.push_back(update);
        }
    }
    return {rules, updates};
}

int main() {
    // Open the input file
    ifstream inputFile("../input/input5.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    auto [rules, updates] = readRulesAndUpdates(inputFile);
    

    inputFile.close(); // Close the file

    // Process updates
    int sumOfMiddlePages = 0;
    for (const auto& update : updates) {
        if (isValidUpdate(update, rules)) {
            // Valid update, find the middle page
            int middleIndex = update.size() / 2;
            sumOfMiddlePages += update[middleIndex];
        }
    }

    // Part 2 Process updates
    int sumOfMiddlePages2 = 0;
    for (const auto& update : updates) {
        if (!isValidUpdate(update, rules)) {
            // Reorder the invalid update
            vector<int> reordered = reorderUpdate(update, rules);
            int middleIndex = reordered.size() / 2;
            sumOfMiddlePages2 += reordered[middleIndex];
        }
    }

    cout << "Sum of middle pages of valid updates: " << sumOfMiddlePages << endl;
    cout << "Sum of middle pages of reordered incorrect updates: "<< sumOfMiddlePages2 << endl;

    return 0;
}

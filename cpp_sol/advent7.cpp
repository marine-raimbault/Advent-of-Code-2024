#include<iostream>
#include<fstream> // to read the file
#include <sstream> // to easily get each long from the report
#include<vector>
#include<algorithm> // for permutations
#include <numeric> // for accumulate
 
using  namespace std;

auto readFile(string filename){ return ifstream(filename);}
pair<long,vector<long>> parseLine(string line);

bool is_possible(long target, vector<long> numbers);
bool is_possible(long target, vector<long>& numbers, int currIndex, vector<char> &ops);

int main(){
    long answer1 = 0;
    // ifstream file = readFile("../input/input7_test.txt"); // should be 3749
    ifstream file = readFile("../input/input7.txt");

    string line;
    while(getline(file, line)){
        auto [target, numbers] = parseLine(line);
        if(is_possible(target, numbers)){
            answer1 = target + answer1;
        }
    }
    
    cout << answer1 << endl;

    
    return 1;
}

pair<long,vector<long>> parseLine(string line){
    vector<long> numbers;
    long n;
    long pos_of_colon = line.find(':');
    
    long target = stol(line.substr(0,pos_of_colon));  // like stoi but for longs

    istringstream numbers_to_read(line.substr(pos_of_colon+1));
    while(numbers_to_read >> n) numbers.push_back(n);   

    return {target, numbers};
}

bool is_possible(long target, vector<long> numbers){
    vector<char> ops; 
    // we are going to test all the possible permutation of + and *, by using recursion
    return is_possible(target,numbers,1, ops); 
}

// I first tried like this but it failed because recursion messes up with the left to right operation order

// bool is_possible(long target, vector<long> numbers, int currIndex, long tempValue){
//     if(currIndex == (numbers.size())){return target == tempValue;} // end of vector

//     // excluding some already wrong path
//     if(tempValue > target) return false;

//     return is_possible(target, numbers, currIndex + 1, tempValue + numbers[currIndex]) 
//         || is_possible(target, numbers, currIndex + 1, tempValue * numbers[currIndex]);
// }

bool is_possible(long target, vector<long>& numbers, int currIndex, vector<char> &ops) {
    if (currIndex == numbers.size()) {
        // Evaluate the operations left-to-right
        long result = numbers[0];
        for (size_t i = 0; i < ops.size(); ++i) {
            if (ops[i] == '+') result += numbers[i + 1];
            if (ops[i] == '*') result *= numbers[i + 1];
        }
        return result == target;
    }

    // Try adding
    ops.push_back('+');
    if(is_possible(target, numbers, currIndex + 1, ops)) return true;
    ops.pop_back();

    // Try multiplying
    ops.push_back('*');
    if(is_possible(target, numbers, currIndex + 1, ops)) return true;
    ops.pop_back();

    return false;
}
#include<iostream>
#include<fstream>
#include<vector>
#include <map>
#include<set>
#include<algorithm>
#include <cmath> 

using namespace std; 
///////////////////////////////////////////////// Part 2
typedef char Frequency;
typedef pair<int,int> Position;
typedef map<Frequency, vector<Position>>  AntennaRecords;   
typedef vector<vector<Frequency>> Grid;

ifstream readFile(string filename){return ifstream(filename);}
Grid readGrid(ifstream& file);
AntennaRecords collectAntennaRecords(Grid& grid);
////////////////////////////////////////////////  Same as part 1 so far

vector<Position> findAntinodPos(vector<Position>& antenna_pos, int antenna_location1, int antenna_location2, Grid grid);

set<pair<int,int>> getIndexCombination(int n);  

bool is_in_grid(Grid grid, Position pos){
    int x = pos.first;
    int y = pos.second;
    return x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size();
}

template <typename T>
bool is_not_in_the_set(set<T> set, T element){ return set.find(element) == set.end(); }

int main(){
    // ifstream file = readFile("../input/input8_test.txt"); // should now be 34
    ifstream file = readFile("../input/input8.txt"); 
    Grid grid = readGrid(file);
    AntennaRecords antenna_records = collectAntennaRecords(grid);
    set<Position> antinode_pos; 

    for (auto& [freq, antenna_pos] : antenna_records){ 
        if(antenna_pos.size() < 2 ) continue;
        set<pair<int,int>> indexCombination = getIndexCombination(antenna_pos.size());

        // for each combination of two antennas 
        for(pair<int,int> twoChosenAntennas : indexCombination){
            vector<Position> antinodes = findAntinodPos(antenna_pos,twoChosenAntennas.first,twoChosenAntennas.second, grid);
            
            for (auto node : antinodes) {
                if (is_in_grid(grid, node) && is_not_in_the_set(antinode_pos, node)) {
                    antinode_pos.insert(node);
                }
            }
         
        }
       }
       cout << "Number of unique antinodes: " << antinode_pos.size() << endl;
    return 0;
}


Grid readGrid(ifstream& file){
    Grid grid;
    string line;
    while(getline(file,line)){
    vector<Frequency> row;  
    for(Frequency c: line) row.push_back(c);
    grid.push_back(row);
    }
    return grid;
}

AntennaRecords collectAntennaRecords(Grid& grid){
    AntennaRecords antenna_records;         
     for(int r = 0; r<grid.size(); r++){
        for(int c = 0; c<grid[0].size(); c++){
            Frequency freq = grid[r][c];
            if(freq != '.'){
                antenna_records[freq].push_back({r,c});
            }
        }
    }
    return antenna_records;
}


 vector<Position> findAntinodPos(vector<Position>& antenna_pos, int twoChosenAntennas1, int twoChosenAntennas2, Grid grid){
    Position antenna1 = antenna_pos[twoChosenAntennas1]; // p
    Position antenna2 = antenna_pos[twoChosenAntennas2]; // q

    int px = antenna1.first;
    int py = antenna1.second;
    int qx = antenna2.first;
    int qy = antenna2.second;

    // coordinates of the vector pq are given by q - p
    int pq_x = qx - px;
    int pq_y = qy - py;


    vector<Position> antinodes_locations;
    int diagonal_length = sqrt(pow(grid.size(),2) + pow(grid.size(),2));
    // we are gonna add in all the points on the line of the two antennas that are in the grid
    
    int scale = -diagonal_length;
    for(int scale = -diagonal_length; scale <= diagonal_length; scale++){
        int x = scale * pq_x + px;
        int y = scale * pq_y + py;
        if(is_in_grid(grid, {x, y })){
             antinodes_locations.push_back({x,y});
        }
    }
   return antinodes_locations;
}


// get all combination of 2 index from a set of n
set<pair<int,int>> getIndexCombination(int n){
    set<pair<int,int>> res;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){ 
            res.insert({i,j});
        }
    }
    return res;
}





// for each type of antenna, calculate the position of the antipods 
    // by hand ? 
    // get two antennas from the same frequency
    // then add their dx and dy and 

// and record them alongside their frequency in a set if inside the grid
// return the size of that set

#include<iostream>
#include<fstream>
#include<vector>
#include <map>
#include<set>
#include<algorithm>

using namespace std; 

typedef char Frequency;
typedef pair<int,int> Position;
typedef map<Frequency, vector<Position>>  AntennaRecords;   
typedef vector<vector<Frequency>> Grid;

ifstream readFile(string filename){return ifstream(filename);}
Grid readGrid(ifstream& file);
AntennaRecords collectAntennaRecords(Grid& grid);

vector<Position> findAntinodPos(vector<Position>& antenna_pos, int antenna_location1, int antenna_location2);

// get all combination of 2 index from a set of n 
set<pair<int,int>> getIndexCombination(int n);  // TODO test 

int main(){
    ifstream file = readFile("../input/input8_test.txt");
    Grid grid = readGrid(file);
    AntennaRecords antenna_records = collectAntennaRecords(grid);

    set<pair<Position, Frequency>> pod_pos;

    AntennaRecords::iterator it = antenna_records.begin();

    // while(it!=antenna_records.end()){ // for all the antennas of the same type (same freq)
    // for each kombinason of all the pos // TODO, 
    // getting all the combinations https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
    Frequency freq = it->first;
    vector<Position> antenna_pos = it->second;

    cout << " size " << antenna_pos.size() << endl;
    getIndexCombination(antenna_pos.size());

    //for now lets just do it with the first two
    int antenna_location1 = 0; // p 
    int antenna_location2 = 0; // q

    vector<Position> antinods = findAntinodPos(antenna_pos,antenna_location1,antenna_location2);

    // if not already in the set, add it 


    //    }

    return 1;
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


 vector<Position> findAntinodPos(vector<Position>& antenna_pos, int antenna_location1, int antenna_location2){
    Position antenna1 = antenna_pos[antenna_location1];
    Position antenna2 = antenna_pos[antenna_location2];

    int px = antenna1.first;
    int py = antenna1.second;
    int qx = antenna2.first;
    int qy = antenna2.second;

    // coordinates of the vector pq are given by q - p
    int pq_x = qx - px;
    int pq_y = qy - py;

    // we get the position of the antipod by adding 2 times the coordinates of pq to p
    int xpos_antipod1 = 2 * pq_x + px;
    int ypos_antipod1 = 2 * pq_y + py;

    // and -1 the coordinates of pq to p
    int xpos_antipod2 = -1 * pq_x + px;
    int ypos_antipod2 = -1 * pq_y + py;

    vector<Position> antinods_locations;
    antinods_locations.push_back({xpos_antipod1,ypos_antipod1});
    antinods_locations.push_back({xpos_antipod2,ypos_antipod2});
   return antinods_locations;
}


// get all combination of 2 index from a set of n
set<pair<int,int>> getIndexCombination(int n){
    set<pair<int,int>> res;
    for(int i = 0; i < n; i++){
        for(int j = 1; j < n; j++){
            if(i != j && res.find({j,i}) == res.end()){ // we don't want (1,1) and we do NOT want to include (1,2) AND (2,1): combination, not permutation
                res.insert({i,j});
                cout << i << " " << j << endl;
            }
        }
    }
    return res;
}




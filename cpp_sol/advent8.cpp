
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

using namespace std; 

typedef char Frequency;
typedef pair<int,int> Position;
typedef map<Frequency, vector<Position>>  AntennaRecords;   
typedef vector<vector<Frequency>> Grid;

ifstream readFile(string filename){return ifstream(filename);}

Grid readGrid(ifstream& file);
AntennaRecords collectAntennaRecords(Grid& grid);


int main(){
    ifstream file = readFile("../input/input8_test.txt");
    Grid grid = readGrid(file);
    AntennaRecords antenna_records = collectAntennaRecords(grid);

    set<pair<Position, Frequency>> pod_pos;

   AntennaRecords::iterator it = antenna_records.begin();
   // while(it!=antenna_records.end()){ // for all the antennas of the same type (same freq)
   // for each kombinason of all the pos // TODO, 
   
   Frequency freq = it->first;
   vector<Position> antenna_pos = it->second;

   //for know lets just do it with the first two
   int antenna_location1 = 0; // p 
   int antenna_location2 = 0; // q

   auto antenna1 = antenna_pos[antenna_location1];
   auto antenna2 = antenna_pos[antenna_location2];

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

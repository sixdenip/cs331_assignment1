#include <iostream>
#include <fstream>
#include <tuple>
#include <string>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

/*std::tuple<int, int, bool> make_tuple(int wolves, int chickens, bool boat){
    return std::make_tuple(wolves, chickens, boat);
}*/

std::vector<int> read_file(std::string file){
    std::vector<int> values;
    std::ifstream infile(file.c_str());
    int a, b, c;
    char d,e;
    while (infile >> a >> d >> b >> e >> c && d == e && e == ',')
    {
        values.push_back(a);
        values.push_back(b);
        values.push_back(c);
    }
    return values;
}


int main(int argc, char* argv[]) {

    if (argc < 5) {
        std:cout << "Usage : < initial state file > < goal state file > < mode > < output file > " << endl;
        return 0;
    }
    std::vector<int> values = read_file(argv[1]);
    /*for(int i = 0; i < values.size(); i++){
        cout << values.at(i) << "\n";
    }*/
    std::tuple<int, int, bool> left_bank = std::make_tuple(values.at(0), values.at(1), !!values.at(2));
    std::tuple<int, int, bool> right_bank = std::make_tuple(values.at(3), values.at(4), !!values.at(5));
    
    pair<std::tuple<int, int, bool>, std::tuple<int, int, bool>> state; 
    state.first = left_bank;
    state.second = right_bank;

    //cout << std::get<2>(state.second);


    //for different modes
    std::string mode = argv[3];
    if(mode.compare("bfs") == 0){
        //do BFS
    }else if(mode.compare("dfs") == 0){
        //do DFS
    }else if(mode.compare("iddfs") == 0){
        //do IDDFS
    }else if(mode.compare("astar") == 0){
        //DO ASTAR
    }
}

#include <iostream>
#include <fstream>
#include <tuple>
#include <string>
#include <vector>

using namespace std;

std::vector<int> read_file(std::string file){
    std::vector<int> values;
    std::ifstream infile(file);
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
    } else {
        std::vector<int> values = read_file(argv[1]);
    }
}
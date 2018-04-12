#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char* argv[]) {

    if (argc < 5) {
        std:cout << "Usage : < initial state file > < goal state file > < mode > < output file > " << endl;
        return 0;
    } else {
        std::ifstream infile(argv[1]);
        //std:: cout << argv[2] << " " << argv[3] << " " << argv[4] << " " << argv[5] << endl; 
        int a, b, c;
        char d,e;
        while (infile >> a >> d >> b >> e >> c && d == e && e == ',')
        {
            std::cout << a << b << c << endl;
        }

        return 0;
    }
}
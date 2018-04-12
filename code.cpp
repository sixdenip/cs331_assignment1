#include <iostream>
#include <fstream>

using namespace std;


int main() {


    std::ifstream infile("start1.txt");
    int a, b, c;
    char d,e;
    while (infile >> a >> d >> b >> e >> c && d == e && e == ',')
    {
        std::cout << a << b << c << endl;
    }
    return 0;
}
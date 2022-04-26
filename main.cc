#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h> 
#include "boost/multi_array.hpp"


static const int d = 2;
typedef boost::multi_array<int, d> array_type;


// https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string?page=1&tab=trending#tab-top
template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

struct arrinfo {
    std::vector<int> dims;
    std::vector<int> values;
};

void parse_input(std::string filename, arrinfo &info) {
    // open file and read into string
    std::ifstream f(filename);
    
    std::string line;
    std::getline(f, line);

    std::cout << line << std::endl;

    std::vector<std::string> tokens = split(line, ' ');

    std::vector<int> dims;
    for (int i = 0; i < tokens.size(); ++i) {
        dims.push_back(int(pow(2, tokens[i][0] - '0')));
    }

    std::getline(f, line);
    std::vector<int> values;
    for (int i = 0; i < line.size(); ++i) {
        values.push_back(line[i] - '0');
    }

    // put in info
    info.dims = dims;
    info.values = values;
}

int main(int argc, char *argv[])
{
    // parse the arguments
    std::string filename;
    if (argc > 1) {
        std::string fname(argv[1]);
        filename = fname;
    }
    else {
        std::cerr << "please give input" << std::endl;
        exit(1);
    }
    arrinfo info;

    parse_input(filename, info);

    array_type A(info.dims);
    array_type::element* itr = A.data();
    
    for (auto v : info.values) 
        *itr++ = v;
    
}

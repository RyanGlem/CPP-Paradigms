#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "io.h"

using std::string;
using std::getline;
using std::endl;
using std::cout;

string read_data () {

    std::ifstream course_data ("../data/1115.csv", std::ifstream::binary);
    //std::ifstream course_data ("../data/3115.csv", std::ifstream::binary);
    //std::ifstream course_data ("../data/3130.csv", std::ifstream::binary);

    if (!course_data) {
      std::cerr << "No data found" << "\n";
    }

    string inputData;
    string dataChunk;

    course_data.seekg(0, std::ios::beg);
    
    getline(course_data, inputData);

    while (getline (course_data, inputData)) {
      dataChunk += inputData;
    }

    return dataChunk;
}

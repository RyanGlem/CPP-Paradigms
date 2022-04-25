#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "io.h"

using std::string;
using std::getline;
using std::endl;
using std::cout;

string read_data (string path) {

    std::ifstream course_data (path, std::ifstream::binary);

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

void write_data (string formatString) {

  std::ofstream output ("../output/coursedata.txt", std::ofstream::binary);
  // const char * format = formatString.c_str();
  output << formatString;
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CSVReader.cc
 * Author: Mariana
 * 
 * Created on 27 de Setembro de 2018, 23:56
 */

#include "CSVReader.h"
#include <fstream>

namespace hamster {
namespace utils {

CSVReader::CSVReader(std::string filename, std::string delm) :
fileName(filename), delimeter(delm) {
    data.clear();
}

CSVReader::~CSVReader() {
    data.clear();
}

void CSVReader::readData() {
    std::ifstream file(fileName);
    std::string line = "";

    // Iterate through each line and split the content using delimeter
    while (getline(file, line)) {
        this->data.push_back(line);
    }
    // Close the File
    file.close();
}

long unsigned int CSVReader::getNumLines() {
    return this->data.size();
}

std::string CSVReader::getData(long unsigned int line) {
    return this->data[line];
}

} /* namespace utils */
} /* namespace hamster */
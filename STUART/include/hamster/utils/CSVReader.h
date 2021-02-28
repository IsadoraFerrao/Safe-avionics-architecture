/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CSVReader.h
 * Author: Mariana
 *
 * Created on 27 de Setembro de 2018, 23:56
 */

#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>

namespace hamster {
namespace utils {

class CSVReader {
public:

    CSVReader(std::string filename, std::string delm = ",");
    virtual ~CSVReader();

    // Function to fetch all data from a CSV File
    void readData();
    
    // Get the total number of lines
    long unsigned int getNumLines();

    std::string getData(long unsigned int line);
    
private:
    std::string fileName;
    std::string delimeter;
    std::vector<std::string> data;

};

} /* namespace utils */
} /* namespace hamster */

#endif /* CSVREADER_H */


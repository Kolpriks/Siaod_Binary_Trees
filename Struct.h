#pragma once

//struct.h
#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <windows.h>

struct Record {
    char licence[10];
    char nameOfCompany[10];
    char name[20];
    bool activeOrNot;
};

void itFile(const std::string& filename);
void textFileToBinaryFile(std::string textFilename, std::string binaryFilename);
void binaryFileToTextFile(std::string binaryFilename, std::string textFilename);
void printBinaryFile(std::string binaryFilename);
void removeRecordByLicence(std::string binaryFilename, std::string licencenumber);

#endif 
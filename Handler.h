#pragma once
//priemnik.h

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include "struct.h"


using namespace std;

void insertDataToBinaryTree(string binaryFilename);

void printBinaryTree();

int findPositionByKeyBinaryTree(string key);

void removeKeyFromBinaryTree(string key);

string findLineByPosition(string binaryFilename, int pos);

void insertDataToBalancedTree(string binaryFilename);

void printBalancedTree();

int findPositionByKeyBalancedTree(string key);

void removeKeyFromBalancedTree(string key);

int getRotationInALVTree();



void simpleSearch(const string& binaryFilename, const string& licencenumber);

#endif 

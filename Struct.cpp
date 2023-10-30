//struct.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <windows.h>
using namespace std;

struct Record {
	char licence[10];
	char nameOfCompany[10];
	char name[20];
	bool activeOrNot;
};

void itFile(const string& filename)
{
	ifstream file(filename);
	if (!file.good()) // �������� �������� �����
	{
		cout << "�� ������� ������� ����" << endl;
		exit(1);
	}
	else
	{
		cout << "���� " + filename + " ������ �������" << endl << endl;
	}
}


void textFileToBinaryFile(string textFilename, string binaryFilename) {
	ifstream textFile(textFilename);
	ofstream binaryFile(binaryFilename, ios::binary);

	if (!textFile.is_open()) {
		cout << "�� ������� ������� ��������� ����." << endl;
		return;
	}

	if (!binaryFile.is_open()) {
		cout << "�� ������� ������� �������� ����." << endl;
		return;
	}

	Record record;
	string line;
	while (getline(textFile, line)) {
		istringstream iss(line);
		iss >> record.licence >> record.nameOfCompany >> record.name >> record.activeOrNot;
		binaryFile.write(reinterpret_cast<char*>(&record), sizeof(Record));
	}
	textFile.close();
	binaryFile.close();
}

void binaryFileToTextFile(string binaryFilename, string textFilename) {
	ifstream binaryFile(binaryFilename, ios::binary);
	ofstream textFile(textFilename);

	if (!binaryFile.is_open()) {
		cout << "������ ��� �������� ��������� �����" << endl;
		return;
	}

	if (!textFile.is_open()) {
		cout << "������ ��� �������� ���������� �����" << endl;
		return;
	}

	Record record;
	while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
		textFile << record.licence << " " << record.nameOfCompany << " " << record.name << " " << record.activeOrNot << endl;
	}

	binaryFile.close();
	textFile.close();
}

void printBinaryFile(string binaryFilename) {
	ifstream binaryFile(binaryFilename, ios::binary);

	if (!binaryFile.is_open()) {
		cout << "������ ��� �������� ��������� �����" << endl;
		return;
	}

	Record record;
	while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
		cout << record.licence << " " << record.nameOfCompany << " " << record.name << " " << record.activeOrNot << endl;
	}
	cout << endl;
	binaryFile.close();
}

void removeRecordByLicence(string binaryFilename, string licencenumber) {
	ifstream binaryFile(binaryFilename, ios::binary);
	ofstream tempFile("temp.dat", ios::binary);

	if (!binaryFile.is_open()) {
		cout << "������ � �������� ��������� �����." << endl;
		return;
	}

	if (!tempFile.is_open()) {
		cout << "������ �������� ���������� �����." << endl;
		binaryFile.close();
		return;
	}

	Record record;
	while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
		if (strcmp(record.licence, licencenumber.c_str()) != 0) {
			tempFile.write(reinterpret_cast<char*>(&record), sizeof(Record));
		}
	}
	cout << endl;
	binaryFile.close();
	tempFile.close();

	remove(binaryFilename.c_str());
	rename("temp.dat", binaryFilename.c_str());
}
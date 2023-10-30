//main.cpp

#include "struct.h"
#include "Handler.h"

#include <iostream>

#include <list>
#include <string>
#include <chrono>
#include <iomanip>
#include <map>
#include <string.h>
using namespace std;




int main() {

	setlocale(LC_ALL, "Russian");

	string filename;
	string id;
	string company;
	string NaMe;
	string active;
	string newLine;
	string result;

	string key;
	int choice;


	cout << "Введите название файла: ";
	cin >> filename;
	itFile(filename);

	while (true) {


		cout << "Конвертация бинарного файла из текстового - 1" << endl;
		cout << "Конвертация текстового файла из бинарного - 2" << endl;
		cout << "Вывод содержимого бинарного файла - 3" << endl;
		cout << "Поместить данные из бинарного файла в дерево - 4" << endl;
		cout << "Вывести Бинарное Дерево Поиска - 5" << endl;
		cout << "Найти значение из Бинарного Дерева Поиска - 6" << endl;
		cout << "Удалить значение из Бинарного Дерева Поиска- 7" << endl;
		cout << "Найти строку в бинарном файле используя позицию, полученную от Бинарного Дерева Поиска- 9" << endl << endl;

		cout << "Линейные поиск по бинарному файлу - 8" << endl << endl;

		cout << "Поместить данные из бинарного файла в  Сбалансированное дерево - 10" << endl;
		cout << "Вывести Сбалансированное Дерево - 11" << endl;
		cout << "Найти значение из Сбалансированного Дерева - 12" << endl;
		cout << "Удалить значение из Сбалансированного Дерева Поиска- 13" << endl;
		cout << "Найти строку в бинарном файле используя позицию, полученную от Сбалансированного Дерева Поиска- 14" << endl;
		cout << "Вывести количество поворотов - 15" << endl;

		cout << "Выход - 0" << endl;

		cout << "Выберите действие: ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 1:
		{
			string binFilename = filename.substr(0, filename.find_last_of('.')) + ".dat";
			textFileToBinaryFile(filename, binFilename);
			cout << "Бинарный файл " << binFilename << " создан." << endl << endl;

			break;
		}
		case 2:
		{
			string binFilename = filename.substr(0, filename.find_last_of('.')) + ".dat";
			binaryFileToTextFile(binFilename, filename);
			cout << "Текстовый файл " << filename << " создан." << endl << endl;

			break;
		}
		case 3:
		{
			string binFilename = filename.substr(0, filename.find_last_of('.')) + ".dat";
			printBinaryFile(binFilename);

			break;
		}
		
		case 4:
		{
			insertDataToBinaryTree("file.dat");
			cout << "Данныые успешно помещенны в дерево!" << endl << endl;
			break;
		}
		case 5:
		{
			printBinaryTree();
			break;
		}
		case 6:
		{	
			string binFilename = filename.substr(0, filename.find_last_of('.')) + ".dat";
			cout << "Введите ключ: " << endl;
			cin >> key;

			int pos = findPositionByKeyBinaryTree(key) - 1;

			cout << pos << endl;
			break;
		}
		case 7:
		{
			cout << "Введите ключ: " << endl;
			cin >> key;
			removeKeyFromBinaryTree(key);
			break;
		}
		case 8:
		{
			string binFilename = filename.substr(0, filename.find_last_of('.')) + ".dat";
			cout << "Введите ключ: " << endl;
			cin >> key;

			auto start = chrono::high_resolution_clock::now();

			simpleSearch(binFilename, key);

			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double> duration = end - start;

			cout << "Время поиска ключа: " << fixed << setprecision(8) << duration.count() << " секунд" << endl;
			break;
		}
		case 9:
		{
			string binFilename = filename.substr(0, filename.find_last_of('.')) + ".dat";
			cout << "Введите ключ: " << endl;
			cin >> key;

			// Засекаем время перед началом поиска
			auto start = chrono::high_resolution_clock::now();

			int pos = findPositionByKeyBinaryTree(key) - 1;

			// Засекаем время после завершения поиска
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double> duration = end - start;

			if (pos >= 0)
			{
				cout << findLineByPosition(binFilename, pos) << endl;
				cout << "Время поиска ключа: " << fixed << setprecision(8) << duration.count() << " секунд" << endl;
			}
			else
			{
				cout << "Ключ не найден!" << endl;
			}
			cout << endl;
			break;
		}

		case 10:
		{
			insertDataToBalancedTree("file.dat");
			cout << "Данныые успешно помещенны в дерево!" << endl << endl;
			break;
		}
		case 11:
		{
			printBalancedTree();
			break;
		}
		case 12:
		{
			string binFilename = filename.substr(0, filename.find_last_of('.')) + ".dat";
			cout << "Введите ключ: " << endl;
			cin >> key;

			findPositionByKeyBalancedTree(key);

			break;
		}
		case 13:
		{
			cout << "Введите ключ: " << endl;
			cin >> key;
			removeKeyFromBalancedTree(key);
			break;
		}
		case 14:
		{
			string binFilename = filename.substr(0, filename.find_last_of('.')) + ".dat";
			cout << "Введите ключ: " << endl;
			cin >> key;

			// Засекаем время перед началом поиска
			auto start = chrono::high_resolution_clock::now();

			int pos = findPositionByKeyBalancedTree(key) - 1;

			// Засекаем время после завершения поиска
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double> duration = end - start;

			if (pos >= 0)
			{
				cout << findLineByPosition(binFilename, pos) << endl;
				cout << "Время поиска ключа: " << fixed << setprecision(8) << duration.count() << " секунд" << endl;
			}
			else
			{
				cout << "Ключ не найден!" << endl;
			}
			cout << endl;
			break;
		}
		case 15:
		{
			double rot = getRotationInALVTree();
			cout << "Количество поворотов: " << rot << endl << endl;
			break;
		}
		case 0:
			return 0;
		}
	}
};

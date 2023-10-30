//priemnik.cpp
#include <iostream>

#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>


#include "struct.h"


using namespace std;




//BINARY TREEEEEEEEEEEEEEEEEEEEEEEEEEEEEE//
struct TreeNode {
    int key;
    int position;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k, int p) : key(k), position(p), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    // Метод для добавления элемента в дерево
    void insert(int key, int position) {
        root = insertRec(root, key, position);
    }

    // Метод для поиска элемента по ключу
    TreeNode* search(int key) {
        return searchRec(root, key);
    }

    // Метод для удаления элемента из дерева
    void remove(int key) {
        root = deleteRec(root, key);
    }

    // Метод для вывода дерева в форме дерева (инфиксный обход)
    void printTree() {
        printTreeRec(root, 0);
    }

private:
    TreeNode* root;

    // Рекурсивный метод для добавления элемента
    TreeNode* insertRec(TreeNode* root, int key, int position) {
        if (root == nullptr) {
            return new TreeNode(key, position);
        }

        if (key < root->key) {
            root->left = insertRec(root->left, key, position);
        }
        else if (key > root->key) {
            root->right = insertRec(root->right, key, position);
        }

        return root;
    }

    // Рекурсивный метод для поиска элемента по ключу
    TreeNode* searchRec(TreeNode* root, int key) {
        if (root == nullptr || root->key == key) {
            return root;
        }

        if (key < root->key) {
            return searchRec(root->left, key);
        }

        return searchRec(root->right, key);
    }

    // Рекурсивный метод для удаления элемента
    TreeNode* deleteRec(TreeNode* root, int key) {
        if (root == nullptr) {
            return root;
        }

        if (key < root->key) {
            root->left = deleteRec(root->left, key);
        }
        else if (key > root->key) {
            root->right = deleteRec(root->right, key);
        }
        else {
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }

            TreeNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteRec(root->right, temp->key);
        }

        return root;
    }

    // Метод для поиска узла с минимальным ключом
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Рекурсивный метод для вывода дерева
    void printTreeRec(TreeNode* root, int depth) {
        if (root != nullptr) {
            printTreeRec(root->right, depth + 1);
            for (int i = 0; i < depth; i++) {
                std::cout << "  ";
            }
            std::cout << root->key << " (" << root->position << ")" << std::endl;
            printTreeRec(root->left, depth + 1);
        }
    }
};


//TREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE END//

//НИЖЕ ВСЕ ФУНКЦИИ К БИНАРНОМУ ДЕРЕВУ ПОИСКА

BinarySearchTree tree;
int position = 1;

//ФУНКЦИЯ ВСТАВКИ ДАННЫХ ИЗ ФАЙЛА В БИНАРНОЕ ДЕРЕВО ПОИСКА
void insertDataToBinaryTree(string binaryFilename) {
    ifstream binaryFile(binaryFilename, ios::binary);

    if (!binaryFile.is_open()) {
        cout << "Ошибка при открытии файла: " << binaryFilename << endl;
        return;
    }


    Record record;

    while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(Record))) {

        string result = (record.licence);
        tree.insert(stoi(result), position);

        position++;
    }


    cout << endl;
    binaryFile.close();
}


//ФУНКЦИЯ УДАЛЕНИЯ ДАННЫХ ИЗ БИНАРНОГО ДЕРЕВО ПОИСКА
void printBinaryTree(){
	tree.printTree();
}


int findPositionByKeyBinaryTree(string key) {
    TreeNode* found = tree.search(stoi(key));
    if (found != nullptr) {
        return found->position;
    }
    else {
        return -1;
    }
}

void removeKeyFromBinaryTree(string key) {
    tree.remove(stoi(key));
    cout << "Значение было успешно удалено!" <<endl;
}


string findLineByPosition(string binaryFilename, int pos)
{
    ifstream file(binaryFilename, ios::binary);

    file.seekg(pos * sizeof(Record), ios::beg);
    Record record;
    file.read(reinterpret_cast<char*>(&record), sizeof(Record));
    file.close();
    string resultLine = string() + record.licence + " " + record.nameOfCompany + " " + record.name + " " + (record.activeOrNot ? "1" : "0");
    return resultLine;
}





//BALANCED TREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE//



class AVLNode {
public:
    int key;
    int position;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k, int pos)
        : key(k), position(pos), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;
    int rotationCount;
    int size;

    int height(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    void updateHeight(AVLNode* node) {
        if (node != nullptr)
            node->height = 1 + (max(height(node->left), height(node->right)));
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        rotationCount++; // Увеличиваем счетчик поворотов

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        rotationCount++; // Увеличиваем счетчик поворотов

        return y;
    }

    AVLNode* insertNode(AVLNode* node, int key, int pos) {
        if (node == nullptr)
            return new AVLNode(key, pos);

        if (key < node->key)
            node->left = insertNode(node->left, key, pos);
        else if (key > node->key)
            node->right = insertNode(node->right, key, pos);
        else
            return node;

        updateHeight(node);

        int balance = balanceFactor(node);

        // Left Heavy
        if (balance > 1) {
            if (key < node->left->key) // Left-Left
                return rotateRight(node);
            if (key > node->left->key) // Left-Right
            {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        // Right Heavy
        if (balance < -1) {
            if (key > node->right->key) // Right-Right
                return rotateLeft(node);
            if (key < node->right->key) // Right-Left
            {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    AVLNode* findMin(AVLNode* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    AVLNode* deleteNode(AVLNode* root, int key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                AVLNode* temp = (root->left) ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else {
                AVLNode* temp = findMin(root->right);
                root->key = temp->key;
                root->position = temp->position;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        updateHeight(root);

        int balance = balanceFactor(root);

        if (balance > 1) {
            if (balanceFactor(root->left) >= 0)
                return rotateRight(root);
            else {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }

        if (balance < -1) {
            if (balanceFactor(root->right) <= 0)
                return rotateLeft(root);
            else {
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }

        return root;
    }

    void printTree(AVLNode* node, int indent = 0) {
        if (node == nullptr)
            return;
        if (node->right)
            printTree(node->right, indent + 4);
        if (indent > 0)
            std::cout << std::setw(indent) << ' ';
        std::cout << node->key << " (" << node->position << ")" << "\n";
        if (node->left)
            printTree(node->left, indent + 4);
    }

public:
    AVLTree() : root(nullptr), rotationCount(0), size(0) {}

    void insert(int key, int pos) {
        root = insertNode(root, key, pos);
        size++;
    }

    int search(int key) {
        AVLNode* current = root;
        while (current != nullptr) {
            if (key == current->key)
                return current->position;
            else if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return -1; // Key not found
    }

    int getSize() {
        return size;
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    void print() {
        printTree(root);
    }

    double getRotationCount() {
        if (root == nullptr) return 0;
        
        return static_cast<double>(rotationCount);
    }

};


//BALANCED TREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE END//

//НИЖЕ ВСЕ ФУНКЦИИ К СБАЛАНСИРОНОМУ ДЕРЕВУ

AVLTree Btree;

void insertDataToBalancedTree(string binaryFilename) {
    ifstream binaryFile(binaryFilename, ios::binary);

    if (!binaryFile.is_open()) {
        cout << "Ошибка при открытии файла: " << binaryFilename << endl;
        return;
    }


    Record record;

    while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(Record))) {

        string result = (record.licence);
        Btree.insert(stoi(result), position);

        position++;
    }


    cout << endl;
    binaryFile.close();
}


void printBalancedTree() {
    Btree.print();
}


int findPositionByKeyBalancedTree(string key) {
    int result = Btree.search(stoi(key));
    if (result != -1) {
        std::cout << "Найден " << key << " на позиции " << result << std::endl;
        return result;
    }
 
    else {
        std::cout << "Ключ " << key << " не найден в дереве." << std::endl;
        return -1;
    }
        
}

void removeKeyFromBalancedTree(string key) {
    Btree.remove(stoi(key));
    cout << "Значение было успешно удалено!" << endl;
}



int getRotationInALVTree(){
    double result = Btree.getRotationCount();
    return result;
}




void simpleSearch(const string& binaryFilename, const string& licencenumber) {
	ifstream binaryFile(binaryFilename, ios::binary);

	if (!binaryFile.is_open()) {
		cout << "Ошибка в открытии бинарного файла." << endl;
		return;
	}

	Record record;
	while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
		if (strcmp(record.licence, licencenumber.c_str()) == 0) {
			cout << "Ключ найден: " << endl;
			cout << record.licence << " " << record.nameOfCompany << " " << record.name << " " << record.activeOrNot << endl;
		}
	}

	binaryFile.close();
}
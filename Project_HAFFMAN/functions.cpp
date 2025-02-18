#include "functions.h"


#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <bitset>
#include <string>

using namespace std;

// Структура узла дерева Хаффмана
struct HuffmanNode {
    unsigned char data; // Символ (для листа)
    int frequency;       // Частота символа
    HuffmanNode* left;    // Левый дочерний узел
    HuffmanNode* right;   // Правый дочерний узел

    HuffmanNode(unsigned char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
    HuffmanNode(int frequency) : data(0), frequency(frequency), left(nullptr), right(nullptr) {}
};


// Пользовательская функция сравнения для приоритетной очереди
struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};




HuffmanNode* buildHuffmanTree(const std::map<unsigned char, int>& freq) {
    //приоритетная очередь для дерева
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;

    //создаем листовой узел и помещаем его в очередь.
    for (auto pair : freq) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        pq.push(node);
    }

    while (pq.size()>1)
    {
        //берем два узла с мин частотой один в лево другой в право
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();



        //создаем новый узел
        HuffmanNode* parent = new HuffmanNode(left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;


        //узел обратно в очередь

        pq.push(parent);

    }

    // возвращаем последний узел в очереди (это корень дерева)
    return pq.top();
}
// Функция для генерации кодов Хаффмана (рекурсивно)
void generateHuffmanCodes(HuffmanNode* node, string code, map<unsigned char, string>& codes) {
    if (node == nullptr) {
        return;
    }

    if (node->left == nullptr && node->right == nullptr) {
        codes[node->data] = code;
        return;
    }

    generateHuffmanCodes(node->left, code + "0", codes);
    generateHuffmanCodes(node->right, code + "1", codes);
}
// Функция для подсчета частот символов в файле
map<unsigned char, int> calculateFrequencies(const string& filename) {
    map<unsigned char, int> frequencies;
    ifstream file(filename, ios::binary);

    if (file.is_open()) {
        unsigned char c;
        while (file.read((char*)&c, 1)) {
            frequencies[c]++;
        }
        file.close();
    }
    else {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return {};
    }

    return frequencies;
}
// Функция для сжатия файла
void compressFile(const string& inputFilename, const string& outputFilename) {
    map<unsigned char, int> frequencies = calculateFrequencies(inputFilename);

    if (frequencies.empty()) {
        cerr << "Нечего сжимать." << endl;
        return;
    }

    HuffmanNode* root = buildHuffmanTree(frequencies);
    map<unsigned char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Не удалось открыть файл для записи: " << outputFilename << endl;
        return;
    }

    // Запись частот символов в файл (необходимо для распаковки)
    size_t frequenciesSize = frequencies.size(); // Сохраняем размер во временную переменную
    outputFile.write(reinterpret_cast<char*>(&frequenciesSize), sizeof(size_t)); // Количество символов
    for (auto const& [symbol, frequency] : frequencies) {
        outputFile.write((char*)&symbol, sizeof(unsigned char));
        outputFile.write((char*)&frequency, sizeof(int));
    }


    // Сжатие данных
    ifstream inputFile(inputFilename, ios::binary);
    string encodedData = "";
    unsigned char c;
    while (inputFile.read((char*)&c, 1)) {
        encodedData += huffmanCodes[c];
    }
    inputFile.close();


    // Padding для выравнивания по байтам (важно!)
    int paddingLength = 8 - (encodedData.length() % 8);
    if (paddingLength == 8) paddingLength = 0;
    for (int i = 0; i < paddingLength; ++i) {
        encodedData += "0";
    }
    outputFile.write((char*)&paddingLength, sizeof(int)); // Запись длины padding

    // Запись сжатых данных побайтно
    for (size_t i = 0; i < encodedData.length(); i += 8) {
        string byteStr = encodedData.substr(i, 8);
        unsigned char byte = (unsigned char)stoi(byteStr, nullptr, 2); // Преобразование двоичной строки в байт
        outputFile.write((char*)&byte, 1);
    }

    outputFile.close();

    // Освобождение памяти, выделенной для дерева Хаффмана
    // (Реализация  удаления дерева не включена, так как может быть сложной.  Для production кода это необходимо!)
}


// Функция для распаковки файла
void decompressFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);

    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл для чтения: " << inputFilename << endl;
        return;
    }

    // Чтение частот символов
    size_t frequenciesSize;
    inputFile.read((char*)&frequenciesSize, sizeof(size_t));
    map<unsigned char, int> frequencies;
    for (size_t i = 0; i < frequenciesSize; ++i) {
        unsigned char symbol;
        int frequency;
        inputFile.read((char*)&symbol, sizeof(unsigned char));
        inputFile.read((char*)&frequency, sizeof(int));
        frequencies[symbol] = frequency;
    }

    HuffmanNode* root = buildHuffmanTree(frequencies);

    // Чтение padding length
    int paddingLength;
    inputFile.read((char*)&paddingLength, sizeof(int));


    // Восстановление данных
    ofstream outputFile(outputFilename, ios::binary);
    HuffmanNode* currentNode = root;
    string decodedData = "";

    // Read the compressed data
    vector<unsigned char> compressedData;
    unsigned char byte;
    while (inputFile.read((char*)&byte, 1)) {
        compressedData.push_back(byte);
    }
    inputFile.close();


    string bitString = "";
    for (unsigned char byte : compressedData) {
        //Convert each byte to its 8-bit binary representation
        for (int i = 7; i >= 0; --i) {
            bitString += ((byte >> i) & 1) ? '1' : '0';
        }
    }

    bitString = bitString.substr(0, bitString.length() - paddingLength); //remove padding

    for (char bit : bitString)
    {
        if (currentNode == nullptr) {
            cerr << "Ошибка: Дерево Хаффмана повреждено или не соответствует данным." << endl;
            outputFile.close();
            delete root;
            return;
        }

        if (bit == '0')
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }

        if (currentNode == nullptr) {
            cerr << "Ошибка: Дерево Хаффмана повреждено или не соответствует данным (после перехода)." << endl;
            outputFile.close();
            delete root;
            return;
        }

        if (currentNode->left == nullptr && currentNode->right == nullptr)
        {
            outputFile.write((char*)&(currentNode->data), 1);
            currentNode = root; // Reset to root for next character
        }
    }

    outputFile.close();
}

#pragma once


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

HuffmanNode* buildHuffmanTree(const map<unsigned char, int>& freq);
void generateHuffmanCodes(HuffmanNode* node, string code, map<unsigned char, string>& codes);
map<unsigned char, int> calculateFrequencies(const string& filename);
void compressFile(const string& inputFilename, const string& outputFilename);
void decompressFile(const string& inputFilename, const string& outputFilename);

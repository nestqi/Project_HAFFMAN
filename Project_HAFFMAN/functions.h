#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <bitset>
#include <string>
#include <filesystem> 


using namespace std;
namespace fs = std::filesystem;

struct HuffmanNode {
    unsigned char data; // символ (для листа)
    int frequency;      // частота символа
    HuffmanNode* left;  // левый сын
    HuffmanNode* right; // правый сын

    HuffmanNode(unsigned char data, int frequency)
        : data(data), frequency(frequency), left(nullptr), right(nullptr) {
    }
    HuffmanNode(int frequency)
        : data(0), frequency(frequency), left(nullptr), right(nullptr) {
    }
};

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

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

// ��������� ���� ������ ��������
struct HuffmanNode {
    unsigned char data; // ������ (��� �����)
    int frequency;       // ������� �������
    HuffmanNode* left;    // ����� �������� ����
    HuffmanNode* right;   // ������ �������� ����

    HuffmanNode(unsigned char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
    HuffmanNode(int frequency) : data(0), frequency(frequency), left(nullptr), right(nullptr) {}
};


// ���������������� ������� ��������� ��� ������������ �������
struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};




HuffmanNode* buildHuffmanTree(const std::map<unsigned char, int>& freq) {
    //������������ ������� ��� ������
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;

    //������� �������� ���� � �������� ��� � �������.
    for (auto pair : freq) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        pq.push(node);
    }

    while (pq.size()>1)
    {
        //����� ��� ���� � ��� �������� ���� � ���� ������ � �����
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();



        //������� ����� ����
        HuffmanNode* parent = new HuffmanNode(left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;


        //���� ������� � �������

        pq.push(parent);

    }

    // ���������� ��������� ���� � ������� (��� ������ ������)
    return pq.top();
}
// ������� ��� ��������� ����� �������� (����������)
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
// ������� ��� �������� ������ �������� � �����
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
        cerr << "�� ������� ������� ����: " << filename << endl;
        return {};
    }

    return frequencies;
}
// ������� ��� ������ �����
void compressFile(const string& inputFilename, const string& outputFilename) {
    map<unsigned char, int> frequencies = calculateFrequencies(inputFilename);

    if (frequencies.empty()) {
        cerr << "������ �������." << endl;
        return;
    }

    HuffmanNode* root = buildHuffmanTree(frequencies);
    map<unsigned char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "�� ������� ������� ���� ��� ������: " << outputFilename << endl;
        return;
    }

    // ������ ������ �������� � ���� (���������� ��� ����������)
    size_t frequenciesSize = frequencies.size(); // ��������� ������ �� ��������� ����������
    outputFile.write(reinterpret_cast<char*>(&frequenciesSize), sizeof(size_t)); // ���������� ��������
    for (auto const& [symbol, frequency] : frequencies) {
        outputFile.write((char*)&symbol, sizeof(unsigned char));
        outputFile.write((char*)&frequency, sizeof(int));
    }


    // ������ ������
    ifstream inputFile(inputFilename, ios::binary);
    string encodedData = "";
    unsigned char c;
    while (inputFile.read((char*)&c, 1)) {
        encodedData += huffmanCodes[c];
    }
    inputFile.close();


    // Padding ��� ������������ �� ������ (�����!)
    int paddingLength = 8 - (encodedData.length() % 8);
    if (paddingLength == 8) paddingLength = 0;
    for (int i = 0; i < paddingLength; ++i) {
        encodedData += "0";
    }
    outputFile.write((char*)&paddingLength, sizeof(int)); // ������ ����� padding

    // ������ ������ ������ ��������
    for (size_t i = 0; i < encodedData.length(); i += 8) {
        string byteStr = encodedData.substr(i, 8);
        unsigned char byte = (unsigned char)stoi(byteStr, nullptr, 2); // �������������� �������� ������ � ����
        outputFile.write((char*)&byte, 1);
    }

    outputFile.close();

    // ������������ ������, ���������� ��� ������ ��������
    // (����������  �������� ������ �� ��������, ��� ��� ����� ���� �������.  ��� production ���� ��� ����������!)
}


// ������� ��� ���������� �����
void decompressFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);

    if (!inputFile.is_open()) {
        cerr << "�� ������� ������� ���� ��� ������: " << inputFilename << endl;
        return;
    }

    // ������ ������ ��������
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

    // ������ padding length
    int paddingLength;
    inputFile.read((char*)&paddingLength, sizeof(int));


    // �������������� ������
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
            cerr << "������: ������ �������� ���������� ��� �� ������������� ������." << endl;
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
            cerr << "������: ������ �������� ���������� ��� �� ������������� ������ (����� ��������)." << endl;
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

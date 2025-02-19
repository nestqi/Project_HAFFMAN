#include "functions.h"

HuffmanNode* buildHuffmanTree(const map<unsigned char, int>& freq) {
    // ������� ������������ ������� ��� �����
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;

    // ��������� �������� ���� (��� ������� �������)
    for (auto pair : freq) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        pq.push(node);
    }

    // ���� �� ��������� ���� ����, ���������� ��� ���� � ����������� ��������
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* parent = new HuffmanNode(left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    return pq.top();
}

void generateHuffmanCodes(HuffmanNode* node, string code, map<unsigned char, string>& codes) {
    if (node == nullptr)
        return;

    // ���� �������� �����, ��������� ���������� ���
    if (node->left == nullptr && node->right == nullptr) {
        codes[node->data] = code;
        return;
    }

    generateHuffmanCodes(node->left, code + "0", codes);
    generateHuffmanCodes(node->right, code + "1", codes);
}

map<unsigned char, int> calculateFrequencies(const string& filename) {
    map<unsigned char, int> frequencies;
    // ���������, ���������� �� ����
    if (!std::filesystem::exists(filename)) {
        cerr << "���� �� ������: " << filename << endl;
        return frequencies;
    }

    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "�� ������� ������� ����: " << filename << endl;
        return frequencies;
    }

    unsigned char c;
    while (file.read(reinterpret_cast<char*>(&c), 1)) {
        frequencies[c]++;
    }
    file.close();
    return frequencies;
}

void compressFile(const string& inputFilename, const string& outputFilename) {
    map<unsigned char, int> frequencies = calculateFrequencies(inputFilename);

    if (frequencies.empty()) {
        cerr << "������ �������: " << inputFilename << endl;
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

    // ��������� ������� ������ (��� ������������)
    size_t frequenciesSize = frequencies.size();
    outputFile.write(reinterpret_cast<char*>(&frequenciesSize), sizeof(size_t));
    for (auto const& [symbol, frequency] : frequencies) {
        outputFile.write(reinterpret_cast<const char*>(&symbol), sizeof(unsigned char));
        outputFile.write(reinterpret_cast<const char*>(&frequency), sizeof(int));
    }

    // ������ ������� ���� ��� �����������
    ifstream inputFile(inputFilename, ios::binary);
    string encodedData;
    unsigned char c;
    while (inputFile.read(reinterpret_cast<char*>(&c), 1)) {
        encodedData += huffmanCodes[c];
    }
    inputFile.close();

    // ��������� padding (���������� �� ������� �����)
    int paddingLength = 8 - (encodedData.length() % 8);
    if (paddingLength == 8) paddingLength = 0;
    for (int i = 0; i < paddingLength; ++i) {
        encodedData += "0";
    }
    outputFile.write(reinterpret_cast<char*>(&paddingLength), sizeof(int));

    // ���������� ������ ������ ��������
    for (size_t i = 0; i < encodedData.length(); i += 8) {
        string byteStr = encodedData.substr(i, 8);
        unsigned char byte = static_cast<unsigned char>(stoi(byteStr, nullptr, 2));
        outputFile.write(reinterpret_cast<char*>(&byte), 1);
    }

    outputFile.close();

    // ����� ���������� �������� ������� ������������ ������ ������ (�� �����������)
}

void decompressFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "�� ������� ������� ���� ��� ������: " << inputFilename << endl;
        return;
    }

    // ��������������� ������� ������
    size_t frequenciesSize;
    inputFile.read(reinterpret_cast<char*>(&frequenciesSize), sizeof(size_t));
    map<unsigned char, int> frequencies;
    for (size_t i = 0; i < frequenciesSize; ++i) {
        unsigned char symbol;
        int frequency;
        inputFile.read(reinterpret_cast<char*>(&symbol), sizeof(unsigned char));
        inputFile.read(reinterpret_cast<char*>(&frequency), sizeof(int));
        frequencies[symbol] = frequency;
    }

    HuffmanNode* root = buildHuffmanTree(frequencies);

    int paddingLength;
    inputFile.read(reinterpret_cast<char*>(&paddingLength), sizeof(int));

    // ������ ������ ������
    vector<unsigned char> compressedData;
    unsigned char byte;
    while (inputFile.read(reinterpret_cast<char*>(&byte), 1)) {
        compressedData.push_back(byte);
    }
    inputFile.close();

    string bitString;
    for (unsigned char b : compressedData) {
        for (int i = 7; i >= 0; --i) {
            bitString += ((b >> i) & 1) ? '1' : '0';
        }
    }

    // ������� padding
    if (paddingLength > 0 && paddingLength <= bitString.size())
        bitString = bitString.substr(0, bitString.size() - paddingLength);

    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "�� ������� ������� ���� ��� ������: " << outputFilename << endl;
        return;
    }

    HuffmanNode* currentNode = root;
    for (char bit : bitString) {
        if (bit == '0')
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;

        // ���� �������� �����, ���������� ������
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            outputFile.write(reinterpret_cast<char*>(&(currentNode->data)), 1);
            currentNode = root;
        }
    }
    outputFile.close();
}

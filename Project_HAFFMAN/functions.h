#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

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
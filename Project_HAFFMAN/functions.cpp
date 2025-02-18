#include "functions.h"

HuffmanNode* buildHuffmanTree(const std::map<unsigned char, int>& freq) {
    //������������ ������� ��� ������
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;

    //������� �������� ���� � �������� ��� � �������.
    for (auto pair : freq) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        pq.push(node);
    }
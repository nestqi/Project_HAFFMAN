#include "functions.h"

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

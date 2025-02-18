#include "functions.h"

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

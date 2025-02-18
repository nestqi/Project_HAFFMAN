#include "functions.h"

HuffmanNode* buildHuffmanTree(const std::map<unsigned char, int>& freq) {
    //приоритетная очередь для дерева
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;

    //создаем листовой узел и помещаем его в очередь.
    for (auto pair : freq) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        pq.push(node);
    }
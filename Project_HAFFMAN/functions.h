#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

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
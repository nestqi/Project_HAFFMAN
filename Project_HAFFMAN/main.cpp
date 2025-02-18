#include "functions.cpp"
#include "functions.h"
int main()
{
    // Сжатие текстового файла
    compressFile("input.txt", "compressed.huff");
    cout << "Файл input.txt сжат в compressed.huff" << endl;
    decompressFile("compressed.huff", "decompressed.txt");
    cout << "Файл compressed.huff распакован в decompressed.txt" << endl;

    // Сжатие BMP файла (пример сжатия всего файла, включая заголовок)
    compressFile("image.bmp", "compressed.huff_bmp");
    cout << "Файл image.bmp сжат в compressed.huff_bmp" << endl;
    decompressFile("compressed.huff_bmp", "decompressed.bmp");
    cout << "Файл compressed.huff_bmp распакован в decompressed.bmp" << endl;

    return 0;
}
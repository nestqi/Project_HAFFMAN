#include <iostream>    
#include "functions.h" 

using namespace std;    

int main()
{
    setlocale(LC_ALL, "RU");
    // —жатие текстового файла
    compressFile("input.txt", "compressed.huff");
    cout << "‘айл input.txt сжат в compressed.huff" << endl;

    decompressFile("compressed.huff", "decompressed.txt");
    cout << "‘айл compressed.huff распакован в decompressed.txt" << endl;

    // —жатие BMP файла
    compressFile("image.bmp", "compressed.huff_bmp");
    cout << "‘айл image.bmp сжат в compressed.huff_bmp" << endl;

    decompressFile("compressed.huff_bmp", "decompressed.bmp");
    cout << "‘айл compressed.huff_bmp распакован в decompressed.bmp" << endl;

    return 0;
}

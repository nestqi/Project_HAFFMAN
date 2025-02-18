#include "functions.cpp"
#include "functions.h"
int main()
{
    // ������ ���������� �����
    compressFile("input.txt", "compressed.huff");
    cout << "���� input.txt ���� � compressed.huff" << endl;
    decompressFile("compressed.huff", "decompressed.txt");
    cout << "���� compressed.huff ���������� � decompressed.txt" << endl;

    // ������ BMP ����� (������ ������ ����� �����, ������� ���������)
    compressFile("image.bmp", "compressed.huff_bmp");
    cout << "���� image.bmp ���� � compressed.huff_bmp" << endl;
    decompressFile("compressed.huff_bmp", "decompressed.bmp");
    cout << "���� compressed.huff_bmp ���������� � decompressed.bmp" << endl;

    return 0;
}
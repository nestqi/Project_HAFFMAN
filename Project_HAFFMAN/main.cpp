#include <iostream>
#include <chrono>
#include "functions.h"

int main()
{
    setlocale(LC_ALL, "RU");

    /*
    auto start = std::chrono::high_resolution_clock::now();
    compressFile("input.txt", "compressed.huff");
    auto end = std::chrono::high_resolution_clock::now();
    auto compressTextTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "���� input.txt ���� � compressed.huff �� " << compressTextTime << " ��." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed.huff", "decompressed.txt");
    end = std::chrono::high_resolution_clock::now();
    auto decompressTextTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "���� compressed.huff ���������� � decompressed.txt �� " << decompressTextTime << " ��." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    compressFile("image.bmp", "compressed.huff_bmp");
    end = std::chrono::high_resolution_clock::now();
    auto compressBmpTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "���� image.bmp ���� � compressed.huff_bmp �� " << compressBmpTime << " ��." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed.huff_bmp", "decompressed.bmp");
    end = std::chrono::high_resolution_clock::now();
    auto decompressBmpTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "���� compressed.huff_bmp ���������� � decompressed.bmp �� " << decompressBmpTime << " ��." << std::endl;
    */

    auto start = std::chrono::high_resolution_clock::now();
    compressFile("warandpeace.txt", "compressed_warandpeace.huff");
    auto end = std::chrono::high_resolution_clock::now();
    auto compressTextTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "���� warandpeace.txt ���� � compressed_warandpeace.huff �� " << compressTextTime << " ��." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed_warandpeace.huff", "decompressed_warandpeace.txt");
    end = std::chrono::high_resolution_clock::now();
    auto decompressTextTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "���� compressed_warandpeace.huff ���������� � decompressed_warandpeace.txt �� " << decompressTextTime << " ��." << std::endl;

    return 0;
}

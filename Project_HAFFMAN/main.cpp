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
    std::cout << "‘айл input.txt сжат в compressed.huff за " << compressTextTime << " мс." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed.huff", "decompressed.txt");
    end = std::chrono::high_resolution_clock::now();
    auto decompressTextTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "‘айл compressed.huff распакован в decompressed.txt за " << decompressTextTime << " мс." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    compressFile("image.bmp", "compressed.huff_bmp");
    end = std::chrono::high_resolution_clock::now();
    auto compressBmpTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "‘айл image.bmp сжат в compressed.huff_bmp за " << compressBmpTime << " мс." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed.huff_bmp", "decompressed.bmp");
    end = std::chrono::high_resolution_clock::now();
    auto decompressBmpTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "‘айл compressed.huff_bmp распакован в decompressed.bmp за " << decompressBmpTime << " мс." << std::endl;
    */

    auto start = std::chrono::high_resolution_clock::now();
    compressFile("warandpeace.txt", "compressed_warandpeace.huff");
    auto end = std::chrono::high_resolution_clock::now();
    auto compressTextTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "‘айл warandpeace.txt сжат в compressed_warandpeace.huff за " << compressTextTime << " мс." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed_warandpeace.huff", "decompressed_warandpeace.txt");
    end = std::chrono::high_resolution_clock::now();
    auto decompressTextTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "‘айл compressed_warandpeace.huff распакован в decompressed_warandpeace.txt за " << decompressTextTime << " мс." << std::endl;

    return 0;
}

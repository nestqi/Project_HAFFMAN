#include <iostream>
#include <chrono>
#include "functions.h"

int main()
{
    setlocale(LC_ALL, "RU");


    
    auto start = std::chrono::high_resolution_clock::now();
    compressFile("video.mp4", "compressed.huff");
    auto end = std::chrono::high_resolution_clock::now();
    auto compressTextTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "‘айл video.mp4 сжат в compressed.huff за " << compressTextTime << " мс." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed.huff", "decompressed.mp4");
    end = std::chrono::high_resolution_clock::now();
    auto decompressTextTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "‘айл compressed.huff распакован в decompressed.mp4 за " << decompressTextTime << " мс." << std::endl;

    
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
    
    start = std::chrono::high_resolution_clock::now();
    compressFile("test10.txt", "compressed_test10.huff_txt");
    end = std::chrono::high_resolution_clock::now();
    auto compress_test1_Time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "‘айл test10.txt сжат в compressed_test10.huff_txt за " << compress_test1_Time << " мс." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed_test10.huff_txt", "decompressed_test10.txt");
    end = std::chrono::high_resolution_clock::now();
    auto decompress_test1_Time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "‘айл compressed_test10.huff_txt распакован в decompressed_test10.txt за " << decompress_test1_Time << " мс." << std::endl;
    

    start = std::chrono::high_resolution_clock::now();
    compressFile("warandpeace.txt", "compressed_warandpeace.huff_txt");
    end = std::chrono::high_resolution_clock::now();
    auto compress_warandpeace_Time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "‘айл warandpeace.txt сжат в compressed_warandpeace.huff_txt за " << compress_warandpeace_Time << " мс." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed_warandpeace.huff_txt", "decompressed_warandpeace.txt");
    end = std::chrono::high_resolution_clock::now();
    auto decompress_warandpeace_Time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "‘айл compressed_warandpeace.huff_txt распакован в decompressed_warandpeace.txt за " << decompress_warandpeace_Time << " мс." << std::endl;


    return 0;
}

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
    std::cout << "���� video.mp4 ���� � compressed.huff �� " << compressTextTime << " ��." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed.huff", "decompressed.mp4");
    end = std::chrono::high_resolution_clock::now();
    auto decompressTextTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "���� compressed.huff ���������� � decompressed.mp4 �� " << decompressTextTime << " ��." << std::endl;

    
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
    
    start = std::chrono::high_resolution_clock::now();
    compressFile("test10.txt", "compressed_test10.huff_txt");
    end = std::chrono::high_resolution_clock::now();
    auto compress_test1_Time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "���� test10.txt ���� � compressed_test10.huff_txt �� " << compress_test1_Time << " ��." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed_test10.huff_txt", "decompressed_test10.txt");
    end = std::chrono::high_resolution_clock::now();
    auto decompress_test1_Time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "���� compressed_test10.huff_txt ���������� � decompressed_test10.txt �� " << decompress_test1_Time << " ��." << std::endl;
    

    start = std::chrono::high_resolution_clock::now();
    compressFile("warandpeace.txt", "compressed_warandpeace.huff_txt");
    end = std::chrono::high_resolution_clock::now();
    auto compress_warandpeace_Time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "���� warandpeace.txt ���� � compressed_warandpeace.huff_txt �� " << compress_warandpeace_Time << " ��." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    decompressFile("compressed_warandpeace.huff_txt", "decompressed_warandpeace.txt");
    end = std::chrono::high_resolution_clock::now();
    auto decompress_warandpeace_Time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "���� compressed_warandpeace.huff_txt ���������� � decompressed_warandpeace.txt �� " << decompress_warandpeace_Time << " ��." << std::endl;


    return 0;
}

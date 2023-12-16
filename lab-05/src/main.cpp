//
// Created by Александр Ковель on 13.12.2023.
//

#include "lzw/compress.h"
#include "lzw/decompress.h"
#include <fstream>
#include <iostream>
#include <iterator>

void printUsage()
{
	printf("lzw {compress | decompress} {source} {destination}");
}

// usage:
//
// 0: program name
// 1: encode/decode
// 2: source
// 3: destination
int main(int argc, char** argv)
{

	if (argc != 4)
	{
		printUsage();
		exit(1);
	}

	// Decide encode or decode
	char* op = argv[1];

	const char* inputPath = argv[2];
	const char* outputPath = argv[3];

	std::ifstream inFile(inputPath, std::ios_base::binary);
	std::ofstream outFile(outputPath, std::ios_base::binary);

	if (!inFile || !outFile)
	{
		std::cout << "file stream error" << std::endl;
		return 1;
	}

	inFile.seekg(0, std::ios::end);
	long long fileSize = inFile.tellg();
	inFile.seekg(0, std::ios::beg);

	std::vector<uint8_t> inData(fileSize);
	std::vector<uint8_t> outData;
	inFile.read((char*)(&inData[0]), fileSize);

	if (std::string(op) == "compress")
	{
		LzwCompressService compressService;
		compressService.compress(inData, outData);
		auto size = float(inData.size() - outData.size()) / inData.size() * 100;
		std::cout << "Процент compress: " << size << "%";
	}
	else if (std::string(op) == "decompress")
	{
		LzwDecompressService decompressService;
		decompressService.decompress(inData, outData);
		auto size = 1 - float(outData.size() - inData.size()) / outData.size();
		std::cout << "Процент  decompress: " << size << "%";
	}
	else
	{
		printUsage();
		exit(1);
	}
	outFile.write((char*)(&outData[0]), outData.size());

	return 0;
}
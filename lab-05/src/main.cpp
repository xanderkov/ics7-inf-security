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
	printf("lzw compress | decompress {source} {destination}");
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
		return false;
	}

	if (std::string(op) == "compress")
	{
		LzwCompressService compressService;

		inFile.seekg(0, std::ios::end);
		size_t fileSize = inFile.tellg();
		inFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> inData(fileSize);
		std::vector<uint8_t> outData;
		inFile.read((char*)(&inData[0]), fileSize);

		compressService.compress(inData, outData);

		outFile.write((char*)(&outData[0]), outData.size());
		//        bool result = manager.encode(input, output);
		//        exit(!result);
	}
	else if (std::string(op) == "decompress")
	{
		LzwDecompressService decompressService;

		inFile.seekg(0, std::ios::end);
		size_t fileSize = inFile.tellg();
		inFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> inData(fileSize);
		std::vector<uint8_t> outData;
		inFile.read((char*)(&inData[0]), fileSize);

		decompressService.decompress(inData, outData);

		outFile.write((char*)(&outData[0]), outData.size());

		//        bool result = manager.decode(input, output);
		//        exit(!result);
	}
	else
	{
		printUsage();
		exit(1);
	}

	return 0;
}
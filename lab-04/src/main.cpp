#include "sha1.hpp"
#include "RSA.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

int main(int argc, const char **argv)
{
    // Input
    if (argc != 2)
    {
        std::cout << "Мало аргументов!" << std::endl;
        return 0;
    }
    const std::string filename = argv[1];
    std::cout << "Название файла <" << filename << ">" << std::endl;

    std::ifstream file(filename, std::ios::binary);

    std::string input;
	char byte;
	while (file.read(&byte, sizeof(char))) 
	{
		input += byte;
	}

    file.close();

    // Keys
    Keys keys = calculateRSAKeys();

    // Hash
    SHA1 checksum;
    checksum.update(input);
    const std::string hash = checksum.final();

    std::cout << "SHA-1 для \"" << input << "\" <" << hash << ">" << std::endl << std::endl;

    // Signature creation
    std::vector<long long> vec;
	for (char c : hash) 
	{
		vec.push_back(static_cast<long long>(c));
	}

    std::vector <largeIntegerType> sign = cryptMessage(vec, keys._private);
	
	std::ofstream outf;
	outf.open("output/out.txt", std::ios::app);

	if (outf)
	{
		for (long long num : sign)
		{
			outf << num;
		}

		outf.close();
	}
	else
	{
		std::cerr << "Ошибка при открытии файла" << std::endl;
	}

	std::cout << "ЭЦП <";
	for (auto i = 0; i < sign.size(); ++i)
    {
        std::cout << sign[i];
        if (i != sign.size() - 1)
            std::cout << " ";
    }
	std::cout << ">" << std::endl << std::endl;

    // Signature verification
    SHA1 originalChecksum;
    originalChecksum.update(input);
    const std::string originalHash = originalChecksum.final();

	std::string signatureHash = encryptMessage(sign, keys._public);

	std::cout << "Хеш ЭЦП <" << signatureHash << ">" << std::endl;
	std::cout << "Хеш документа <" << originalHash << ">" << std::endl << std::endl;

	if (originalHash == signatureHash)
		std::cout << "ОК" << std::endl;
	else
		std::cout << "Ошибка!" << std::endl;

    return 0;
}


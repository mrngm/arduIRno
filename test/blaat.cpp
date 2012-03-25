#include <cstdio>
#include <iostream>
#include <string>

int
main (int argc, char** argv) {

	char params[] = "NEC_0x88877_32";
	char* vendor = new char[4];
	unsigned long int code = 0;
	unsigned int bits = 0;

	std::cout << "Scanning params: '" << params << "'" << std::endl;
	std::cout << "sscanf: " << sscanf(params, "%3s_0x%5lx_%2u", vendor, &code, &bits) << std::endl; 
	std::cout << "Vendor: " << vendor << std::endl;
	std::cout << "Code  : " << code   << std::endl;
	std::cout << "Bits  : " << bits   << std::endl;

	return 0;
}


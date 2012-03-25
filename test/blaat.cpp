#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

int
main (int argc, char** argv) {

	char params[] = "Sony_0x88877_32";
	char* vendor;
	unsigned long int code = 0;
	unsigned int bits = 0;

	char * pch;
	char * tokens = new char[strlen(params)];
	strcpy(tokens, params);
	int num = 0;
	pch = strtok(tokens, "_");
	while (pch != NULL) {
		num++;
		switch (num) {
			case 1:
				vendor = new char[strlen(pch)];
				strcpy(vendor, pch);
				break;
			case 2:
				sscanf(pch, "0x%5lx", &code);
				break;
			case 3:
				sscanf(pch, "%2u", &bits);
				break;
			default:
				break;
		}
		pch = strtok (NULL, "_");
	}
	std::cout << "Extracted data from params: '" << params << "'" << std::endl;
	std::cout << "Vendor: " << vendor << std::endl;
	std::cout << "Code  : " << code   << std::endl;
	std::cout << "Bits  : " << bits   << std::endl;

	return 0;
}


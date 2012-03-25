#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char** argv) {

	char params[] = "Sony_0x88877_32";
	char* vendor;
	unsigned long int code = 0;
	unsigned int bits = 0;

	char * pch;
	char * tokens = (char *) malloc(sizeof(char) * strlen(params));
	strcpy(tokens, params);
	int num = 0;
	pch = strtok(tokens, "_");
	while (pch != NULL) {
		num++;
		switch (num) {
			case 1:
				vendor = (char *) malloc(sizeof(char) * strlen(pch));
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
	printf("Extracted data from params: '%s'\n", params);
	printf("Vendor: %s\n", vendor);
	printf("Code  : %lx\n", code  );
	printf("Bits  : %d\n", bits  );
	
	if (vendor != NULL)
	{
		free(vendor);
	}
	free(tokens);

	return 0;
}


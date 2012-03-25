#include "etherShield.h" //ENC28J60 libraries inladen
#include "ETHER_28J60.h" //same.
#include <IRremote.h>    //aangepaste IR libraries voor arduino inladen
#include <string.h>

IRsend irsend;
int outputPin = 3; //Digitale out voor IR-led

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24}; //MAC
static uint8_t ip[4] = {192, 168, 2, 123}; //IP
static uint16_t port = 80; //Poort

ETHER_28J60 e;

void extract(char* params, char* vendor, unsigned long int* code, unsigned int* bits)
{
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
	/*
	 * vervangen voor e.print(blaat) ?
	 */
	/*
	std::cout << "Extracted data from params: '" << params << "'" << std::endl;
	std::cout << "Vendor: " << vendor << std::endl;
	std::cout << "Code  : " << code   << std::endl;
	std::cout << "Bits  : " << bits   << std::endl;
	*/
}

void setup()
{
	e.setup(mac, ip, port);
}

void loop()
{
	char* params;
	if (params = e.serviceRequest())
	{
		e.print(params);
		//output van website zal de waarde params zijn. 
		//bij 192.168.2.123/power zal de tekst op de website
		//enkel 'power' betreffen
		//verder niet nuttig ofzo, enkel even als test.
		e.respond();
	}

	if (params = e.serviceRequest())
	{
		/* proto:
		* (RC5, RC6, RC5x, NEC, Sony, Samsung)
		*/
		char* vendor;
		unsigned long int code = 0;
		unsigned int bits = 0;

		extract(params, vendor, &code, &bits);
		if (vendor == "RC5")
		{
			irsend.sendRC5(code, bits);
		}
		else if (vendor == "RC6")
		{
			irsend.sendRC6(code, bits);
		}
		else if (vendor == "RC5x")
		{
			irsend.sendRC5x(code, bits);
		}
		else if (vendor == "NEC")
		{
			irsend.sendNEC(code, bits);
		}
		else if (vendor == "Sony")
		{
			irsend.sendSony(code, bits);
		}
		else if (vendor == "Samsung")
		{
			irsend.sendSamsung(code, bits);
		}
	/*
	irsend.sendNEC(0x88877, 32); 

	//De eigenlijke code waar het allemaal om gaat.
	//Zal hex 0x88877 verzenden met NEC IR protocol.
	//eigenlijk wil je dus 0x88877 variabel hebben,
	//met input vanuit params. Wat doet char* precies? 
	//irsend.sendNEC verwacht een long unsigned integer, geen char*
	//
	//als je het protocol ook nog wil beinvloeden zou
	//er dus even protocol en IR code uit params gefilterd moeten worden.
	*/
	}
}

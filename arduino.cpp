#include "etherShield.h" //ENC28J60 libraries inladen
#include "ETHER_28J60.h" //same.
#include <IRremote.h>    //aangepaste IR libraries voor arduino inladen

IRsend irsend;
int outputPin = 3; //Digitale out voor IR-led

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24}; //MAC
static uint8_t ip[4] = {192, 168, 2, 123}; //IP
static uint16_t port = 80; //Poort

ETHER_28J60 e;

void setup()
{ 
  e.setup(mac, ip, port);
}

void loop()
{
  char* params;
  if (params = e.serviceRequest())
  {
    e.print(params); //output van website zal de waarde params zijn. 
                     //bij 192.168.2.123/power zal de tekst op de website
                     //enkel 'power' betreffen
                     //verder niet nuttig ofzo, enkel even als test.
    e.respond();
  }
  
  if (params = e.serviceRequest())
  {
    irsend.sendNEC(0x88877, 32); //De eigenlijke code waar het allemaal om gaat.
                                 //Zal hex 0x88877 verzenden met NEC IR protocol.
                                 //eigenlijk wil je dus 0x88877 variabel hebben,
                                 //met input vanuit params. Wat doet char* precies? 
                                 //irsend.sendNEC verwacht een long unsigned integer, geen char*
                                 //
                                 //als je het protocol ook nog wil beinvloeden zou
                                 //er dus even protocol en IR code uit params gefilterd moeten worden.
  }
}
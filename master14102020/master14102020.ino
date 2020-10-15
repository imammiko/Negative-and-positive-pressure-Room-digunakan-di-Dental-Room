
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


struct node{
  int address=0;
  }master,slave1,slave2;


void setup() {
  // put your setup code here, to run once:
master.address=1;
slave1.address=2;
slave1.address=3;
}

void loop() {
  // put your main code here, to run repeatedly:

}

#include <Mouse.h>


#include "wiring_private.h"

void setup() {
  SerialUSB.begin(9600);
  delay(2000);
  Serial1.begin(9600);

  pinPeripheral(0, PIO_SERCOM); //Assign RX function to pin 0
  pinPeripheral(1, PIO_SERCOM); //Assign TX function to pin 1
  
  Mouse.begin();
}

uint8_t i=0;
byte Rx[] = {0,0,0,0,0,0,0,0,0,0};
long xval = 0;
long yval = 0;
long buttonValue = 0;

void loop() {
  int j =0; 
  if (Serial1.available()) {  
    while (Serial1.available() > 0) {
      Rx[j] = Serial1.read();
      delay(8);
      ++j;
    }
    xval = (long(Rx[0]) << 24);
    xval += (long(Rx[1]) << 16);
    xval += (long(Rx[2]) << 8);
    xval += long(Rx[3]);
    
    yval = (long(Rx[4]) << 24);
    yval += (long(Rx[5]) << 16);
    yval += (long(Rx[6]) << 8);
    yval += long(Rx[7]);
    
    buttonValue = long(Rx[8]);

    while (Serial1.available()) { //svuota il buffer se necessario
      byte temp = Serial1.read();
    }
  }
    switch (Rx[8]) {
      case 'L':
        Mouse.click(MOUSE_LEFT);
        delay(50);
        Rx[8] = 0;
        break;
      case 'R':
        Mouse.click(MOUSE_RIGHT);
        delay(50);
        Rx[8] = 0;
        break; 
      case ' ': 
        Mouse.move(xval, yval);
        break;
    }
  delay(10);

}

#include <OSCMessage.h>
#include <OSCBoards.h>
#include <OSCBundle.h>
/*
Make an OSC message and send it over serial
 */

#include <SLIPEncodedSerial.h>
#ifdef BOARD_HAS_USB_SERIAL
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
 SLIPEncodedSerial SLIPSerial(Serial); // Change to Serial1 or Serial2 etc. for boards with multiple serial ports that don’t have Serial
#endif


void setup() {
  //begin SLIPSerial just like Serial
  SLIPSerial.begin(115200);   // set this as high as you can reliably run on your platform
}


void loop(){
  OSCBundle bundle;
  bundle.add("/accel/x").add((int32_t)analogRead(A0));
  bundle.add("/accel/y").add((int32_t)analogRead(A1));
  bundle.add("/accel/z").add((int32_t)analogRead(A2));

  SLIPSerial.beginPacket();  
  bundle.send(SLIPSerial);
  SLIPSerial.endPacket(); // mark the end of the OSC Packet
  bundle.empty();

  delay(20);
}

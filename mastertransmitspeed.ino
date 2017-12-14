#include <Wire.h>
byte   x,i;
void setup() {
  // put your setup code here, to run once:
Wire.begin();
Serial.begin(9600);
}

void loop() {
 // if(Serial.available()>0){
   // x=Serial.read();
  //}
  x=78;
//  i=4;
  for (i=4;i<8;i++){
    Wire.beginTransmission(i);
    Wire.write(x);
    Wire.endTransmission();
  }
  delay(50);
}

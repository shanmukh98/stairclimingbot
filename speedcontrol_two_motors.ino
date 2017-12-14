#include <Wire.h>

#include <PID_v1.h>
double setspeed=60;
double speedleft,speedright;
long int countleft,countright,olt;
double dutycycleleft,dutycycleright;
double interval;
double rate=100;
int data,old;
void change(){
  data=Wire.read();
  double speedlevel=data&0b00000111;
  setspeed=speedlevel*(115/7);
  if(data!=old){
    setdirection();
  }
  old=data;
}
void setdirection(){
  digitalWrite(14,data&64);
  digitalWrite(15,data&32);
  digitalWrite(16,data&16);
  digitalWrite(10,data&8);
}
void isrL(){
  countleft++;
}
void isrR(){
  countright++;
}
PID motorL(&speedleft,&dutycycleleft,&setspeed,2,3,0,DIRECT);
PID motorR(&speedright,&dutycycleright,&setspeed,2,3,0,DIRECT);
void setup() {
  Wire.begin(4);
  Wire.onReceive(change);
  pinMode(14,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(7,INPUT_PULLUP);
  pinMode(0,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7),isrL,CHANGE);
  attachInterrupt(digitalPinToInterrupt(0),isrR,CHANGE);
  motorL.SetMode(AUTOMATIC);
  motorR.SetMode(AUTOMATIC);
  interval=1/rate;
  motorL.SetOutputLimits(0,255);
  motorL.SetSampleTime(10);
  motorR.SetOutputLimits(0,255);
  motorR.SetSampleTime(10);
  
  
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()-olt>interval*1000){
    speedleft=(countleft*60)/(interval*64*24);
    speedright=(countright*60)/(interval*64*24);
    countleft=0;
    countright=0;
    olt=millis();
  }
  motorR.Compute();
  motorL.Compute();
  analogWrite(5,(int)dutycycleleft);
  analogWrite(6,(int)dutycycleright);
}

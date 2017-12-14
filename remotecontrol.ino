int x,y,x1,y1;
int direction;
int speed,data;
int speedm;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  x=analogRead(A0);
  y=analogRead(A1);
  x1=map(x,0,1023,-512,512);
  y1=map(y,0,1023,-512,512);
  if(x1>0&&abs(x1)>abs(y1)*1.2){
    direction=0b00110;
    speed=abs(x1);
  }
  else if(x1<0&&abs(x1)>abs(y1)*1.2){
    direction=0b01001;
    speed=abs(x1);
  }
  else if(y1<0&&abs(x1)*1.2<abs(y1)){
    direction=0b01010;
    speed=abs(y1);
  }  
  else if(y1>0&&abs(x1)*1.2<abs(y1)){
    direction=0b00101;
    speed=abs(y1);
  } 
  else{
 //   direction=0b01111;
    speed=0; 
  }
  speedm=map(speed,0,512,0,7);
  data=(direction<<3)+(speedm);
  Serial.println(data);
 // delay(0);
  
  
  // put your main code here, to run repeatedly:

}

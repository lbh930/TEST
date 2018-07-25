#include <Wire.h>
#include <JY901.h>
#include <Servo.h>
/*
Test on Uno R3.
JY901    UnoR3
SDA <---> SDA
SCL <---> SCL
*/
int pos = 0;
Servo myservo;
//int base = 0;
int initialized = false;
void setup() 
{
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);
  JY901.StartIIC();
} 
void clamp(float mini, float maxi, int &value){
  if (value>maxi)value = maxi;
  if (value<mini)value = mini;
}
void loop() 
{
    JY901.GetAngle();
    int angle = (float)JY901.stcAngle.Angle[2]/32768*180;
    if (angle < 0)angle+=360; //0-360
    if (!initialized){
      //base = angle;
      initialized = true;
    }
    int angle1 = angle;//r 
    //if (angle1<0)angle1+=360;//0-180, 360-180
    if (angle1<=180){
      clamp (0, 90, angle1);
      angle1+=90;
    }else{
      angle1 = angle1-360;
      clamp (-90, 0, angle1);
      angle1 += 90;
    }
    myservo.write(angle1);
    //Serial.println(base);  
    Serial.println(angle);
    Serial.println(angle1);
   //Serial.print("pos:");
    //Serial.print(pos);
    Serial.println("");
    
    delay(300);                       // waits 15ms for the servo to reach the position
}






#include <Wire.h>

byte adress = 0x0A ;        // Write 0x14, Read 0x15 (Includes R/W bit)
byte comand = 0x4C;         // Standard command
byte count = 35;            // Data length read from sensor

String stg;
unsigned int i=0;           // counter

byte in[35];                // Data Input
unsigned int p[18];          // Measure Value

int x;
int y;


void setup()
{
  Wire.begin(); 
  Serial.begin(9600);
}


void loop()
{
  // get sensor data
  Wire.beginTransmission(adress);       // start send write (14h)
  Wire.write(byte(comand));             // send command byte
  Wire.endTransmission();
  delay(1);
  Wire.requestFrom(adress, count);
  for(i=0;i<=count;i++){
    in[i] = Wire.read();                // read char 0-34 (2*(16+1)+1=35)
  }
  Wire.endTransmission();               // stop
  
  x=1;
  y=0;
  
  for(int f=0; f<17; f++){
    p[f]=0xFF*(unsigned int)in[x] + (unsigned int)in[y];
    x=x+2;
    y=y+2;
    if(f==0){
      Serial.print(String(999)+"\n");
    }else{
      stg=String(p[f]);
      if(stg.length()==3){
        Serial.print(stg + "\n");
      }else{
        Serial.print(String(888)+"\n");   //ERROR
      }
    }
     delay(10);
  }
  delay(250);
}

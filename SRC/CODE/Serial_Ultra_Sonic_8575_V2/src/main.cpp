#include <header.h>

int dBuffer = 0;
unsigned char nBuffer = 0;

// Communicate with PCF8574


// unsigned char SonarRead(){
//   unsigned char buffer = 0;
//   Wire.beginTransmission(TrigrAddr1);
//   buffer = Wire.read();
//   Wire.endTransmission();
//   return buffer;
// }
// // Return the order of 


void setup() {

  set_up_I2C();
  
  pinMode(IntPin1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IntPin1), FlipFlag1, FALLING);
  pinMode(IntPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IntPin2), FlipFlag2, FALLING);
  
  Serial.begin(9600);
  while (!Serial); 
}

void loop() { 
  Lane1.Data = 0xFF01;

  SonarPowSet(PowAddr, ~(Lane1.Data));
  SonarPing (Lane1Addr, (Lane1.Data));
  
  // if(flag){
  //   duration = pulseIn(IntPin1, LOW);
  //   distance = duration * 0.034 / 2;
  //   n = LaneSenNum(0x01);
  //   Serial.print("Distance: ");
  //   Serial.println(distance);
  // } 
  // else if (~flag)
  // {
  //   Serial.println("Sensor can't read data");
  // }
  
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // if( (dBuffer != distance)||(n >= nBuffer+4)||(n <= nBuffer-4) ){
  //   lcd1.clear(); 
  // 	lcd1.print("Sensor: ");
  // 	lcd1.print(n);
  // 	lcd1.setCursor(0,1);
  // 	lcd1.print("Distance: ");
  // 	lcd1.print(distance);
  // 	lcd1.setCursor(14,1);
  // 	lcd1.print("CM");
    
  //   dBuffer = distance;
  //   nBuffer = n;
  // }
  
    delay(10);
}


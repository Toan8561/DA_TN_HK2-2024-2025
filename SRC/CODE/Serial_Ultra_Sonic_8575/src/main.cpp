#include <header.h>

int dBuffer = 0;
unsigned char nBuffer = 0;

// Communicate with PCF8574



void setup() {

  set_up_I2C();
  
  pinMode(IntPin1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IntPin1), FlipFlag1, FALLING);
  
  Serial.begin(9600);
  while (!Serial); 
}

void loop() { 

  SonarPowSet(PowAddr, 0xFFFE);
  SonarPing (TrigAddr, 0x0001);
  
  if(flag1){
    duration1 = pulseIn(IntPin1, LOW);
    distance1 = duration1 * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.println(distance1);
    flag1 = false;
  } 
  // else if (~flag)
  // {
  //   Serial.println("Sensor can't read data");
  // }

  
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
  
    delay(100);
}


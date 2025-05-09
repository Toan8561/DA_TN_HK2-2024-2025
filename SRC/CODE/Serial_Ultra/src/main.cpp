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
  attachInterrupt(digitalPinToInterrupt(IntPin1), FlipFlag1, CHANGE);
  pinMode(IntPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IntPin2), FlipFlag1, CHANGE);
  
  Serial.begin(9600);
  while (!Serial); 
}

void loop() { 
   
  SonarPowSet(PowAddr, test);
  SonarPing (TrigAddr, test); 
  // SonarRead(Lane1Addr);
  
  
  if(flag1){
  //   int pulseDuration = (pulseInTimeEnd - pulseInTimeBegin) * (0.034 / 2);
  // //  distance = pulseDuration * 0.034 / 2;

  //   Serial.print("Distance: ");
  //   Serial.println(pulseDuration);

  //   flag1 = false;
    duration = pulseIn(IntPin1, LOW);
    distance = duration * 0.034 / 2;
    Serial.print("Ultrasonic Sensor: ");
    Serial.print(index);
    Serial.println("th");
    Serial.print("Distance: ");
    Serial.println(distance);
  } 


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
  
  
  if( (dBuffer != distance)||(n >= nBuffer+4)||(n <= nBuffer-4) ){
    lcd1.clear(); 
  	lcd1.print("Sensor: ");
  	lcd1.print(index);
  	lcd1.setCursor(0,1);
  	lcd1.print("Distance: ");
  	lcd1.print(distance);
  	lcd1.setCursor(14,1);
  	lcd1.print("CM");
    
    dBuffer = distance;
    nBuffer = index;
  }
  
  delay(500);
  test = (test == 0x8000) ? 0x0001 : (test << 1);
  index = (index == 16) ? 1 : index + 1;
}


#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const uint8_t 	IntPin1		= 2;
const uint8_t 	IntPin2		= 3;

uint8_t n = 0;

const uint8_t	LcdAddr1    = 0x3E;
const uint8_t	LcdAddr2    = 0x3F;
LiquidCrystal_I2C lcd1 (LcdAddr1, 20, 4);
LiquidCrystal_I2C lcd2 (LcdAddr2, 20, 4);

const uint8_t Lane1Addr   = 0x27;
const uint8_t Lane2Addr   = 0x26;
const uint8_t PowAddr     = 0x25;
struct Sonic_Config{
    uint8_t Echo;
    uint8_t Trig;
};
union Sonic_I2C{
    uint16_t Data;
    struct Sonic_Config Config;   
};
union Sonic_I2C Lane1, Lane2;

float duration = 0;
int distance = 0;

volatile bool flag1 = false;
volatile bool flag2 = false;
volatile unsigned long pulseInTimeBegin = micros();
volatile unsigned long pulseInTimeEnd = micros();

void FlipFlag1(){  
    if (digitalRead(IntPin1) == LOW) {
        // start measuring
        pulseInTimeBegin = micros();
    }
    else {
        // stop measuring
        pulseInTimeEnd = micros();
        flag1 = true; 
    }    
}
void FlipFlag2(){  
    if (digitalRead(IntPin2) == LOW) {
        // start measuring
        pulseInTimeBegin = micros();
    }
    else {
        // stop measuring
        pulseInTimeEnd = micros();
        flag2 = true; 
    }    
}

void set_up_I2C(){
    Lane1.Data = 0xFF00;
    Lane2.Data = 0xFF00;

    uint16_t Buffer = ( Lane1.Config.Trig << 8) | ( Lane2.Config.Trig ); 

    Wire.begin();
    Wire.setClock(400000UL);

    Wire.beginTransmission(Lane1Addr);
    Wire.write((uint8_t*)&(Lane1.Data), 2);	
    Wire.endTransmission();

    Wire.beginTransmission(Lane2Addr);
    Wire.write((uint8_t*)&(Lane2.Data), 2);	
    Wire.endTransmission();
    
    Wire.beginTransmission(PowAddr);
    Wire.write((uint8_t*)&Buffer, 2);	
    Wire.endTransmission();

    // lcd1.init();
    // lcd1.backlight();
    // lcd2.init();
    // lcd2.backlight();

}

void SonarPowSet ( uint8_t add, uint16_t data16 ){
/*  
    uint8_t myArray[2];
    myArray[0] = (bigNum >> 8) &amp; 0xFF;
    myArray[1] = bigNum & 0xFF;
*/    
    Wire.beginTransmission(add);
    Wire.write( (uint8_t*)&data16 , 2);  
    Wire.endTransmission();
}

void SonarPing ( uint8_t add, uint16_t data ){
    uint16_t clear = 0xFF00;
    Wire.beginTransmission(add);
    Wire.write( (uint8_t*)&clear , 2);
    delayMicroseconds(2);
    Wire.write( (uint8_t*)&data , 2);  
    delayMicroseconds(10);
    Wire.write( (uint8_t*)&clear , 2);
    Wire.endTransmission();
}

uint8_t LaneSenNum (uint8_t a) {
    // static 
	switch (a){
      case 0x01:	return 1;	break;
      case 0x02:	return 2;	break;
      case 0x04:	return 3;	break;
      case 0x08:	return 4;	break;
      case 0x10:	return 5;	break;
      case 0x20:	return 6;	break;
      case 0x40:	return 7;	break;
      case 0x80:	return 8;	break;
  	}
}


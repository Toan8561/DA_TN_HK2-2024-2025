#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const uint8_t 	IntPin1		= 2;
const uint8_t 	IntPin2		= 3;
const uint8_t   PcfRead     = 0xFF;

const uint8_t	LcdAddr1    = 0x3E;
const uint8_t	LcdAddr2    = 0x3F;
LiquidCrystal_I2C lcd1 (LcdAddr1, 20, 4);
LiquidCrystal_I2C lcd2 (LcdAddr2, 20, 4);

const uint8_t TrigAdd   = 0x27;
const uint8_t EchoAdd   = 0x26;
const uint8_t PowAddr     = 0x25;

float duration = 0;
int distance = 0;

volatile bool flag = false;

void FlipFlag(){  flag = true;  }

void set_up_I2C(){

    uint16_t buffer;

    Wire.begin();
    Wire.setClock(400000UL);

    buffer = 0x0000;

    Wire.beginTransmission(PowAddr);
    Wire.write((byte*)&buffer, 2);	
    Wire.endTransmission();

    Wire.beginTransmission(TrigAdd);
    Wire.write((byte*)&buffer, 2);	
    Wire.endTransmission();

    buffer = 0xFFFFF;
    Wire.beginTransmission(EchoAdd);
    Wire.write((byte*)&buffer, 2);	
    Wire.endTransmission();
    
    lcd1.init();
    lcd1.backlight();
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
    Wire.beginTransmission(add);
    Wire.write(0x00);
    delayMicroseconds(2);
    Wire.write((byte*)data, 2);
    delayMicroseconds(10);
    Wire.write(0x00);
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
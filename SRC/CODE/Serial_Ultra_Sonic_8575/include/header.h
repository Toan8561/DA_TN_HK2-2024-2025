#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const uint8_t 	IntPin1		= 2;
const uint16_t  PcfRead     = 0xFFFF;
const uint16_t  PcfWrite    = 0x0000;

uint8_t n = 0;


const uint8_t	LcdAddr1    = 0x3E;
const uint8_t	LcdAddr2    = 0x3F;
LiquidCrystal_I2C lcd1 (LcdAddr1, 20, 4);
LiquidCrystal_I2C lcd2 (LcdAddr2, 20, 4);

const uint8_t TrigAddr      = 0x27;
const uint8_t EchoAddr      = 0x26;
const uint8_t PowAddr       = 0x25;
struct Sonic_Config{
    uint8_t Echo;
    uint8_t Trig;
};
union Sonic_I2C{
    uint16_t Data;
    struct Sonic_Config Config;   
};
union Sonic_I2C Lane1, Lane2;

float duration1 = 0, duration2 = 0;
int distance1 = 0, distance2 = 0;

volatile bool flag1 = false;
volatile bool flag2 = false;

void FlipFlag1( ){  
    flag1 = true;  
}

void set_up_I2C(){
    Wire.begin();
    Wire.setClock(400000);

    Wire.beginTransmission(TrigAddr);
    Wire.write((uint8_t*)&PcfWrite, 2);
    Wire.endTransmission();

    Wire.beginTransmission(EchoAddr);
    Wire.write((uint8_t*)&PcfRead, 2);
    Wire.endTransmission();

    Wire.beginTransmission(PowAddr);
    Wire.write((uint8_t*)&PcfRead, 2);	
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
    Wire.beginTransmission(add);
    Wire.write((uint8_t*)&PcfWrite, 2);
    delayMicroseconds(2);
    Wire.write((uint8_t*)&data, 2);
    delayMicroseconds(10);
    Wire.write((uint8_t*)&PcfWrite, 2);
    Wire.endTransmission();
}

/*
LaneSenNum (uint8_t a) {
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
*/ 
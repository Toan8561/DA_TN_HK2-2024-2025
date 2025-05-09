#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const uint8_t 	IntPin1		= 2;
const uint8_t 	IntPin2		= 3;
const uint16_t  PcfRead     = 0xFFFF;
const uint16_t  PcfWrite    = 0x0000;

uint16_t  test = 0x00001;
uint8_t index = 1;

uint8_t n = 0;

const uint8_t	LcdAddr1    = 0x3E, LcdAddr2    = 0x3F;
LiquidCrystal_I2C lcd1 (LcdAddr1, 20, 4);
LiquidCrystal_I2C lcd2 (LcdAddr2, 20, 4);

const uint8_t   TrigAddr   = 0x27, EchoAddr   = 0x26, PowAddr = 0x25;


float duration = 0;
int distance = 0;

volatile bool flag1 = false;
volatile bool flag2 = false;
volatile unsigned long pulseInTimeBegin ;
volatile unsigned long pulseInTimeEnd ;

void FlipFlag1(){  
    if (digitalRead(IntPin1) == HIGH) {
        pulseInTimeBegin = micros();
    }
    if (digitalRead(IntPin1) == LOW){
        pulseInTimeEnd = micros();
        flag1 = true; 
        detachInterrupt(digitalPinToInterrupt(IntPin1));
    }    
}

void FlipFlag2(){  
    if (digitalRead(IntPin2) == LOW) {
        pulseInTimeBegin = micros();
    }
    else {
        pulseInTimeEnd = micros();
        flag2 = true; 
    }    
}

void set_up_I2C(){

    Wire.begin();
    Wire.setClock(400000UL);


    Wire.beginTransmission(TrigAddr);
    Wire.write((uint8_t*)&PcfWrite, 2);	
    Wire.endTransmission();

    Wire.beginTransmission(EchoAddr);
    Wire.write((uint8_t*)&PcfRead, 2);	
    Wire.endTransmission();
    
    Wire.beginTransmission(PowAddr);
    Wire.write((uint8_t*)&PcfRead, 2);	
    Wire.endTransmission();

    lcd1.init();
    lcd1.backlight();
    lcd2.init();
    lcd2.backlight();

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
    Wire.write( (uint8_t*)&PcfWrite , 2); 
    Wire.write( (uint8_t*)&data , 2);
    Wire.write( (uint8_t*)&PcfWrite , 2);
    Wire.endTransmission();
}

void SonarRead ( uint8_t add ){
    Wire.beginTransmission(add);
    Wire.write(0xFF);
    Wire.endTransmission();
}



/*
 * max7219-digit.c
 *
 *  Created on: Aug 10, 2019
 *      Author: seba
 *      Libreria para el manejo de displays 7 segmentos
 *      con MAX7219
 */

#include "max7219-digits.h"
#include "stm32f1xx_hal.h"

SPI_HandleTypeDef * SPI;
uint8_t maxDevices = 0;
uint8_t spidata[16];

void shutdown(uint8_t addr, bool b) {
    if(addr<0 || addr>=maxDevices)  return;
    b ? (spiTransfer(addr, OP_SHUTDOWN,0)): (spiTransfer(addr, OP_SHUTDOWN,1));
}

void setScanLimit(uint8_t addr, uint8_t limit) {
    if(addr<0 || addr>=maxDevices) return;
    if(limit>=0 && limit<8)  spiTransfer(addr, OP_SCANLIMIT,limit);
}

void setIntensity(uint8_t addr, uint8_t intensity) {
    if(addr<0 || addr>=maxDevices) return;
    if(intensity>=0 && intensity<16) spiTransfer(addr, OP_INTENSITY,intensity);
}

void clearDisplay(uint8_t addr) {
    if(addr<0 || addr>=maxDevices) return;
    for(uint8_t i=0;i<8;i++) {
        spiTransfer(addr, i+1, BLANCK_DIGIT);
    }
}

void setDigit(uint8_t addr, uint8_t digit, uint8_t value, bool dp) {
    if(addr<0 || addr>=maxDevices) return;
    if(digit<0 || digit>7 || value>15) return;
    if(dp) value |= DOT_VALUE;// Set msb;
    spiTransfer(addr, digit+1,value);
}

void spiTransfer(uint8_t addr, volatile uint8_t opcode, volatile uint8_t data) {
    //Create an array with the data to shift out
    uint8_t offset=addr*2;
    uint8_t maxbytes=maxDevices*2;

    //Todo optimizar esto, uso de ram y cpu de mas
    spidata[offset+1]=opcode;
    spidata[offset]=data;
    uint8_t datos [maxbytes];

    //Invertimos el orden de los bytes a mandar
    uint8_t j = 0;
    for(uint8_t i=maxbytes;i>0;i--){
    	datos[j] = spidata[i-1];
    	j++;
    }
    SPI_START();
    HAL_SPI_Transmit((SPI_HandleTypeDef*)(SPI),&datos,maxbytes, 100);
    SPI_STOP();
   }

void config(uint8_t devices, SPI_HandleTypeDef* SPI_Handler){
	maxDevices = devices;
	SPI = SPI_Handler;
    for(int i=0;i<maxDevices;i++) {
        spiTransfer(i,OP_DISPLAYTEST,NO_TETS);
        setScanLimit(i,MAX_LIMIT);
        spiTransfer(i,OP_DECODEMODE, BCD_DECODE); //decode BCD
        clearDisplay(i);
        shutdown(i,true);
    }
}

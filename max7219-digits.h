/*
 * max7219-digits.h
 *
 *  Created on: Aug 10, 2019
 *      Author: seba
 */

#ifndef MAX7219_DIGITS_H_
#define MAX7219_DIGITS_H_
#include "main.h"
#include <stdbool.h>
#include "binary.h"


//Registros MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

//Valores para algunos registros
#define BCD_DECODE 0xFF
#define MAX_LIMIT  0x07
#define NO_TETS    0x00
#define BLANCK_DIGIT 0xF
#define DOT_VALUE 0x80

//Funciones de la libreria
void config(uint8_t, SPI_HandleTypeDef *);
void spiTransfer(uint8_t , volatile uint8_t, volatile uint8_t);
void setDigit(uint8_t, uint8_t, uint8_t, bool);
void clearDisplay(uint8_t);
void setIntensity(uint8_t, uint8_t);
void setScanLimit(uint8_t, uint8_t);
void shutdown(uint8_t, bool);
void shiftOut(uint8_t);

//Cambiar estas macros con los valores correctos del pin CS
#define SPI_START() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define SPI_STOP() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

#endif /* MAX7219_DIGITS_H_ */

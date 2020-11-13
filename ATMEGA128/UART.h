/*
 * UART.h
 *
 * Created: 2020-04-01 오전 9:47:14
 *  Author: DEV-PC
 */ 


#ifndef UART_H_
#define UART_H_




void uartInit();
void transmitByte(unsigned char ch);
uint8_t receiveByte(void);
int printString(char *str);
void readString(char str[], uint8_t maxLength);
uint8_t GetChar(uint8_t *data);
uint8_t GetString(uint8_t *data);
void mode(uint8_t msg);




#endif /* UART_H_ */
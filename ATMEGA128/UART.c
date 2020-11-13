/*
 * UART.c
 *
 * Created: 2020-04-01 오전 9:47:36
 *  Author: DEV-PC
 */ 

#include "..\Board\CPU.h"


#define MY_F_CPU 16000000UL
#define USART_BAUDRATE 9600
#define UBRR_VALUE (((MY_F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define MAX_LENGTH 8

uint32_t	data_Head=0;
uint32_t	data_Tail=0;
uint8_t		data_Buff[MAX_LENGTH]="";


void uartInit()
{
	//3. UBRR0은 16비트 레지스터이기 때문에 8비트씩 나누어서 넣어야 한다.
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
	UBRR0L = (uint8_t) UBRR_VALUE;
	
	//4. USART 설정
	UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01); //Charecter size : 8비트
	UCSR0C &= ~(1<<USBS0); //stop  bit : 1비트
	UCSR0C &= ~((1<<UPM01)|(1<<UPM00)); // no parity mode
	
	//5. 송수신을 가능하게 한다.
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);
}

void transmitByte(unsigned char ch)
{
	
	//이전 전송이 끝나기를 기다림
	while(!(UCSR0A&(1<<UDRE0))){};
	
	UDR0 = ch;                                            /* send data */
}

uint8_t receiveByte(void) 
{
	// 수신 되기를 기다림
	while(!(UCSR0A&(1<<RXC0))){};
	return UDR0;                                /* return register value */
}

int printString(char *str) 
{
	//uint8_t i = 0;
	for (int i=0;str[i];i++)
	{
		transmitByte(str[i]);
	}
	return 0;
}

void readString(char str[], uint8_t maxLength) 
{
	char response;
	uint8_t i;
	i = 0;
	while (i < (maxLength - 1)) {                   /* prevent over-runs */
		response = receiveByte();
		transmitByte(response);                                    /* echo */
		if (response == '\r') {                     /* enter marks the end */
			break;
		}
		else {
			str[i] = response;                       /* add in a letter */
			i++;
		}
	}
	str[i] = 0;                          /* terminal NULL character */
}


void mode(uint8_t msg)
{
	PORTA=0x00;
	switch (msg)
	{
		case '0' :
		printString("SRC1&DET1\n\r");
		PORTA=0x00;
		break;
		case '1' :
		printString("SRC2&DET2\n\r");
		PORTA=0x02;
		break;
		case '2' :
		printString("SRC1&DET3\n\r");
		PORTA=0x01;
		break;
		case '3' :
		printString("SRC2&DET4\n\r");
		PORTA=0x05;
		break;
		case '4' :
		printString("PA2\n\r");
		PORTA=0x04;
		break;
		case '5' :
		printString("PA3\n\r");
		PORTA=0x08;
		break;
		case '6' :
		printString("Reset\n\r");
		PORTA=0x00;
		break;
		default :
		printString("no effect\n\r");
		break;
	}
}

uint8_t GetChar(uint8_t *data)
{
	mode(data);
// 	if(data == '\r')
// 	{
// 		printString("\n\r");
// 		get_msg=data_Buff[data_Tail-1];
// 		data_Tail=0;
// 		return 1;
// 	}
// 	else
// 	{
// 		transmitByte(data);
// 		if(data_Tail>=MAX_LENGTH){printString("\n\r");printString("overlord\n\r");data_Tail=0;}
// 		data_Buff[data_Tail++]=data;
// 
// 		return 0;
// 	}
}

uint8_t GetString(uint8_t *data)
{
	if(data == '\r')
	{		
		printString("\n\r");
		get_msg=data_Buff[data_Tail-1];
		
		printString(get_msg);
		printString("\n\r");

		data_Tail=0;
		return 1;
	}
	else
	{
		transmitByte(data);
		if(data_Tail>=MAX_LENGTH){printString("\n\r");printString("overlord\n\r");data_Tail=0;}
		data_Buff[data_Tail++]=data;

		return 0;
	}
}
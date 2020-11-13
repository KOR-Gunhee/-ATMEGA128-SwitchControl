/*
 * ContRes_FW.c
 *
 * Created: 2020-04-01 오전 9:24:10
 * Author : DEV-PC
 */ 


#include "main.h"


int main(void)
{	
    /* Replace with your application code */
	uartInit();
	PIO_Init();

    while (1) 
    {
		while(!(UCSR0A&(1<<RXC0)));
		{GetChar(receiveByte());};

		
// 		if (GetChar(receiveByte())>0)
// 		{
// 			mode(get_msg);
// 		}
    }
}


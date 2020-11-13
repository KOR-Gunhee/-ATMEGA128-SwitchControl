/*
 * PIO.c
 *
 * Created: 2020-04-07 오전 11:01:50
 *  Author: ghhan
 */ 

#include "..\Board\CPU.h"


void PIO_Init()
{
	//PA0, PA1 포트 출력 설정
	DDRA = 0x0F;
	//PA0, PA1 포트 0V 출력
	PORTA = 0x00;
}
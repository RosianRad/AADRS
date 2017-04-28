/*
===============================================================================
 Name        : AutomaticAccidentDetectionReportingSystem.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "board.h"
#include "chip.h"
#include <cr_section_macros.h>
#include "ADXL345.h"
#include "SIM808.h"
#include "string.h"
#include "AutomaticAccidentDetectionReportingSystem.h"
#include "Functions.h"
#include "math.h"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here
RINGBUFF_T txring, rxring;

float u16ValueX = 0x00, u16ValueY = 0x00, u16ValueZ = 0x00;
char send[30] = "";

int main(void)
{

//	char DataToResend[] = "";
	Init_SSP_PinMux();
	ADXL345_init();
	SIM808_Init();
	ADXL345_WriteReg(LPC_SSP,DATA_FORMAT,0x0B,true);
	ADXL345_WriteReg(LPC_SSP,POWER_CTL,0x30,true);
	ADXL345_WriteReg(LPC_SSP,THRESH_ACT,0x03,true);
	ADXL345_WriteReg(LPC_SSP,THRESH_INACT,0x02,true);
	ADXL345_WriteReg(LPC_SSP,TIME_INACT,0x02,true);
	ADXL345_WriteReg(LPC_SSP,ACT_INACT_CTL,0x70,true);

//	GetGPSPosition();
//	TransformData();
//	SendMessage();
    while(1)
    {
    	u16ValueX = ADXL345_ReadData(DATAX1,DATAX0);
    	u16ValueY = ADXL345_ReadData(DATAY1,DATAY0);
    	u16ValueZ = ADXL345_ReadData(DATAZ1,DATAZ0);

    	float result = sqrt(u16ValueX*u16ValueX + u16ValueY*u16ValueY +u16ValueZ*u16ValueZ );

    	sprintf(send,"Result: %f",result);

    	Chip_UART_SendRB(LPC_USART, &txring, &send, sizeof(send) - 1);

//    	memset(send, "");
//    	Delay_mS(200);
    }

    SIM808_DeInit();
    return 1 ;
}

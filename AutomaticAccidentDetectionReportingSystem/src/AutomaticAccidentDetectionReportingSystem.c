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


// TODO: insert other include files here

// TODO: insert other definitions and declarations here
RINGBUFF_T txring, rxring;

float u16ValueX = 0x00, u16ValueY = 0x00, u16ValueZ = 0x00;

int main(void)
{

//	char DataToResend[] = "";
//	Init_SSP_PinMux();
//	ADXL345_init();
	SIM808_Init();
//	ADXL345_WriteReg(LPC_SSP,DATA_FORMAT,0x0B,true);
//	ADXL345_WriteReg(LPC_SSP,POWER_CTL,0x08,true);
//	u16ValueX = ADXL345_ReadData(DATAX1,DATAX0);
//	u16ValueY = ADXL345_ReadData(DATAY1,DATAY0);
//	u16ValueZ = ADXL345_ReadData(DATAZ1,DATAZ0);

	GetGPSPosition();
    while(1)
    {

    }

    SIM808_DeInit();
    return 1 ;
}

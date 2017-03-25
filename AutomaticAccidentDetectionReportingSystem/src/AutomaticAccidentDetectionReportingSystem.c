/*
===============================================================================
 Name        : AutomaticAccidentDetectionReportingSystem.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include "ADXL345.c"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

float u16ValueX = 0x00, u16ValueY = 0x00, u16ValueZ = 0x00;

int main(void)
{
	Init_SSP_PinMux();
	ADXL345_init();
	ADXL345_WriteReg(LPC_SSP,DATA_FORMAT,0x0B,true);
	ADXL345_WriteReg(LPC_SSP,POWER_CTL,0x08,true);
	u16ValueX = ADXL345_ReadData(DATAX1,DATAX0);
	u16ValueY = ADXL345_ReadData(DATAY1,DATAY0);
	u16ValueZ = ADXL345_ReadData(DATAZ1,DATAZ0);


    while(1)
    {

    }
    return 0 ;
}

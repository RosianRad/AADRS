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
char send[30] = "Incearca";

void PIOINT0_IRQHandler(void)
{
	//	u16ValueX = ADXL345_ReadData(DATAX1,DATAX0);
	//	u16ValueY = ADXL345_ReadData(DATAY1,DATAY0);
	//	u16ValueZ = ADXL345_ReadData(DATAZ1,DATAZ0);
	//
	//	float result = sqrt(u16ValueX*u16ValueX + u16ValueY*u16ValueY +u16ValueZ*u16ValueZ );
	//	sprintf(send,"Result: %f",result);

	//Chip_UART_SendRB(LPC_USART, &txring, &send, sizeof(send) - 1);

	GetGPSPosition();
	TransformData();
	SendMessage();

	Chip_GPIO_ClearInts(LPC_GPIO,0,1 << 6);

}

int main(void)
{

	//	char DataToResend[] = "";
	Chip_GPIO_Init(LPC_GPIO);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,0,6);
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_6,(IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGMODE_EN));
	Chip_GPIO_SetupPinInt(LPC_GPIO, 0, 6, GPIO_INT_RISING_EDGE);
	Chip_GPIO_EnableInt(LPC_GPIO,0,1 << 6);

	Init_SSP_PinMux();
	ADXL345_init();
	SIM808_Init();



	NVIC_EnableIRQ(EINT0_IRQn);

	while(1)
	{


		__WFI();	/* Go to Sleep */

		NVIC_DisableIRQ(EINT0_IRQn);
	}

	SIM808_DeInit();

	return 1 ;

}

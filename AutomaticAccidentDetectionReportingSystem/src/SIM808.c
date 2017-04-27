/*
 * SIM808.c
 *
 *  Created on: Mar 26, 2017
 *      Author: rosian.rad
 */

#include "board.h"
#include "chip.h"
#include "SIM808.h"
#include "Functions.h"
//#include "AutomaticAccidentDetectionReportingSystem.h"

///* Transmit and receive buffers */
//static uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];
//
///* Transmit and receive ring buffers */
GPSRETURN_T GPSReturn;
const char CGPSPWRON[] = "AT+CGPSPWR=1\r";
const char CGPSSTATUS[] = "AT+CGPSSTATUS?\r";
const char CGPSINF[] = "AT+CGPSINF=0\r";
const char CGPSRST[] = "AT+CGPSRST=1\r";
const char CGPSPWROFF[] = "AT+CGPSPWR=0\r";

char GPSReturnString[] = "";
char **GPSReturnVector;

/* Transmit and receive buffers */
static uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

/* Transmit and receive ring buffers */
extern RINGBUFF_T txring, rxring;

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Set pin mux for UART operation */
void Init_UART_PinMux(void)
{
#if (defined(BOARD_NXP_XPRESSO_11U14) || defined(BOARD_NGX_BLUEBOARD_11U24))
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 18, IOCON_FUNC1 | IOCON_MODE_INACT);	/* PIO0_18 used for RXD */
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 19, IOCON_FUNC1 | IOCON_MODE_INACT);	/* PIO0_19 used for TXD */
#elif (defined(BOARD_NXP_XPRESSO_11C24) || defined(BOARD_MCORE48_1125))
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_6, (IOCON_FUNC1 | IOCON_MODE_INACT));/* RXD */
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_7, (IOCON_FUNC1 | IOCON_MODE_INACT));/* TXD */
#else
#error "No Pin muxing defined for UART operation"
#endif
}

void UART_IRQHandler(void)
{
	/* Want to handle any errors? Do it here. */

	/* Use default ring buffer handler. Override this with your own
	   code if you need more capability. */
	Chip_UART_IRQRBHandler(LPC_USART, &rxring, &txring);
}

void SIM808_Init()
{
	SystemCoreClockUpdate();
	Board_Init();
	Init_UART_PinMux();
	Board_LED_Set(0, false);

	/* Setup UART for 115.2K8N1 */
	Chip_UART_Init(LPC_USART);
	Chip_UART_SetBaud(LPC_USART, 115200);
	Chip_UART_ConfigData(LPC_USART, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT));
	Chip_UART_SetupFIFOS(LPC_USART, (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV2));
	Chip_UART_TXEnable(LPC_USART);

	/* Before using the ring buffers, initialize them using the ring
	   buffer init function */
	RingBuffer_Init(&rxring, rxbuff, 1, UART_RRB_SIZE);
	RingBuffer_Init(&txring, txbuff, 1, UART_SRB_SIZE);

	/* Enable receive data and line status interrupt */
	Chip_UART_IntEnable(LPC_USART, (UART_IER_RBRINT | UART_IER_RLSINT));

	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(UART0_IRQn, 1);
	NVIC_EnableIRQ(UART0_IRQn);

	/*Reseting the module*/
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 7, true);
	Delay_mS(10);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 7, false);
	Delay_mS(100);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 7, true);

	/*Wait 7 seconds for the module to start*/
	Delay_mS(7000);
}

void SendGPSSynchronizationMessage()
{
	for(int CountValue = 50;CountValue > 0;CountValue--)
	{
		Chip_UART_SendRB(LPC_USART, &txring, &CGPSSTATUS, sizeof(CGPSSTATUS) - 1);
		Delay_mS(100);
	}
}

void GetGPSPosition()
{
	Chip_UART_SendRB(LPC_USART, &txring, &CGPSPWRON, sizeof(CGPSPWRON) - 1);
	Delay_mS(10);
	Chip_UART_SendRB(LPC_USART, &txring, &CGPSRST, sizeof(CGPSRST) - 1);
	Delay_mS(10);

	while((GPSReturn.Latitude == 0.000000) || (GPSReturn.Longitude == 0.000000))
	{
		SendGPSSynchronizationMessage();
		Chip_UART_SendRB(LPC_USART, &txring, &CGPSINF, sizeof(CGPSINF) - 1);
		Chip_UART_ReadRB(LPC_USART, &rxring, &GPSReturnString, 128);
		SeparateReturnedString(GPSReturnString,&GPSReturnVector);
		GPSReturn.Latitude = atof(GPSReturnVector[1]);
		GPSReturn.Longitude = atof(GPSReturnVector[2]);
	}
}

void SIM808_DeInit()
{
	NVIC_DisableIRQ(UART0_IRQn);
	Chip_UART_DeInit(LPC_USART);
}

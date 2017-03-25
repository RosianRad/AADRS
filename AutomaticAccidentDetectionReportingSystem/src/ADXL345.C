/*
 * ADXL345.C
 *
 *  Created on: Jan 3, 2017
 *      Author: rosian.rad
 */

#include "board.h"
#include "chip.h"
#include "ADXL345.h"

static SSP_ConfigFormat ssp_format;

//static Chip_SSP_DATA_SETUP_T xf_setup;

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Set pin mux for SSP operation */
void Init_SSP_PinMux(void)
{

#if defined(BOARD_NXP_XPRESSO_11C24)
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_8, (IOCON_FUNC1 | IOCON_MODE_INACT));	/* MISO0 */
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_9, (IOCON_FUNC1 | IOCON_MODE_INACT));	/* MOSI0 */
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_2, (IOCON_FUNC1 | IOCON_MODE_INACT));	/* SSEL0 */
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO2_11, (IOCON_FUNC1 | IOCON_MODE_INACT));	/* SCK0 */
	Chip_IOCON_PinLocSel(LPC_IOCON, IOCON_SCKLOC_PIO2_11);
#else
	#error "SSP Pin muxing not configured"
#endif
}

/* ADXL345 initialization */
void ADXL345_init()
{
	SystemCoreClockUpdate();
	Board_Init();
	Init_SSP_PinMux();
	Chip_SSP_Init(LPC_SSP);
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI;
    ssp_format.bits = SSP_DATA_BITS;
    ssp_format.clockMode = SSP_CLOCK_MODE3;
	Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);
	Chip_SSP_SetMaster(LPC_SSP, SSP_MODE_TEST);
	Chip_SSP_Enable(LPC_SSP);

	ADXL345_WriteReg(LPC_SSP,OFSX,-3,true);
	ADXL345_WriteReg(LPC_SSP,OFSY,-2,true);
	ADXL345_WriteReg(LPC_SSP,OFSZ,-4,true);

}

/* ADXL345 writing to register; TRUE-with MB; FALSE-without MB */
void ADXL345_WriteReg(LPC_SSP_T *pSSP,uint8_t ADXL345_register,int8_t value_to_ADXL345,bool choose_MB)
{

	if(choose_MB == true)
	{
		ADXL345_register = ADXL345_register | WRITE_MB;
	}
	else
	{
		ADXL345_register = ADXL345_register | WRITE;
	}

//
//	Chip_SSP_WriteFrames_Blocking(pSSP, &ADXL345_register, 1);
//	Chip_SSP_WriteFrames_Blocking(pSSP, &value_to_ADXL345, 1);
	uint32_t tx_cnt = 0, rx_cnt = 0;
	uint8_t wdata8[2] = {ADXL345_register,value_to_ADXL345};

	while (tx_cnt < 2 || rx_cnt < 2) {
		/* write data to buffer */
		if ((Chip_SSP_GetStatus(pSSP, SSP_STAT_TNF) == SET) && (tx_cnt < 2)) {
			Chip_SSP_SendFrame(pSSP, wdata8[tx_cnt]);
			tx_cnt++;
		}

		/* Check for any data available in RX FIFO */
		while (Chip_SSP_GetStatus(pSSP, SSP_STAT_RNE) == SET && rx_cnt < 2) {
			Chip_SSP_ReceiveFrame(pSSP);	/* read dummy data */
			rx_cnt++;
		}
	}

}

uint8_t ADXL345_ReadReg(LPC_SSP_T *pSSP,uint8_t ADXL345_register,bool choose_MB)
{

	if(choose_MB == true)
	{
		ADXL345_register = ADXL345_register | READ_MB;
	}
	else
	{
		ADXL345_register = ADXL345_register | READ;
	}


	uint8_t rdata8;

	 Chip_SSP_WriteFrames_Blocking(pSSP, &ADXL345_register, 2);
	 Chip_SSP_ReadFrames_Blocking(pSSP, &rdata8, 1);


	return rdata8;
}
float ADXL345_ReadData(uint8_t u8data1,uint8_t u8data0){	int16_t u16ReadResult = 0;
	float u16ReadResult1G = 0;	uint8_t u8ValueMSB = 0;	uint8_t u8ValueLSB = 0;	u8ValueMSB = ADXL345_ReadReg(LPC_SSP,u8data1,true);	u8ValueLSB = ADXL345_ReadReg(LPC_SSP,u8data0,true);	u16ReadResult = (u8ValueMSB << 0x08) | u8ValueLSB;
	u16ReadResult1G = (float)u16ReadResult * 0.00390625;	return u16ReadResult1G;}

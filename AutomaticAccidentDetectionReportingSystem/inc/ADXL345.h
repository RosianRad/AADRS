/*
 * ADXL345.h
 *
 *  Created on: Jan 3, 2017
 *      Author: rosian.rad
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#define LPC_SSP           LPC_SSP0
#define LOOPBACK_TEST       0
#define SSP_MODE_TEST       1	/*1: Master, 0: Slave */
#define POLLING_MODE        1
#define SSP_DATA_BITS     (SSP_BITS_8)

/* Registers definition */
#define DEVID            (0x00)  /*Device ID */
#define THRESH_TAP       (0x1D)  /*Tap threshold */
#define OFSX             (0x1E)  /*X-axis offset */
#define OFSY             (0x1F)  /*Y-axis offset */
#define OFSZ             (0x20)  /*Z-axis offset */
#define DUR              (0x21)  /*Tap duration */
#define LATENT           (0x22)  /*Tap latency */
#define WINDOW           (0x23)  /*Window latency */
#define THRESH_ACT       (0x24)  /*Activity threshold */
#define THRESH_INACT     (0x25)  /*Inactivity threshold */
#define TIME_INACT       (0x26)  /*Inactivity time */
#define ACT_INACT_CTL    (0x27)  /*Axis enable control for activity and inactivity detection */
#define THRESH_FF        (0x28)  /*Free-fall threshold */
#define TIME_FF          (0x29)  /*Free-fall time */
#define TAP_AXES         (0x2A)  /*Axis control for single tap/double tap */
#define ACT_TAP_STATUS   (0x2B)  /*Source of single tap/double tap */
#define BW_RATE          (0x2C)  /*Data rate and power mode control */
#define POWER_CTL        (0x2D)  /*Power-saving features control */
#define INT_ENABLE       (0x2E)  /*Interrupt enable control */
#define INT_MAP          (0x2F)  /*Interrupt mapping control */
#define INT_SOURCE       (0x30)  /*Source of interrupts */
#define DATA_FORMAT      (0x31)  /*Data format control */
#define DATAX0           (0x32)  /*X-Axis Data 0 */
#define DATAX1           (0x33)  /*X-Axis Data 1 */
#define DATAY0           (0x34)  /*Y-Axis Data 0 */
#define DATAY1           (0x35)  /*Y-Axis Data 1 */
#define DATAZ0           (0x36)  /*Z-Axis Data 0 */
#define DATAZ1           (0x37)  /*Z-Axis Data 1 */
#define FIFO_CTL         (0x38)  /*FIFO control */
#define FIFO_STATUS      (0x39)  /*FIFO status */

/*Modes definition*/
#define READ             (0x80)  /*SPI 4-Wire Read */
#define READ_MB          (0xC0)  /*SPI 4-Wire Read with multiple-byte */
#define WRITE            (0x00)  /*SPI 4-Wire Write */
#define WRITE_MB         (0x40)  /*SPI 4-Wire Write with multiple-byte */

/*Functions definition*/
void Init_SSP_PinMux(void);                                                                                 /*Set pin mux for SSP operation */
void ADXL345_init(void);                                                                                    /*ADXL345 initialization */
void ADXL345_WriteReg(LPC_SSP_T *pSSP,uint8_t ADXL345_register,int8_t value_to_ADXL345,bool choose_MB);    /*ADXL345 writing to register; TRUE-with MB; FALSE-without MB */
uint8_t ADXL345_ReadReg(LPC_SSP_T *pSSP,uint8_t ADXL345_register,bool choose_MB);                           /*ADXL345 reading from register; TRUE-with MB; FALSE-without MB */
float ADXL345_ReadData(uint8_t data1,uint8_t data0);                                                                                                       /*ADXL345 reading axis data */

#endif /* ADXL345_H_ */

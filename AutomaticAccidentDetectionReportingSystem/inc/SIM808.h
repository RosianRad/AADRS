/*
 * SIM808.h
 *
 *  Created on: Mar 26, 2017
 *      Author: rosian.rad
 */

#ifndef SIM808_H_
#define SIM808_H_



/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 128	/* Send */
#define UART_RRB_SIZE 128	/* Receive */

typedef struct
{
	float Latitude;
	float Longitude;
	float Altitude;
} GPSRETURN_T;

//const char CGPSPWRON[] = "AT+CGPSPWR=1\r";
//const char CGPSSTATUS[] = "AT+CGPSSTATUS?\r";
//const char CGPSINF[] = "AT+CGPSINF=0\r";
//const char CGPSRST[] = "AT+CGPSRST=1\r";
//const char CGPSPWROFF[] = "AT+CGPSPWR=0\r";


void Init_UART_PinMux(void);
void SIM808_Init(void);
void SIM808_DeInit(void);
void SendGPSSynchronizationMessage(void);
void GetGPSPosition(void);

#endif /* SIM808_H_ */

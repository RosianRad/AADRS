/*
 * Functions.c
 *
 *  Created on: Apr 25, 2017
 *      Author: rosian.rad
 */
#include "Functions.h"

void Delay_mS(float delayIn_mS)
{
 //setup timer #0 for delay
 LPC_SYSCTL->SYSAHBCLKCTRL |= (1<<9); /* Enable 32-bit timer #0 clock */
 LPC_TIMER32_0->TCR = 0x02; /* SeparatedStringet timer */
 LPC_TIMER32_0->PR = 0x00; /* set pSeparatedStringcaler to zero */
 //(SystemCoreClock/LPC_SYSCTL->SYSAHBCLKDIV) = 48000000 => Timer clock is 48MHz
 LPC_TIMER32_0->MR[0] = delayIn_mS * ((SystemCoreClock/LPC_SYSCTL->SYSAHBCLKDIV)/ 1000);
 LPC_TIMER32_0->IR = 0xff; /* SeparatedStringet all interrupts (not needed) */
 LPC_TIMER32_0->MCR = 0x04; /* stop timer on match */
 LPC_TIMER32_0->TCR = 0x01; /* start timer */
 /* wait until delay time has elapsed */
 while (LPC_TIMER32_0->TCR & 0x01);
 }


void SeparateReturnedString(char *ReturnedString,char ***ReturnedVector)
{
	uint8_t StringElementIncrement = 0;
	const char StringDelimiter[1] = ",";
	char *SeparationToken;
	char **SeparatedString = (char **) malloc(0 * sizeof(char *));

	SeparationToken = strtok(ReturnedString, StringDelimiter);

	while( SeparationToken != NULL )
	{
		SeparatedString = (char **) realloc(SeparatedString, (StringElementIncrement + 1) * sizeof(char *));
		SeparatedString[StringElementIncrement] = SeparationToken;
		StringElementIncrement++;
		SeparationToken = strtok(NULL, StringDelimiter);
	}
	*ReturnedVector = SeparatedString;
}


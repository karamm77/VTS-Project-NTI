/**
 * @file GPS_Program.c
 * @author Mohamed Dwedar (MohamedDwedar@gmail.com)
 * @brief Implement GPS Driver
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Bit_Math.h"
#include "Std_Types.h"

#include "USART_interface.h"

#include "GPS_Interface.h"
#include "GPS_Private.h"


/********** Function Implementation Start *************/

/**
 * @brief GPS Initialization
 * 
 */

u8 GPS_Complete_FRAME = 0;
void GPS_Init(void)
{
	/* write the frame name in string to copy it into Buffer */
	u8  GPS_FRAME[5] = (FRAME);
	for (u8 i = 0; i < 5; i++)
	{
		GPS_Buffer[i] = GPS_FRAME[i];
	}
	/* Call The GPS_Recieve_Buffer When Receiving Data */
	UART2_RX_CALLBACK(GPS_Recieve_Buffer);
}


/**
 * @brief GPS Decode Data
 * 
 * @param RMC Buffer Where Data Decoded
 */
void GPS_Decode_Buffer_st(GPS_RMC_ST * RMC)
{
	/*Pharse_count to count ','*/
	u8 pharse_count = 0;
	/*Pharse_count to count splitted frame foe each specified*/
	u8 frame_count = 0;
	/*Check for all frame*/
	for (u8 i = 0; i < 100; i++)
	{
		/*Count num of ','*/
		if (GPS_Buffer[i] == ',')
		{
			pharse_count++;
			i++;
			frame_count = 0;
		}
		/*
		Pharse_count = 1 -> Time
		Pharse_count = 3 -> latitude
		Pharse_count = 5 -> longitude
		Pharse_count = 9 -> date
		*/
		if(pharse_count == 1 && GPS_Buffer[i] != ',')
		{
			RMC->UTC_Time[frame_count] = GPS_Buffer[i];
			frame_count++;
		}
		if(pharse_count == 3 && GPS_Buffer[i] != ',')
		{
			RMC->Latitude[frame_count] = GPS_Buffer[i];
			frame_count++;
		}
		if(pharse_count == 5 && GPS_Buffer[i] != ',')
		{
			RMC->Longitude[frame_count] = GPS_Buffer[i];
			frame_count++;
		}
		if(pharse_count == 9 && GPS_Buffer[i] != ',')
		{
			RMC->Date[frame_count] = GPS_Buffer[i];
			frame_count++;
		}
	}
}

/********** Function Implementation End *************/


/********** Static Function Implementation Start ******/

/**
 * @brief GPS Recive from UART
 * 
 */
void static GPS_Recieve_Buffer(void)
{
	/* count refers to location where writing in buffer */
	u8 static count = 0;
	/* GPS_TRUE_FRAME = 1 when indicate that I have received desired frame */
	u8 static GPS_TRUE_FRAME = 0;

	/* Receive UART Data */
	u8 GPS_Char = UART2_RXdata();

	/*check for start of new frame*/
	if (GPS_Char == '$')
	{
		/* Start of Frame */
		count = 0;
		/* assume that you in write frame */
		GPS_TRUE_FRAME = 1;
	}
	/* Check for frame */
	else if (count < 5 && GPS_TRUE_FRAME)
	{
		if (GPS_Char != GPS_Buffer[count])
		{
			/* if Frame not desired make flag = 0 */
			GPS_TRUE_FRAME = 0;
		}
		count++;
	}
	/*continue Receiving Frame if true*/
	else if ((count >= 5) && (GPS_TRUE_FRAME == 1))
	{
		GPS_Buffer[count] = GPS_Char;
		count++;
	}
	/* Detect the end of frame*/
	if ((GPS_Char == '\r') && (GPS_TRUE_FRAME == 1))
	{
		GPS_TRUE_FRAME = 0;
		GPS_Complete_FRAME = 1;
	}
}
/********** Static Function Implementation End ********/

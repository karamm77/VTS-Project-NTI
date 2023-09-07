/**
 * @file main.c
 * @author Mohamed Dwedar (MohamedDwedar@gmail.com)
 * @brief Main Function To test GPS Performance ON TTL
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Std_Types.h"
#include "Bit_Math.h"
#include "Common_Function.h"

#include "DIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "USART_interface.h"
#include "GPS_Interface.h"
#include "GSM_Interface.h"



GPS_RMC_ST RMC;

/**
 * @brief Main APP
 * 
 * @return int 
 */
int main(void)
{
	/*RCC*/
	RCC_voidSysClkInt();// Initailize Clock of The system
	RCC_voidEnablePerClk(RCC_APB1,RCC_APB1_USART2);// Enable USART1 RCC
	RCC_voidEnablePerClk(RCC_APB2, RCC_APB2_AFIO); // Enable Alternate function RCC
	RCC_voidEnablePerClk(RCC_APB2, RCC_APB2_DIOA); // Enable GPIOA RCC

	/*UART1*/
	UART1_init();     //Initialize UART
	UART1_enableTX(); //Enable Sending
	UART1_enableRX(); //Enable Recieving
	DIO_voidSetPinDirection(PORTA, PIN9, GPIO_OUTPUT_10MHZ_AFPP);//uart pint tx
	DIO_voidSetPinDirection(PORTA, PIN10, GPIO_INPUT_FLOAT);//uart pin rx

	/*UART2*/
	UART2_init();     //Initialize UART
	UART2_enableTX(); //Enable Sending
	UART2_enableRX(); //Enable Recieving
	DIO_voidSetPinDirection(PORTA, PIN2, GPIO_OUTPUT_10MHZ_AFPP);//uart pint tx
	DIO_voidSetPinDirection(PORTA, PIN3, GPIO_INPUT_FLOAT);//uart pin rx

	/*NVIC UART2*/
	NVIC_voidInit();
	NVIC_voidEnablePerInt(38);
	NVIC_voidSetSwIntPriority(38, 0b1100);
	NVIC_voidEnablePerInt(38);

	GSM_INIT(); //GSM Initialization
	char GSM_Buffer[20];//Buffer

	GPS_Init();
	GPS_RMC_ST RMC;
	/*super loope*/
	while(1)
	{
		// Send data to server every 10 sec
		if (GPS_Complete_FRAME == 1)
		{
			GPS_Decode_Buffer_st(&RMC);
			GSM_Post("Longitude",RMC.Longitude, GSM_Buffer);
			GSM_Post("Longitude",RMC.Latitude, GSM_Buffer);
			GPS_Complete_FRAME = 0;
			_delay_ms(10000);
		}
	}
}
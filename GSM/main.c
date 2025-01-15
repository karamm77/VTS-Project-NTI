/**
 * @file main.c
 * @author Karam Albendary
 * @brief Main to Test GSM Module
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Std_Types.h"
#include "Bit_Math.h"
#include "Common_Function.h"

#include "GSM_Interface.h"
#include "DIO_interface.h"
#include "RCC_interface.h"
#include "USART_interface.h"




/**
 * @brief main Fuction
 * 
 * @return int 
 */
int main(void)
{
	/*RCC*/
	RCC_voidSysClkInt();// Initailize Clock of The system
	RCC_voidEnablePerClk(RCC_APB2,RCC_APB2_USART1);// Enable USART1 RCC
	RCC_voidEnablePerClk(RCC_APB2, RCC_APB2_AFIO); // Enable Alternate function RCC
	RCC_voidEnablePerClk(RCC_APB2, RCC_APB2_DIOA); // Enable GPIOA RCC


	/*UART1*/
	UART1_init();     //Initialize UART
	UART1_enableTX(); //Enable Sending
	UART1_enableRX(); //Enable Recieving
	DIO_voidSetPinDirection(PORTA, PIN9, GPIO_OUTPUT_10MHZ_AFPP);//uart pint tx
	DIO_voidSetPinDirection(PORTA, PIN10, GPIO_INPUT_FLOAT);//uart pin rx

	/*GSM*/
	GSM_INIT(); //GSM Initialization
	char GSM_Buffer[100];//Buffer
	char type[10];// Type Test
	char data[10];// data Test
	u8 Event= 1;// event trigger one time
	GSM_Post(type, data, GSM_Buffer);//Post data to server
	GSM_MakeCall();// Call The Car Owner
	GSM_SendSMS("Warning Car is Moving");// Send Message to car owner
	/*super loope*/
	while(1)
	{
		GSM_Post(type, data, GSM_Buffer);//Post data to server

		if (Event == 1) //flag for module testing
		{
			GSM_MakeCall();// Call The Car Owner
			GSM_SendSMS("Warning Car is Moving");// Send Message to car owner
			Event = 0; // Make event = 0
		}
	}
}

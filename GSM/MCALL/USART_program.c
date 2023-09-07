/**
 * @file USART_program.c
 * @author Mohamed Dwedar (MohamedDwedar2699@gmail.com)
 * @brief USART Driver Implementation
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Std_Types.h"
#include "Bit_Math.h"

#include "USART_config.h"
#include "USART_interface.h"
#include "USART_private.h"



/**
 * @brief Initialized UART
 * 
 */
void UART1_init(void) {
	// set Baud rate
	USART1 -> BRR = USART1_BAUDRATE;
	// Enable RXNEIE
	//USART1 -> CR1 = 1 << RXNEIE;
	// enable transmission complete interrupt
	//USART1 -> CR1 = 1 << TCIE;
	// USART1 -> CR1 = 1 << TXEIE;
#if USART1_PARITY == PARITY_NO
	USART1 -> CR1 |= 1 << PCE;
#if USART1_PARITY_TYPE == PARITY_ODD
	USART1 -> CR1 |= 1 << PS;
#endif
#endif
	USART1 -> CR1 |= USART1_DATA_LENGTH << M;
	USART1 -> CR2 |= USART1_STOP_LENGTH << STOP;
	USART1 -> CR1 |= 1 << UE;
}
/**
 * @brief Enable Data Transmition
 * 
 */
void UART1_enableTX(void) {
	USART1 -> CR1 |= 1 << TE;
}
/**
 * @brief Enable data Recieve
 * 
 */
void UART1_enableRX(void) {
	USART1 -> CR1 |= 1 << RE;
}

/**
 * @brief Transmint Data
 * 
 * @param data data to be transmitter
 */
void UART1_TXdata(u32 data){
//	 while(!get_bit(UCSRA,UCSRA_UDRE)) ;
//	 UDR = data ;
	while(!GET_BIT(USART1->SR,7));
	USART1->DR = data ;
	while (!GET_BIT(USART1->SR,6));
}

/**
 * @brief Recieve Data
 * 
 * @return u32 Data to be recieverd
 */
u32 UART1_RXdata (void) {
//	while(!get_bit(UCSRA ,UCSRA_RXC)) ;
//	*data = UDR ;
	u32 data = 0;
	//while (!GET_BIT(USART1 -> SR , 5));
	if (GET_BIT(USART1 -> SR, 5))
	{
			data = USART1 -> DR;
	}
	USART1 -> DR = 0;
	return data;
}

/**
 * @brief Send String
 * 
 * @param str 
 */
void UART1_voidSendString(char const * str)
{
	u16 buffer = 0;
	while (str[buffer] != '\0')
	{
		UART1_TXdata(str[buffer]);
		buffer++;
	}
}

/**
 * @brief recieve string
 * 
 * @return u8* const 
 */
u8 * const UART1_StrReceiveString(void)
{
	u8 buffer = 0;
	u8 static data[30];
	while (data[buffer] != '\0')
	{
		data[buffer] = UART1_RXdata();
		buffer++;
	}
	return data;
}

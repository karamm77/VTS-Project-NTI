/**
 * @file USART_interface.h
 * @author Mohamed Dwedar (MohamedDwedar2699@gmail.com)
 * @brief APIs and Global data
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

 void UART1_init(void);
 void UART1_enableTX(void);
 void UART1_enableRX(void);
 void UART1_TXdata(u32 data);
 u32 UART1_RXdata (void);
 void UART1_voidSendString(char const * str);
 u8 * const UART1_StrReceiveString(void);
#endif

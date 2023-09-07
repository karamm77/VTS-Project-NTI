/**
 * @file NVIC_interface.h
 * @author Mohamed Dwedar (MohamedDwedar@gmail.com)
 * @brief NVIC APIs and Global data
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef		NVIC_INTERFACE_H
#define		NVIC_INTERFACE_H

void		NVIC_voidInit();

void		NVIC_voidEnablePerInt(u8 IntNum);
void		NVIC_voidDisablePerInt(u8 IntNum);

void		NVIC_voidSetPendingFlag(u8 IntNum);
void		NVIC_voidClrPendingFlag(u8 IntNum);

u8			NVIC_u8ReadActiveFlag(u8 IntNum);

void		NVIC_voidSetSwIntPriority(u8 IntNum , u8 priority);

#endif

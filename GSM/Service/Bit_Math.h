/**
 * @file Bit_Math.h
 * @author your name (you@domain.com)
 * @brief used to control bits
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef		BIT_MATH_H
#define		BIT_MATH_H

#define		SET_BIT(REG,BIT)		(REG|=  (1<<BIT))
#define		CLR_BIT(REG,BIT)		(REG&= ~(1<<BIT))
#define		TOG_BIT(REG,BIT)		(REG^=  (1<<BIT))
#define		GET_BIT(REG,BIT)		((REG>>BIT)&0x01)

//#define		BIT_LOW					((u8)0)

#endif
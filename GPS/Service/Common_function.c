/**
 * @file Common_function.c
 * @author Mohamed Dwedar (MohamedDwedar@gmail.com)
 * @brief Helper Fucntions
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Common_Function.h"

/**
 * @brief This Function is used to delay the task 
 * 
 * @param ticks number of ms to wait
 */
void	_delay_ms(u32 ticks){
	u32 i;
	for( i = 0; i < (ticks * 500) ; i++)
	{
		asm("NOP");
	}
}

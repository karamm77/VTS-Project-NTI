/**
 * @file DIO_program.c
 * @author Karam Albendary
 * @brief DIO Implementaiton
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include	"Std_Types.h"
#include	"Bit_Math.h"

#include	"DIO_interface.h"

//#include	"DIO_config.h"




/**
 * @brief Set Direction of DIO
 * 
 * @param port 
 * @param pin 
 * @param Direction 
 */
void	DIO_voidSetPinDirection(u8 port, u8 pin, u8 Direction)
{
	/*		Range Check 		*/
	if(port < 3 && pin < 16)
	{
		if(pin<8)	/*		Low	(PIN0:PIN7) CRL	*/
		{
			switch(port)
			{
				case	PORTA	:
				/*		Clear the 4 bits before writing		*/
				GPIOA_CRL &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
				GPIOA_CRL |=  ((Direction)<<(pin * 4));
				break;

				case	PORTB	:
				/*		Clear the 4 bits before writing		*/
				GPIOB_CRL &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
				GPIOB_CRL |=  ((Direction)<<(pin * 4));
				break;

				case	PORTC	:
				/*		Clear the 4 bits before writing		*/
				GPIOC_CRL &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
				GPIOC_CRL |=  ((Direction)<<(pin * 4));
				break;
			}
		}else if(pin<16)	/*		Low	(PIN8:PIN15) CRL	*/
		{
			pin -= 8;
			switch(port)
			{
				case	PORTA	:
				/*		Clear the 4 bits before writing		*/
				GPIOA_CRH &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
				GPIOA_CRH |=  ((Direction)<<(pin * 4));
				break;

				case	PORTB	:
				/*		Clear the 4 bits before writing		*/
				GPIOB_CRH &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
				GPIOB_CRH |=  ((Direction)<<(pin * 4));
				break;

				case	PORTC	:
				/*		Clear the 4 bits before writing		*/
				GPIOC_CRH &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
				GPIOC_CRH |=  ((Direction)<<(pin * 4));
				break;
			}

		}
	}else{/*	Return Error	*/}
}

/**
 * @brief Set PIN Value
 * 
 * @param port 
 * @param pin 
 * @param Value 
 */
void	DIO_voidSetPinValue(u8 port, u8 pin, u8 Value)
{
	/*		Range Check 		*/
	if(port < 3 && pin < 16)
	{
		if(Value == GPIO_HIGH)
		{
			switch(port)
			{
				case	PORTA	:	GPIOA_BSRR=(1<<pin)    ;	break;
				case	PORTB	:	GPIOB_BSRR=(1<<pin);	break;
				case	PORTC	:	GPIOC_BSRR=(1<<pin);	break;
			}
		}
		else if(Value == GPIO_LOW)
		{
			switch(port)
			{
				case	PORTA	:	GPIOA_BRR=(1<<pin);	break;
				case	PORTB	:	GPIOB_BRR=(1<<pin);	break;
				case	PORTC	:	GPIOC_BRR=(1<<pin);	break;
			}
		}

	}else{/*	Return Error	*/}

}

/**
 * @brief Toggle PIN State
 * 
 * @param port 
 * @param pin 
 */
void	DIO_voidtogglepin (u8 port,u8 pin){
	if(port < 3 && pin < 16)
	{
		
			switch(port)
			{
				case	PORTA	:	GPIOA_ODR^=(1<<pin);	break;
				case	PORTB	:	GPIOB_ODR^=(1<<pin);	break;
				case	PORTC	:	GPIOC_ODR^=(1<<pin);	break;
			}
		}
		
	
	
}

/**
 * @brief return PIN State
 * 
 * @param port 
 * @param pin 
 * @return u8 
 */
u8		DIO_u8GetPinValue(u8 port, u8 pin)
{
	/*		Range Check 		*/
	u8	Local_u8Val = 0x99;
	if(port < 3 && pin < 16)
	{

			switch(port)
			{
				case	PORTA	:	Local_u8Val	=	GET_BIT(GPIOA_IDR,pin);	break;
				case	PORTB	:	Local_u8Val	=	GET_BIT(GPIOB_IDR,pin);	break;
				case	PORTC	:	Local_u8Val	=	GET_BIT(GPIOC_IDR,pin);	break;
			}
	}else{/*	Return Error	*/}
	return Local_u8Val ;
}

/**
 * @brief write value on PORT
 * 
 * @param port 
 * @param startpin 
 * @param data 
 */
void DIO_voidWriteValue(u8 port,u8 startpin,u8 data)
{
    switch(port)
    {
    case PORTA:
        GPIOA_BRR = 0xff << startpin;
        GPIOA_BSRR = data << startpin;
        break;
    case PORTB:
        GPIOB_BRR = 0xff << startpin;
        GPIOB_BSRR = data << startpin;
        break;
    }
}

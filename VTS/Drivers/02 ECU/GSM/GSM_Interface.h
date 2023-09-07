/**
 * @file GSM_Interface.h
 * @author Mohamed Dwedar (MohamedDwedar2699@gmail.com)
 * @brief GSM APIs and Global Functions
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef GSM_INTERFACE_H_
#define GSM_INTERFACE_H_

/********* APIs Section Start ********/
void GSM_INIT(void);
void GSM_Post(char const * type,char const * data, char * buffer);
void GSM_MakeCall(void);
void GSM_SendSMS(char const * SMS);
/********* APIs Section End ********/


#endif /* GSM_INTERFACE_H_ */

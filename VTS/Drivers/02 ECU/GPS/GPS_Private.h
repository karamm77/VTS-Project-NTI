/**
 * @file GPS_Private.h
 * @author Mohamed Dwedar (MohamedDwedar@gmail.com)
 * @brief GPS Private Data
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GPS_CONFIG_H_
#define GPS_CONFIG_H_

/******** Static Variable Definition Start *******/
u8 static GPS_Buffer[Buffer_size];
/******** Static Variable Definition End *******/


/******** Private APIs  Start *******/
void static GPS_Recieve_Buffer(void);
/******** Private APIs  End *******/


#endif /* GPS_CONFIG_H_ */
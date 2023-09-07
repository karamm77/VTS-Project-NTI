/**
 * @file GSM_Private.h
 * @author Mohamed Dwedar (MohamedDwedar2699@gmail.com)
 * @brief Private Data of GSM Module
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GSM_PRIVATE_H_
#define GSM_PRIVATE_H_

/********* Define Section Start ***************/
#define CALL_CONC "ATD" NUMBER "\r\n"
#define SMS_CONC "AT+CMGS=\"" NUMBER ";\r\n"
#define URL_CONC "AT+HTTPPARA=\"URL\",\"" URL "\"\r\n"
/********* Define Section End ***************/

/********* Private APIs Section Start ********/
void static waitforok(void);
void static waitforDOWNLOAD(void);
void static waitforHTTPACTION(void);
void static GSM_INIT_GPRS_MODE(void);
void static GSM_Init_HTTP(void);
void static GSM_AdjustData_Json(void);
void static PlainToJSON(char const * type,char const * data, char  * buffer);
void static SMS_INIT(void);
/********* Private APIs Section End ********/

#define CALL_CONC "ATD" NUMBER "\r\n"
#define SMS_CONC "AT+CMGS=\"" NUMBER ";\r\n"
#define URL_CONC "AT+HTTPPARA=\"URL\",\"" URL "\"\r\n"

#endif /* GSM_PRIVATE_H_ */

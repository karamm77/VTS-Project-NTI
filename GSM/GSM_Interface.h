


#ifndef GSM_INTERFACE_H_
#define GSM_INTERFACE_H_

/********* APIs Section Start ********/
void GSM_INIT(void);
void GSM_Post(char const * type,char const * data, char * buffer);
void GSM_MakeCall(void);
void GSM_SendSMS(char const * SMS);
/********* APIs Section End ********/


#endif /* GSM_INTERFACE_H_ */

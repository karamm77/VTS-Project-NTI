/**
 * @file GPS_Interface.h
 * @author Mohamed Dwedar (MohamedDwedar@gmail.com)
 * @brief GPS APIs and Global data
 * @version 0.1
 * @date 2023-08-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GPS_INTERFACE_H_
#define GPS_INTERFACE_H_




/******** Define Section Start ******/
/* Size of Buffer That Receive the Data*/
#define Buffer_size 70
/* Name of Desired Frame */
#define FRAME       "GPRMC"
/******** Define Section end   ******/


/******** Typedef Section Start *****/
typedef struct GPS_RMC{
	u8 UTC_Time[10];
	u8 Latitude[10];
	u8 Longitude[10];
	u8 Date[6];
	}GPS_RMC_ST;
	
/******** Typedef Section End *****/

/******** Flag Section Start ******/
/* That indicate That Frame is available to use*/
u8 extern GPS_Complete_FRAME;
/******** Flag Section End ******/



/********* APIs Section Start ********/
void GPS_Init(void);
void GPS_Decode_Buffer(u8  * longitude, u8 * latidude);
void GPS_Decode_Buffer_st(GPS_RMC_ST * RMC);
/********* APIs Section End ********/


#endif /* GPS_INTERFACE_H_ */

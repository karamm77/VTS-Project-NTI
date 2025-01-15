

#include "Bit_Math.h"
#include "Std_Types.h"

#include "USART_interface.h"
#include "Common_Function.h"

#include "GSM_Config.h"
#include "GSM_Private.h"
#include "GSM_Interface.h"




/********** Fucntion Implementation Start *************/

/**
 * @brief Initialization Of GSM
 * 
 */
void GSM_INIT(void)
{
	/*Start */
	UART1_voidSendString("ATE0\r\n");//Stop typing reply
	waitforok();//wait for response

	/*Initialization of  SMS */
	SMS_INIT();

	/*Initialization of GPRS*/
	GSM_INIT_GPRS_MODE();
	/*Initialization of HTTP*/
	GSM_Init_HTTP();
	/*Configure data as Json*/
	GSM_AdjustData_Json();
}

/**
 * @brief GSM Send Data to Server
 * 
 * @param type Type of data to send
 * @param data data to send
 * @param buffer Buffer to send data from it
 */
void GSM_Post(char const * type,char const * data, char * buffer)
{
	/*convert data to json*/
	PlainToJSON(type,data,buffer);

	UART1_voidSendString("AT+HTTPDATA=100,2000\r\n");//Start data Input
	waitforDOWNLOAD();// wait for download
	UART1_voidSendString(buffer);// write buffer after update
	waitforok();// wait for ok
	UART1_voidSendString("AT+HTTPACTION=1\r\n");// start transmission
	waitforHTTPACTION();//wait for HTTPACTION With timeout

}

/**
 * @brief Make A CAll to configured Numbed
 * 
 */
void GSM_MakeCall(void)
{
	/*Start The Call*/
	UART1_voidSendString(CALL_CONC);//Start the Call (configuerd in GSM_Config.h file)
	waitforok();// wait for ok
}

/**
 * @brief Send SMS To Number 
 * 
 * @param SMS Content of SMS
 */
void GSM_SendSMS(char const * SMS)
{
	UART1_voidSendString(SMS_CONC);//Start the message (configuerd in GSM_Config.h file)
	_delay_ms(100);//must delay to avoid error
	while(UART1_RXdata() == '>');//start to write
	UART1_voidSendString(SMS);// write message
	UART1_voidSendString("\r\n");// end of data
	UART1_TXdata(26);// EOF end of file to send
	waitforok();// wait for ok
}

/********** Fucntion Implementation End ***********************/

/********** Private Fucntion Implementation Start *************/

/**
 * @brief Iintilization of GPRS Mode
 * 
 */
void static GSM_INIT_GPRS_MODE(void)
{

	UART1_voidSendString("AT+SAPBR=0,1\r\n");// Stop GPRS to stop stucking in response
	_delay_ms(100);
	UART1_voidSendString("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n");// Start GPRS
	waitforok();//wait for ok
	UART1_voidSendString("AT+SAPBR=3,1,\"APN\",\"internet.etisalat\"\r\n");// Enter APN
	waitforok();//wait for ok
	UART1_voidSendString("AT+SAPBR=1,1\r\n");//Open GPRS Context
	waitforok();//wait for ok
}

/**
 * @brief Initilization of HTTP
 * 
 */
void static GSM_Init_HTTP(void)
{
	UART1_voidSendString("AT+HTTPTERM\r\n");// Stop HTTP to stop stucking in response
	_delay_ms(100);
	UART1_voidSendString("AT+HTTPINIT\r\n");//Initialize HTTP Requist
	waitforok();//wait for ok
	UART1_voidSendString("AT+HTTPPARA=\"CID\",1\r\n");//Set parameters for HTTP session
	waitforok();//wait for ok
	/*Configure data as Json*/
	GSM_AdjustData_Json();
	UART1_voidSendString(URL_CONC);//Enter Website URL
	waitforok();//wait for ok
}

/**
 * @brief Adjust Data format to be Written In Json
 * 
 */
void static GSM_AdjustData_Json(void)
{
	/*Choose data format as Json*/
	UART1_voidSendString("AT+HTTPPARA=\"CONTENT\",\"application/json\"\r\n");
	waitforok();// wait for ok
}

/**
 * @brief Wait for HTTPACTION
 * 
 */
void static waitforHTTPACTION(void)
{
	u16 volatile i = 0;
	/*wait for H*/
	while(UART1_RXdata() != 'H')
	{
		i++;
		if (i == 100000)
		{
			break;
		}
		//while(1);
	}
	/*wait for A*/
	while(UART1_RXdata() != 'A')
	{
		i++;
		if (i == 100000)
		{
			break;
		}
	}
	/*wait for N*/
	while(UART1_RXdata() != 'N')
	{
		i++;
		if (i == 100000)
		{
			break;
		}
	}
}

/**
 * @brief Wait for ok
 * 
 */
void static waitforok(void)
{
	u16 volatile i = 0;
	// wait for K
	while(UART1_RXdata() != 'K')
	{
		i++;
		if (i == 100000)
		{
			break;
		}
	}
}
/**
 * @brief wait for Download
 * 
 */
void static waitforDOWNLOAD(void)
{
	u16 volatile i = 0;
	// wait for D
	while(UART1_RXdata() != 'D')
	{
		i++;
		if (i == 100000)
		{
			break;
		}
	}
	// wait for D
	while(UART1_RXdata() != 'D')
	{
		i++;
		if (i == 100000)
		{
			break;
		}
	}
}

/**
 * @brief Convert Data to json Format
 * 
 * @param type Type of data
 * @param data data to content
 * @param buffer buffer to save data
 */
void static PlainToJSON(char const * type,char const * data, char * buffer)
{
	// Buffer for JSON format
    buffer[0] = '{';
    buffer[1] = '\"';
    int i_json = 2;
    int i_data = 0;

    // Add type to buffer
    while (type[i_data] != 0)
    {
        buffer[i_json] = type[i_data];
        i_json++;
        i_data++;
    }
    buffer[i_json] = '\"';
    i_json++;
    buffer[i_json] = ':';
    i_json++;


    i_data = 0;
    // add data to buffer
    while (data[i_data] != 0)
    {
        buffer[i_json] = data[i_data];
        i_json++;
        i_data++;
    }
    /*End of Frame*/
    buffer[i_json] = '\"';
    i_json++;
    buffer[i_json] = '}';
    i_json++;
    buffer[i_json] = '\0';
}

/**
 * @brief Send SMS Initialization
 * 
 */
void static SMS_INIT(void)
{
	UART1_voidSendString("AT+CMGF=0\r\n");//Stop SMS and wait
	_delay_ms(100);
	UART1_voidSendString("AT+CMGF=1\r\n");//Start SMS and wait for OK
	waitforok();//Wait for OK
}
/********** Private Fucntion Implementation End *************/










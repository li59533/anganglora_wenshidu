/**
 **************************************************************************************************
 * @file        bsp_hdc2010.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "bsp_conf.h"

#include "clog.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_iic.h"
#include "user_task.h"
/**
 * @addtogroup    bsp_hdc2010_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_hdc2010_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_hdc2010_Macros_Defines 
 * @brief         
 * @{  
 */
#define HDC2010_SLAVE_ADDR  			0X40

#define HDC2010_TEMPERATURE_L_REG		0X00  
#define HDC2010_TEMPERATURE_H_REG		0x01
#define HDC2010_HUMIDITY_L_REG			0x02
#define HDC2010_HUMIDITY_H_REG			0x03

#define HDC2010_INT_EN_REG				0x07
#define HDC2010_MEASUREMENT_REG			0X0F
#define HDC2010_MANUFACTURE_ID_L_REG	0XFC
#define HDC2010_MANUFACTURE_ID_H_REG	0xFD
#define HDC2010_DEVICE_ID_L_REG			0xFE
#define HDC2010_DEVICE_ID_H_REG			0xFF

#define HDC2010_DEVICE_ID				0XD007

/**
 * @}
 */

/**
 * @defgroup      bsp_hdc2010_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_hdc2010_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
	float temperature; 
	float humidity;
	uint8_t value_status;
	uint8_t device_status;
	
}BSP_HDC2010_t ;

typedef enum
{
	HDC2010_ERR,
	HDC2010_Normal,
	HDC2010_Update,
	HDC2010_NoUpdate,
}BSP_HDC2010_Status_e;

/**
 * @}
 */

/**
 * @defgroup      bsp_hdc2010_Private_Variables 
 * @brief         
 * @{  
 */
BSP_HDC2010_t BSP_HDC2010_Data;

/**
 * @}
 */

/**
 * @defgroup      bsp_hdc2010_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_hdc2010_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static uint8_t bsp_hdc2010_init(void);
static uint8_t bsp_hdc2010_conf(void);
static uint8_t bsp_hdc2010_trig(void);
static uint8_t bsp_hdc2010_Get(void);


/**
 * @}
 */

/**
 * @defgroup      bsp_hdc2010_Functions 
 * @brief         
 * @{  
 */


/*

//  write single byte
start -> slave addr(w) -> wait ACK ->addr -> wait ack -> data -> wait ack  -> Stop 
// write Multi Byte
Start -> slave addr(w) -> wait ACK -> addr ->wait ack -> data -> wait ack -> data -> ...-> Stop
// read single Byte
Start -> slave addr(w) -> wait ACK -> addr -> wait ack -> Start -> Slave addr(r) -> wait ACK -> data -> NACK -> Stop
// read Multi Byte 
Start -> slave addr(w) -> wait ACK -> addr -> wait ACK -> Start -> Slave addr(r) -> wait ACK -> data -> ACK -> Data ->..-> NACK -> Stop
*/ 



void BSP_HDC2010_Init(void)
{
	BSP_IIC_Init( BSP_IIC1);
	UserTask_Send_Event(USER_TASK_HDC2010_CORELOOP_EVENT);
}

typedef enum
{
	HDC2010_S_Init  = 0,
	HDC2010_S_Conf ,
	HDC2010_S_Trig , 
	HDC2010_S_Get , 
		
}HDC2010_CoreLoop_S_e;

void BSP_HDC2010_CoreLoop(void)
{
	static uint8_t status = 0;
	
	switch(status)
	{
		case HDC2010_S_Init:
		{
			DEBUG("HDC2010_S_Init\r\n");
			status = bsp_hdc2010_init();
		}
		break;
		case HDC2010_S_Conf:
		{
			DEBUG("HDC2010_S_Conf\r\n");
			status = bsp_hdc2010_conf();
		}
		break;
		case HDC2010_S_Trig:
		{
			DEBUG("HDC2010_S_Trig\r\n");
			status = bsp_hdc2010_trig();
		}
		break;
		case HDC2010_S_Get:
		{
			DEBUG("HDC2010_S_Get\r\n");
			status = bsp_hdc2010_Get();
		}
		break;
		default:break; 
	}
}

static uint8_t bsp_hdc2010_init(void)
{
	uint8_t device_id[2] = { 0 };
	
	BSP_IIC_ReadBytes( HDC2010_SLAVE_ADDR , HDC2010_DEVICE_ID_L_REG , device_id , 2 );
	DEBUG("device_id : %X%X\r\n" ,device_id[0] , device_id[1] );
	if(device_id[0] == 0xd0 && device_id[1] == 0x07)
	{
		BSP_HDC2010_Data.device_status = HDC2010_Normal;
		UserTask_Send_Event(USER_TASK_HDC2010_CORELOOP_EVENT);
		return HDC2010_S_Conf;
	}
	else
	{
		BSP_HDC2010_Data.device_status = HDC2010_ERR;
		UserTask_Timer_Start_Event(USER_TASK_HDC2010_CORELOOP_EVENT,1000);
		
		return HDC2010_S_Init;		
	}

	return HDC2010_S_Init;
}

static uint8_t bsp_hdc2010_conf(void)
{
	uint8_t conf_temp[1] = { 0 };
	
	
	conf_temp[0] = 0x00;
	BSP_IIC_WriteBytes(HDC2010_SLAVE_ADDR , HDC2010_INT_EN_REG , conf_temp , 1 );
	BSP_IIC_ReadBytes( HDC2010_SLAVE_ADDR , HDC2010_INT_EN_REG , conf_temp , 1 );
	
	if(conf_temp[0] == 0x00)
	{
		UserTask_Send_Event(USER_TASK_HDC2010_CORELOOP_EVENT);
		return HDC2010_S_Trig;
	}
	else
	{
		BSP_HDC2010_Data.device_status = HDC2010_ERR;
		UserTask_Timer_Start_Event(USER_TASK_HDC2010_CORELOOP_EVENT,1000);
		return HDC2010_S_Init;		
	}
	return HDC2010_S_Init;
}

static uint8_t bsp_hdc2010_trig(void)
{
	uint8_t conf_temp[1] = { 0 };
	
	
	conf_temp[0] = 0x01;
	BSP_IIC_WriteBytes(HDC2010_SLAVE_ADDR , HDC2010_MEASUREMENT_REG , conf_temp , 1 );
	UserTask_Timer_Start_Event(USER_TASK_HDC2010_CORELOOP_EVENT,2);
	return HDC2010_S_Get;
}

static uint8_t bsp_hdc2010_Get(void)
{
	uint8_t conf_temp[2] = { 0 };
	uint16_t temperature = 0;
	uint16_t humidity = 0;
	
	BSP_IIC_ReadBytes( HDC2010_SLAVE_ADDR , HDC2010_TEMPERATURE_L_REG , (uint8_t *)&temperature , 2 );
	BSP_IIC_ReadBytes( HDC2010_SLAVE_ADDR , HDC2010_HUMIDITY_L_REG , (uint8_t *)&humidity , 2 );
	
	BSP_HDC2010_Data.temperature = (float)(temperature)/65536*165-40;
	BSP_HDC2010_Data.humidity = (float)(humidity)/65536*100;
	BSP_HDC2010_Data.value_status = HDC2010_Update;
	
	char debug_s[40] ;
	sprintf(debug_s , "T:%f  H:%f \r\n" ,BSP_HDC2010_Data.temperature ,BSP_HDC2010_Data.humidity );
	DEBUG("%s" , debug_s);
	
	UserTask_Timer_Start_Event(USER_TASK_HDC2010_CORELOOP_EVENT,1000);
	return HDC2010_S_Trig;
}



/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


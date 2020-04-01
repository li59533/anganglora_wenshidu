/**
 **************************************************************************************************
 * @file        bsp_hdc2010.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_HDC2010_H_
#define _BSP_HDC2010_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_hdc2010_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_hdc2010_Exported_Macros 
 * @{  
 */
#define   HDC2010_TEMPERATURE_LOW	          	0x00      //温度低  
#define   HDC2010_TEMPERATURE_HIGH	          	0x01      //温度高
#define   HDC2010_HUMIDITY_LOW                	0x02      //湿度高
#define   HDC2010_HUMIDITY_HIGH               	0x03      //湿度低

#define   HDC2010_INTERRUPT_DRDY              	0x04      //DRDY中断
//bit[7]:DataReady bit status                           数据完成标志
#define  DRDY_STATUS_NOT_READAY        			0x00
#define  DRDY_STATUS_READAY            			0x80  
//bit[6]:Temperature threshold HIGH Interrupt status    温度阈值高中断标志  
#define  TH_STATUS_NO_INT              			0x00
#define  TH_STATUS_INT                 			0x40
//bit[5]:Temperature threshold LOW Interrupt status
#define  TL_STATUS_NO_INT              			0x00
#define  TL_STATUS_INT                 			0x20
//bit[4]:Humidity threshold HIGH Interrupt status
#define  HH_STATUS_NO_INT              			0x00
#define  HH_STATUS_INT                 			0x10
//bit[3]:Humidity threshold LOW Interrupt status
#define  HL_STATUS_NO_INT              			0x00
#define  HL_STATUS_INT                 			0x08

#define   HDC2010_TEMPERATURE_MAX             	0x05      //温度峰值
#define   HDC2010_HUMIDITY_MAX                	0x06      //湿度峰值

#define   HDC2010_INTERRUPT_ENABLE            	0x07      //中断配置
//bit[7]:DataReady Interrupt enable
#define  DRDY_ENABLE         	      			0x80 
#define  DRDY_DISABLE                  			0x00
//bit[6]:Temperature threshold HIGH Interrupt enable  
#define  TH_ENABLE                     			0x40
#define  TH_DISABLE                    			0x00
//bit[5]:Temperature threshold LOW Interrupt enable
#define  TL_ENABLE                     			0x20
#define  TL_DISABLE                    			0x00
//bit[4]:Humidity threshold HIGH Interrupt enable
#define  HH_ENABLE                     			0x10
#define  HH_DISABLE                    			0x00
//bit[3]:Humidity threshold HIGH Interrupt enable
#define  HL_ENABLE                     			0x08
#define  HL_DISABLE                    			0x00

#define   HDC2010_TEMP_OFFSET_ADJUST          	0x08      //温度偏移调整
#define   HDC2010_HUM_OFFSET_ADJUST           	0x09      //湿度偏移调整
#define   HDC2010_TEMP_THR_L                  	0x0A      //温度阈值低
#define   HDC2010_TEMP_THR_H                  	0x0B      //温度阈值高
#define   HDC2010_RH_THR_L                    	0x0C      //湿度阈值低
#define   HDC2010_RH_THR_H                    	0x0D      //湿度阈值高

#define   HDC2010_RESET_DRDY_INT_CONF         	0x0E      //重置和DRDY/INT配置
//bit[7]:
#define SOFT_RES_NORMAL                			0x00
#define SOFT_RES_SOFT                  			0x80
//bit[6:4]:Output Data Rate
#define ODR_NO                         			0x00      //000
#define ODR_1_120HZ                    			0x10      //001
#define ODR_1_60HZ                     			0x20      //010
#define ODR_0_1HZ                      			0x30      //011
#define ODR_0_2HZ                      			0x40      //100
#define ODR_1HZ                        			0x50      //101
#define ODR_2HZ                        			0x60      //110
#define ODR_5HZ                        			0x70      //111
//bit[3]:
#define HEAT_EN_ON                     			0x08      //加热器开
#define HEAT_EN_OFF                    			0x00
//bit[2]:DRDY/INT_EN pin configuration     
#define DRDY_OR_INT_EN_ENABLE          			0x04      //DRDY/INT_EN引脚开
#define DRDY_OR_INT_EN_HIGH_Z          			0x00      //DRDY/INT_EN引脚高阻
//bit[1]:Interrupt polarity
#define INT_POL_LOW                    			0x00
#define INT_POL_HIGH                   			0x02
//bit[0]:Interrupt mode
#define INT_MODE_LEVEL                 			0x00
#define INT_MODE_COMPARAM              			0x01

#define   HDC2010_MEASUREMENT_CONF            	0x0F      //测量配置
//bit[7:6]:Temperature resolution           温度分辨率
#define  TEM_RES_14BIT                 			0x00      //00
#define  TEM_RES_11BIT                 			0x40      //01 
#define  TEM_RES_9BIT                  			0x80      //10
//bit[5:4]:Humidity resolution
#define  HUM_RES_14BIT                 			0x00      //00
#define  HUM_RES_11BIT                 			0x10      //01 
#define  HUM_RES_9BIT                  			0x20      //10
//bit[3]:res
//bit[2:1]:Measurement configuration
#define  MEAS_CONF_TEM_HUM             			0x00      //00
#define  MEAS_CONF_TEM_ONLY            			0x02      //01
//bit[0]:Measurement trigger
#define  MEAS_TRIG_START               			0x01
#define  MEAS_TRIG_NO_ACTION           			0x00

#define   HDC2010_MANUFACTURER_ID_LOW         	0xFC     //制造商ID低    0x4954
#define   HDC2010_MANUFACTURER_ID_HIGH        	0xFD     //制造商ID高    
#define   HDC2010_DEVICE_ID_LOW               	0xFE     //设备ID低      0x07D0
#define   HDC2010_DEVICE_ID_HIGH              	0xFF     //设备ID高 


/**
 * @}
 */

/**
 * @defgroup      bsp_hdc2010_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_hdc2010_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_hdc2010_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_hdc2010_Exported_Functions 
 * @{  
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif

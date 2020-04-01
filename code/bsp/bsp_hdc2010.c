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


/**
 * @}
 */

/**
 * @defgroup      bsp_hdc2010_Private_Variables 
 * @brief         
 * @{  
 */


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




/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


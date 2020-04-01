/**
 **************************************************************************************************
 * @file        bsp_iic.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_IIC_H_
#define _BSP_IIC_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_iic_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_iic_Exported_Macros 
 * @{  
 */

#define BSP_IIC0    0
#define BSP_IIC1    1

/**
 * @}
 */

/**
 * @defgroup      bsp_iic_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_iic_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_iic_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_iic_Exported_Functions 
 * @{  
 */
void BSP_IIC_Init(uint8_t BSP_IICx);

void BSP_IIC_ReadBytes(uint8_t slavesddr , uint8_t addr , uint8_t * buf ,uint8_t len );
void BSP_IIC_WriteBytes(uint8_t slavesddr , uint8_t addr , uint8_t *buf , uint8_t len );

// -----------Test Func ------

void BSP_IIC_TestFunc(void);
bool I2C_ReadAccelWhoAmI(void);
// ---------------------------
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

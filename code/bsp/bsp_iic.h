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

bool I2C_ReadAccelWhoAmI(void);

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

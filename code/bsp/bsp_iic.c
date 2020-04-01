/**
 **************************************************************************************************
 * @file        bsp_iic.c
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
 * @addtogroup    bsp_iic_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_iic_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_iic_Macros_Defines 
 * @brief         
 * @{  
 */
#define ACCEL_I2C_CLK_SRC I2C0_CLK_SRC
#define ACCEL_I2C_CLK_FREQ CLOCK_GetFreq(I2C0_CLK_SRC)

#define I2C_RELEASE_SDA_PORT PORTE
#define I2C_RELEASE_SCL_PORT PORTE
#define I2C_RELEASE_SDA_GPIO GPIOE
#define I2C_RELEASE_SDA_PIN 25U
#define I2C_RELEASE_SCL_GPIO GPIOE
#define I2C_RELEASE_SCL_PIN 24U
#define I2C_RELEASE_BUS_COUNT 100U
#define I2C_BAUDRATE 100000U
#define FXOS8700_WHOAMI 0xC7U
#define MMA8451_WHOAMI 0x1AU
#define ACCEL_STATUS 0x00U
#define ACCEL_XYZ_DATA_CFG 0x0EU
#define ACCEL_CTRL_REG1 0x2AU
/* FXOS8700 and MMA8451 have the same who_am_i register address. */
#define ACCEL_WHOAMI_REG 0x0DU
#define ACCEL_READ_TIMES 10U
/**
 * @}
 */

/**
 * @defgroup      bsp_iic_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_iic_Private_Types
 * @brief         
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      bsp_iic_Private_Variables 
 * @brief         
 * @{  
 */
i2c_master_handle_t g_m_handle;

/**
 * @}
 */

/**
 * @defgroup      bsp_iic_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_iic_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void bsp_iic1_init(void);
static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData);

/**
 * @}
 */

/**
 * @defgroup      bsp_iic_Functions 
 * @brief         
 * @{  
 */



void BSP_IIC_Init(uint8_t BSP_IICx)
{
	bsp_iic1_init();
}

/*
iic1:
PE0 -> SDA
PE1 -> SCL
*/

static void bsp_iic1_init(void)
{
	// -------gpio init ------
	CLOCK_EnableClock(kCLOCK_PortE);
	
	
	const port_pin_config_t porte0_pin1_config = {
	kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	kPORT_SlowSlewRate,                                      /* Slow slew rate is configured */
	kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
	kPORT_MuxAlt6,                                           /* Pin is configured as I2C1_SDA */
	};
	PORT_SetPinConfig(PORTE, 0, &porte0_pin1_config);   /* PORTE0 (pin 1) is configured as I2C1_SDA */
	const port_pin_config_t porte1_pin2_config = {
	kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	kPORT_SlowSlewRate,                                      /* Slow slew rate is configured */
	kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
	kPORT_MuxAlt6,                                           /* Pin is configured as I2C1_SCL */
	};
	PORT_SetPinConfig(PORTE, 1, &porte1_pin2_config);   /* PORTE1 (pin 2) is configured as I2C1_SCL */
	// -----------------------		
	
	
	// -------iic 1 init ----
	CLOCK_EnableClock(kCLOCK_I2c1);
	
	
	// ----master conf ------
	
    /*
     * masterConfig.baudRate_Bps = 100000U;
     * masterConfig.enableStopHold = false;
     * masterConfig.glitchFilterWidth = 0U;
     * masterConfig.enableMaster = true;
     */	
	
	i2c_master_config_t masterConfig;
	I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = 200000U;

	I2C_MasterInit(I2C1, &masterConfig, CLOCK_GetFreq(I2C0_CLK_SRC));	
	
	I2C_Enable(I2C1,true);
	
	I2C_MasterTransferCreateHandle(I2C1, &g_m_handle, i2c_master_callback, NULL);
	
	
	// ----------------------

}


static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < I2C_RELEASE_BUS_COUNT; i++)
    {
        __NOP();
    }
}

/*  FXOS8700 and MMA8451 device address */
const uint8_t g_accel_address[] = {0x1CU, 0x1DU, 0x1EU, 0x1FU};

i2c_master_handle_t g_m_handle;

uint8_t g_accel_addr_found = 0x00;

volatile bool completionFlag = false;
volatile bool nakFlag = false;

static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        completionFlag = true;
    }
    /* Signal transfer success when received success status. */
    if ((status == kStatus_I2C_Nak) || (status == kStatus_I2C_Addr_Nak))
    {
        nakFlag = true;
    }
}


void BSP_IIC_Start(uint8_t BSP_IICx , uint8_t addr , i2c_direction_t direction)	
{
	I2C_MasterStart( I2C1, addr, direction);
}

void BSP_IIC_Stop(uint8_t BSP_IICx )
{
	I2C_MasterStop(I2C1);
}

void BSP_IIC_Write_Byte(uint8_t slaveaddr , uint8_t addr , uint8_t value )
{

}

void BSP_IIC_ReadBytes(uint8_t slavesddr , uint8_t addr , uint8_t * buf ,uint8_t len )
{

    i2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.slaveAddress = slavesddr;
    masterXfer.direction = kI2C_Read;
    masterXfer.subaddress = addr;
    masterXfer.subaddressSize = 1;
    masterXfer.data = buf;
    masterXfer.dataSize = len;
    masterXfer.flags = kI2C_TransferDefaultFlag;


	I2C_MasterTransferNonBlocking(I2C1, &g_m_handle, &masterXfer);

	/*  wait for transfer completed. */
	while ((!nakFlag) && (!completionFlag))
	{
		
	}
	completionFlag = false;
	nakFlag = false;
	
}


void BSP_IIC_WriteBytes(uint8_t slavesddr , uint8_t addr , uint8_t *buf , uint8_t len )
{

    i2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.slaveAddress = slavesddr;
    masterXfer.direction = kI2C_Write;
    masterXfer.subaddress = addr;
    masterXfer.subaddressSize = 1;
    masterXfer.data = buf;
    masterXfer.dataSize = len;
    masterXfer.flags = kI2C_TransferDefaultFlag;


	I2C_MasterTransferNonBlocking(I2C1, &g_m_handle, &masterXfer);

	/*  wait for transfer completed. */
	while ((!nakFlag) && (!completionFlag))
	{
		
	}
	completionFlag = false;
	nakFlag = false;
	
}



// -----------Test Func --------------

void BSP_IIC_TestFunc(void)
{
	
	uint8_t temp[3] = {0x12 , 0x45 , 0xfe};
	BSP_IIC_WriteBytes(0x40 , 0x07 , temp , 3);

}


bool I2C_ReadAccelWhoAmI(void)
{
    /*
    How to read the device who_am_I value ?
    Start + Device_address_Write , who_am_I_register;
    Repeart_Start + Device_address_Read , who_am_I_value.
    */
    uint8_t who_am_i_reg = ACCEL_WHOAMI_REG;
    uint8_t who_am_i_value = 0x00;
    uint8_t accel_addr_array_size = 0x00;
    bool find_device = false;
    uint8_t i = 0;
    uint32_t sourceClock = 0;

    i2c_master_config_t masterConfig;

    /*
     * masterConfig.baudRate_Bps = 100000U;
     * masterConfig.enableStopHold = false;
     * masterConfig.glitchFilterWidth = 0U;
     * masterConfig.enableMaster = true;
     */
    I2C_MasterGetDefaultConfig(&masterConfig);

    masterConfig.baudRate_Bps = I2C_BAUDRATE;

    sourceClock = ACCEL_I2C_CLK_FREQ;

    I2C_MasterInit(I2C1, &masterConfig, sourceClock);

    i2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));

	uint8_t temp = 0;

    masterXfer.slaveAddress = 0x40;
    masterXfer.direction = kI2C_Read;
    masterXfer.subaddress = 0xfe;
    masterXfer.subaddressSize = 1;
    masterXfer.data = &temp;
    masterXfer.dataSize = 1;
    masterXfer.flags = kI2C_TransferDefaultFlag;


	I2C_MasterTransferNonBlocking(I2C1, &g_m_handle, &masterXfer);

	/*  wait for transfer completed. */
	while ((!nakFlag) && (!completionFlag))
	{
		
	}
	completionFlag = false;
	nakFlag = false;

	
	DEBUG("temp:%x\r\n" , temp);
	
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


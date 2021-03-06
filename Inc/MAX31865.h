/*
 * MAX31865.h
 *
 *  Created on: 12.06.2016
 *      Author: washed
 */

#ifndef MAX31865_H_
#define MAX31865_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include <spi.h>

#define TEMP_INT_FACTOR						10000

#define MAX31865_SPI_INSTANCE_PT			&hspi3

#define MAX31865_MAX_DEVICES				1

#define MAX31865_WDG_PERIOD					250000		//�s

#define MAX31865_CON_DEVICES				1
#define MAX31865_USE_CALLENDAR_VAN_DUSEN	0 // TODO: This is still broken
#define MAX31865_MAX_BUFFERSIZE             10
#if (MAX31865_USE_CALLENDAR_VAN_DUSEN == 1)
#error "don't use this right now!"
#endif

#define MAX31865_CVD_A						(float)255.8723
#define MAX31865_CVD_B						(float)9.6
#define MAX31865_CVD_C						(float)0.878
#define MAX31865_REF_RESISTOR				4000
#define MAX31865_MAX_RTD					(float)0x8000
#define MAX31865_R0minus1					(float)999
#define MAX31865_RTD_DIVIDER				(float)(MAX31865_MAX_RTD * MAX31865_R0minus1)
#define MAX31865_KELVIN_0dC					2731600

#define MAX31865_0_CS_BANK					(uint32_t)SPI3_CS0_GPIO_Port
#define MAX31865_1_CS_BANK					(uint32_t)0
#define MAX31865_2_CS_BANK					(uint32_t)0
#define MAX31865_3_CS_BANK					(uint32_t)0

#define MAX31865_0_CS_PIN					(uint32_t)SPI3_CS0_Pin
#define MAX31865_1_CS_PIN					(uint32_t)0
#define MAX31865_2_CS_PIN					(uint32_t)0
#define MAX31865_3_CS_PIN					(uint32_t)0

#define MAX31865_0_DR_BANK					(uint32_t)GPIOA
#define MAX31865_1_DR_BANK					(uint32_t)0
#define MAX31865_2_DR_BANK					(uint32_t)0
#define MAX31865_3_DR_BANK					(uint32_t)0

#define MAX31865_0_DR_PIN					(uint32_t)GPIO_PIN_15
#define MAX31865_1_DR_PIN					(uint32_t)0
#define MAX31865_2_DR_PIN					(uint32_t)0
#define MAX31865_3_DR_PIN					(uint32_t)0

#define MAX31865_CFG_REG_RD_ADDR			0x00
#define MAX31865_RTDMSB_REG_RD_ADDR			0x01
#define MAX31865_RTDLSB_REG_RD_ADDR			0x02
#define MAX31865_HFTHRMSB_REG_RD_ADDR		0x03
#define MAX31865_HFTHRLSB_REG_RD_ADDR		0x04
#define MAX31865_LFTHRMSB_REG_RD_ADDR		0x05
#define MAX31865_LFTHRLSB_REG_RD_ADDR		0x06
#define MAX31865_FLTSTAT_REG_RD_ADDR		0x07

#define MAX31865_CFG_REG_WR_ADDR			0x80
#define MAX31865_HFTHRMSB_REG_WR_ADDR		0x83
#define MAX31865_HFTHRLSB_REG_WR_ADDR		0x84
#define MAX31865_LFTHRMSB_REG_WR_ADDR		0x85
#define MAX31865_LFTHRLSB_REG_WR_ADDR		0x86

#define MAX31865_FLTSTAT_REG_MASK			0xFC
#define MAX31865_FLTSTAT_REG_RTDHIGH		0x80
#define MAX31865_FLTSTAT_REG_RTDLOW			0x40
#define MAX31865_FLTSTAT_REG_REFINHIGH		0x20
#define MAX31865_FLTSTAT_REG_REFINLOW		0x10
#define MAX31865_FLTSTAT_REG_RTDINLOW		0x08
#define MAX31865_FLTSTAT_REG_OVUVFLT		0x04

#define MAX_31865_CFG_VBIAS_ON_SHIFT		7
#define MAX_31865_CFG_CONVAUTO_ON_SHIFT		6
#define MAX_31865_CFG_1SHOT_ON_SHIFT		5
#define MAX_31865_CFG_3WIRE_ON_SHIFT		4
#define MAX_31865_CFG_FAULT_SHIFT			2
#define MAX_31865_CFG_50HZ_ON_SHIFT			0

#define MAX_31865_CFG_VBIAS_ON				(1 << MAX_31865_CFG_VBIAS_ON_SHIFT)
#define MAX_31865_CFG_CONVAUTO_ON			(1 << MAX_31865_CFG_CONVAUTO_ON_SHIFT)
#define MAX_31865_CFG_1SHOT_ON				(1 << MAX_31865_CFG_1SHOT_ON_SHIFT)
#define MAX_31865_CFG_3WIRE_ON				(1 << MAX_31865_CFG_3WIRE_ON_SHIFT)
#define MAX_31865_CFG_FAULT_NONE			(0 << MAX_31865_CFG_FAULT_SHIFT)
#define MAX_31865_CFG_FAULT_AUTODELAY		(1 << MAX_31865_CFG_FAULT_SHIFT)
#define MAX_31865_CFG_FAULT_RUN_MAN			(2 << MAX_31865_CFG_FAULT_SHIFT)
#define MAX_31865_CFG_FAULT_FIN_MAN			(3 << MAX_31865_CFG_FAULT_SHIFT)
#define MAX_31865_CFG_50HZ_ON				(1 << MAX_31865_CFG_50HZ_ON_SHIFT)

	extern volatile uint32_t MAX31865_DEVICES_RTD_DATA[MAX31865_MAX_DEVICES];
	extern int32_t MAX31865_DEVICES_TEMP[MAX31865_MAX_DEVICES];
	extern volatile uint32_t MAX31865_DEVICES_TIME_SINCE_LAST_READ[MAX31865_MAX_DEVICES];
	extern uint32_t averaged_RTD_temp;

//const uint32_t MAX31865_DEVICES_CS_BANK_PIN[MAX31865_MAX_DEVICES][2];
//const uint32_t MAX31865_DEVICES_DR_BANK_PIN[MAX31865_MAX_DEVICES][2];

	void handleMAX31865Devices();
	void initMAX31865();
	void checkMAX31865WDG();
	void getRTDData_MAX31865( uint32_t device_num );
	void setCfgReg_MAX31865( uint32_t device_num, uint8_t config_flags );
	uint8_t getFaultStatus_MAX31865( uint32_t device_num );
	void setReg_MAX31865( uint32_t device_num, uint8_t reg, uint8_t* p_data, uint8_t len );
	void getReg_MAX31865( uint32_t device_num, uint8_t reg, uint8_t* p_data, uint8_t len );
	void initSPIIdleClock();
	void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin );
	void tickMAX31865WDGTimer( uint32_t ticks );

#ifdef __cplusplus
}
#endif
#endif /* RS232_SNIFFER_V0_INC_MAX31865_H_ */

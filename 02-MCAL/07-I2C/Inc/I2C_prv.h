#ifndef		I2C2_PRV_H_
#define 	I2C2_PRV_H_

/*Registers Mask*/

/**/
#define MCU_FREQ_CLOCK		8000000UL
#define MCU_PERIOD_TIME		1/MCU_FREQ_CLOCK

#define MAX_PERIPH_CLK_FREQ		50
#define MIN_PERIPH_CLK_FREQ		2
/*NUMBER OF I2C INTERRUPT FLAGS*/
#define READY_FLAG				1
#define NOT_READY_FLAG			0


/*GET/READ VALUE MASK*/
#define READ_VAL_MASK			0x01

/*SET/RESET MASKS*/
#define SET_MASK   				1
#define RESET_MASK 				0

#define BUSY_FLAG				1


#endif

#ifndef   USART_PRV_H_
#define   USART_PRV_H_

/*Registers Mask*/

#define STATUS_REG_MASK		0x000003FFUL
#define DATA_REG_MASK		0x000001FFUL
#define	BAUDRATE_REG_MASK	0x0000FFFFUL
#define	CR1_REG_MASK		0x00003FFFUL
#define	CR2_REG_MASK		0x00007F6FUL
#define	CR3_REG_MASK		0x000007FFUL
#define GTP_REG_MASK		0x0000FFFFUL

/*Mantissa and fractional part MASKs*/


/*Received and transmitted Data - parity MASKs */


/*NUMBER OF USART PERIPHERALS in STM32F1xx*/
#define	NUMBER_OF_USART_PERIPH	5

/*NUMBER OF USART INTERRUPT FLAGS*/
#define FLAGS_NUMBER			9

#define READY_FLAG				1
#define NOT_READY_FLAG			0

/*GET/READ VALUE MASK*/
#define READ_VAL_MASK			0x01


/*SET/RESET MASKS*/
#define SET_MASK   1
#define RESET_MASK 0



#endif

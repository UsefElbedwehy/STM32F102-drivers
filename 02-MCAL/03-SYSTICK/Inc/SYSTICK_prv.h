#ifndef	SYSTICK_PRV_H_
#define	SYSTICK_PRV_H_
/*FREQ*/
#define SYSTEM_FREQUANCY	8000000UL
#define EXTERNAL_CLK_PRESCALLER		8

/*MASKS*/
#define SET_MASK		1
#define GET_MASK		0x01

/*Initial values*/
#define INITIAL_LOAD_VAL    0
#define INIT_VALUE			0

/*FLAGS*/
#define READY_FLAG		1
#define NOT_READY_FLAG	0

/*POWER*/
#define	_10POW3				1000UL
#define	_10POW6				1000000UL

#endif

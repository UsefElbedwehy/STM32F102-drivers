#ifndef ERRTYPE_H_
#define ERRTYPE_H_

typedef enum{
	OK,
	NOK,
	NULL_POINTER,
	I2C_OK,
	I2C_NOK,
	I2C_NULL_POINTER

}ErrorState_t;

#define NULL ((void *)0)

#endif

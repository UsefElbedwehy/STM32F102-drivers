#ifndef		BITHMATH_H_
#define		BITHMATH_H_

#define		SetBit(Reg,Bit)				Reg|=(1<<Bit)		
#define		CLRBit(Reg,Bit)				Reg&=~(1<<Bit)
#define		GetBit(Reg,Bit)				((Reg>>Bit)&0x01)
#define		ToggleBit(Reg,Bit)			Reg^=(1<<Bit)

#endif
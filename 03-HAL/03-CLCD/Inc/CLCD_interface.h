#ifndef   CLCD_INTERFACE_H
#define    CLCD_INTERFACE_H

void CLCD_Init(void);
void CLCD_SendCmd(uint8_t Copy_u8Cmd);
void CLCD_SendData(uint8_t Copy_u8Data);
void CLCD_PrintWord(char* Copy_pvData);

#endif

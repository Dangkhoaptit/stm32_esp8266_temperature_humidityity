#include "stm32f10x.h"

#define DHT_Pin GPIO_Pin_12

void Delay1Ms(void);
void Delay_Ms(uint32_t u32DelayInMs);
void ReadDHT11(void);
void DHT_Init(void);

extern uint16_t u16Tim;
extern uint8_t u8Buff[5];		//Data from DHT11
extern uint8_t u8CheckSum;		//Check bit

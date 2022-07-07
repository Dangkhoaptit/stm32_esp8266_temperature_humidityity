#include "DHT11_DK.h"

void Delay1Ms(void)
{
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < 1000) {
	}
}

void Delay_Ms(uint32_t u32DelayInMs)
{
	
	while (u32DelayInMs) {
		Delay1Ms();
		--u32DelayInMs;
	}
}
void DHT_Init(void){
	GPIO_InitTypeDef gpioInit;
	TIM_TimeBaseInitTypeDef timerInit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_OD;
	gpioInit.GPIO_Pin = DHT_Pin;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	GPIO_SetBits(GPIOB, DHT_Pin);
	
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	timerInit.TIM_Period = 0xFFFF;
	timerInit.TIM_Prescaler = 72 - 1;
	
	TIM_TimeBaseInit(TIM2, &timerInit);
	
	TIM_Cmd(TIM2, ENABLE);
}

void ReadDHT11(void){
		uint8_t i;
	  GPIO_ResetBits(GPIOB, DHT_Pin);
		Delay_Ms(20);
		GPIO_SetBits(GPIOB, DHT_Pin);
		
		/* cho chan PB12 len cao */
		TIM_SetCounter(TIM2, 0);
		while (TIM_GetCounter(TIM2) < 10) {
			if (GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
				break;
			}
		}
		u16Tim = TIM_GetCounter(TIM2);
		if (u16Tim >= 10) {
			while (1) {
			}
		}
		
		/* cho chan PB12 xuong thap */
		TIM_SetCounter(TIM2, 0);
		while (TIM_GetCounter(TIM2) < 45) {
			if (!GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
				break;
			}
		}
		u16Tim = TIM_GetCounter(TIM2);
		if ((u16Tim >= 45) || (u16Tim <= 5)) {
			while (1) {
			}
		}
		
		/* cho chan PB12 len cao */
		TIM_SetCounter(TIM2, 0);
		while (TIM_GetCounter(TIM2) < 90) {
			if (GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
				break;
			}
		}
		u16Tim = TIM_GetCounter(TIM2);
		if ((u16Tim >= 90) || (u16Tim <= 70)) {
			while (1) {
			}
		}
		
		/* cho chan PB12 xuong thap */
		TIM_SetCounter(TIM2, 0);
		while (TIM_GetCounter(TIM2) < 95) {
			if (!GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
				break;
			}
		}
		u16Tim = TIM_GetCounter(TIM2);
		if ((u16Tim >= 95) || (u16Tim <= 75)) {
			while (1) {
			}
		}
		
		/* nhan byte so 1 */
		for (i = 0; i < 8; ++i) {
			/* cho chan PB12 len cao */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 65) {
				if (GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 65) || (u16Tim <= 45)) {
				while (1) {
				}
			}
			
			/* cho chan PB12 xuong thap */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 80) {
				if (!GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 80) || (u16Tim <= 10)) {
				while (1) {
				}
			}
			u8Buff[0] <<= 1;
			if (u16Tim > 45) {
				/* nhan duoc bit 1 */
				u8Buff[0] |= 1;
			} else {
				/* nhan duoc bit 0 */
				u8Buff[0] &= ~1;
			}
		}
		
		/* nhan byte so 2 */
		for (i = 0; i < 8; ++i) {
			/* cho chan PB12 len cao */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 65) {
				if (GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 65) || (u16Tim <= 45)) {
				while (1) {
				}
			}
			
			/* cho chan PB12 xuong thap */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 80) {
				if (!GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 80) || (u16Tim <= 10)) {
				while (1) {
				}
			}
			u8Buff[1] <<= 1;
			if (u16Tim > 45) {
				/* nhan duoc bit 1 */
				u8Buff[1] |= 1;
			} else {
				/* nhan duoc bit 0 */
				u8Buff[1] &= ~1;
			}
		}
		
		/* nhan byte so 3 */
		for (i = 0; i < 8; ++i) {
			/* cho chan PB12 len cao */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 65) {
				if (GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 65) || (u16Tim <= 45)) {
				while (1) {
				}
			}
			
			/* cho chan PB12 xuong thap */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 80) {
				if (!GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 80) || (u16Tim <= 10)) {
				while (1) {
				}
			}
			u8Buff[2] <<= 1;
			if (u16Tim > 45) {
				/* nhan duoc bit 1 */
				u8Buff[2] |= 1;
			} else {
				/* nhan duoc bit 0 */
				u8Buff[2] &= ~1;
			}
		}
		
		/* nhan byte so 4 */
		for (i = 0; i < 8; ++i) {
			/* cho chan PB12 len cao */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 65) {
				if (GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 65) || (u16Tim <= 45)) {
				while (1) {
				}
			}
			
			/* cho chan PB12 xuong thap */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 80) {
				if (!GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 80) || (u16Tim <= 10)) {
				while (1) {
				}
			}
			u8Buff[3] <<= 1;
			if (u16Tim > 45) {
				/* nhan duoc bit 1 */
				u8Buff[3] |= 1;
			} else {
				/* nhan duoc bit 0 */
				u8Buff[3] &= ~1;
			}
		}
		
		/* nhan byte so 5 */
		for (i = 0; i < 8; ++i) {
			/* cho chan PB12 len cao */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 65) {
				if (GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 65) || (u16Tim <= 45)) {
				while (1) {
				}
			}
			
			/* cho chan PB12 xuong thap */
			TIM_SetCounter(TIM2, 0);
			while (TIM_GetCounter(TIM2) < 80) {
				if (!GPIO_ReadInputDataBit(GPIOB, DHT_Pin)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM2);
			if ((u16Tim >= 80) || (u16Tim <= 10)) {
				while (1) {
				}
			}
			u8Buff[4] <<= 1;
			if (u16Tim > 45) {
				/* nhan duoc bit 1 */
				u8Buff[4] |= 1;
			} else {
				/* nhan duoc bit 0 */
				u8Buff[4] &= ~1;
			}
		}
		
		u8CheckSum = u8Buff[0] + u8Buff[1] + u8Buff[2] + u8Buff[3];
		if (u8CheckSum != u8Buff[4]) {
			while (1) {
			}
		}
}
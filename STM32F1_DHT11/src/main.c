#include "stm32f10x.h"
#include "usart.h"
#include "DHT11_DK.h"

uint16_t u16Tim;
uint8_t u8Buff[5];		//Data from DHT11
uint8_t u8CheckSum;		//Check bit

void GPIO_Led_Init(void);

char DHT11_TEMP[20], DHT11_HUMI[20];

int main(void)
{
	GPIO_Led_Init();
	
	DHT_Init();
	
	USARTx_Init(USART1, Pins_PA9PA10,115200);
	
	
	while (1) {
		ReadDHT11();
		
		//send temperature and humidity
		sprintf(DHT11_TEMP,"tem%d,%d",u8Buff[2],u8Buff[3]);
		USART_Puts(USART1,DHT11_TEMP);
		Delay_Ms(2500);
		
		sprintf(DHT11_HUMI,"hum%d,%d",u8Buff[0],u8Buff[1]);
		USART_Puts(USART1,DHT11_HUMI);
		Delay_Ms(2500);
		
		//Display stauts to Led PC13
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay_Ms(500);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay_Ms(100);
	}
}

void GPIO_Led_Init(void){
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &gpioInit);
}

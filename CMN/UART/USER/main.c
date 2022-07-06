#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "ds18b20.h"

 float nhietdo = 0;
 float pre_temp = 0;
 char str[20];
 int main(void)
 {	
	//char c = '0';
	//char buffer[100] ;
	 //LED_init();
	 delay_init();
	 pinMode(PB5,OUTPUT);
	 pinMode(PB6,INPUT);
	 
	 USARTx_Init(USART1, Pins_PA9PA10, 115200);
	 
  while(1)
	{
	//	c=USART_Getc(USART1);
//		if(c) USART_Putc(USART1,c);
		//buffer printf("%s",buffer);//
		
		nhietdo = ds18b20_read();
		delay_ms(1000);
		sprintf(str,"%3.2f\n",(float)nhietdo);
		
		//delay_ms(2000);
		
		//char buffer[100];
		if (pre_temp != nhietdo) {
			USART_Puts(USART1,str);
			pre_temp = nhietdo;
			}

//	digitalWrite( PB5, HIGH );delay_ms(300);
//	digitalWrite( PB5, LOW );delay_ms(300);
	}
 }

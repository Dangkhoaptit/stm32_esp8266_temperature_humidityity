
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "includes.h"

#include "ds18b20.h"

#include "stm32f10x_rtc.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_pwr.h"
#include "RTC_BTL.h"

/*======================================== START TASK============================================*/
#define START_TASK_PRIO      			3 
#define START_STK_SIZE  			  	64
OS_STK START_TASK_STK[START_STK_SIZE];

void start_task(void *pdata);	
 			   
/*==================================== READ TEMPERATURE TASK =====================================*/
#define READ_TEMPERATURE_PRIO       					1
#define READ_TEMPERATURE_STK_SIZE  		    		64
OS_STK READ_TEMPERATURE_STK[READ_TEMPERATURE_STK_SIZE];

void READ_TEMPERATURE(void *pdata);

/*=========================== RECEIVE DATA FROM ESP32 TASK =========================*/
#define RTC_TASK_PRIO       			2
#define RTC_STK_SIZE  					128
OS_STK RTC_TASK_STK[RTC_STK_SIZE];

void main_task(void *pdata);

OS_EVENT * msg_key;	


char a[16],des[16];

float nhietdo = 0;
char temperature_str[20];

int main(void)
{	
	 
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		delay_init();	
	 
		USARTx_Init(USART1, Pins_PA9PA10, 115200);	 
	 
		OSInit();   
		OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );
		OSStart();
  
}
 
void start_task(void *pdata){
	 
	 OS_CPU_SR cpu_sr=0;
	 pdata = pdata; 
	 
	 msg_key=OSMboxCreate((void*)0);	
	 OS_ENTER_CRITICAL();
	 
	 OSTaskCreate(READ_TEMPERATURE,(void *)0,(OS_STK *)&READ_TEMPERATURE_STK[READ_TEMPERATURE_STK_SIZE-1],READ_TEMPERATURE_PRIO );
	 OSTaskCreate(main_task,(void *)0,(OS_STK*)&RTC_TASK_STK[RTC_STK_SIZE-1],RTC_TASK_PRIO);
	
	 OSTaskSuspend(START_TASK_PRIO);	
	 OS_EXIT_CRITICAL();
	 
 }
 
void READ_TEMPERATURE(void *pdata)
{	  
	while(1)
	{
			nhietdo = ds18b20_read();
			sprintf(temperature_str,"%3.2f",(float)nhietdo);
			delay_ms(2000);
	};
}


void main_task(void *pdata)
{	
 	while(1)
	{		
			printf("%s",temperature_str);			
			delay_ms(2000);
	}
}	





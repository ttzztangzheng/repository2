#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key_exti.h"
#include "stm32f10x_it.h"
#include "timer.h"
#include "usart.h"

u8 key_caiji=0;
u8 flag_caiji=0;
int main(void)
{ 
 
	delay_init();		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	EXTI_Key_init();
	TIM_GPIO_Config();
	USART1_Configuration();
//	printf("Hello, SMART103!\r\n");
	while(1)
	{
		if(key_caiji)
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
			if(flag_caiji==1)
			{
				flag_caiji=0;
				GPIO_ResetBits(GPIOB,GPIO_Pin_5);
				delay_ms(1000);
				GPIO_SetBits(GPIOB,GPIO_Pin_5);
				
			}
		}
		else
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_5);
			
		}
		
	}
} 
 


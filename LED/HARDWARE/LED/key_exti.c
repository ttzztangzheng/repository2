#include "key_exti.h"
#include "stm32f10x.h"

static void EXTI_Key_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   			//把NVIC中断优先级分组设置为第一组
  
  /* 配置P[A|B|C|D|E]的中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;            //配置的为EXTI第5~9的中断向量
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;            //配置的为EXTI第10~15的中断向量
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

/*
 * 函数名：EXTI_Key_GPIO_Configuration
 * 描述  ：配置独立按键所使用的GPIO端口及模式
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void EXTI_Key_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
    /* EXTI line gpio config(PD8,PD9,PD10,PD11) */	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_3;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
}

/*
 * 函数名：EXTI_Key_init
 * 描述  ：初始化独立按键，配置所需的中断端口及模式
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void EXTI_Key_init(void)
{	
	EXTI_InitTypeDef EXTI_InitStructure;												

    /* config the extiline(PD) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,ENABLE);	//使用中断务必要开启复用时钟
    /* config the GPIO(PD) */
  EXTI_Key_GPIO_Configuration();
    /* config the NVIC(PD) */
	EXTI_Key_NVIC_Configuration();

	/* EXTI line mode config */
	/*设置外部中断8、9、10、11在下降沿时触发中断*/

  EXTI_InitStructure.EXTI_Line=EXTI_Line3|EXTI_Line4;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	
	EXTI_Init(&EXTI_InitStructure);
    
}   
    
    
    
    
    
    
    




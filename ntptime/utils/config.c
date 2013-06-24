#include "config.h"
#include "stm32f10x.h"

GPIO_InitTypeDef  GPIO_InitStruct;

void LCD_Port_Set_Output(void)
{
	GPIO_InitStruct.GPIO_Pin = 	LCD_DB0 | LCD_DB3 |
								LCD_DB4 | LCD_DB5 |
								LCD_DB6 | LCD_DB7;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(LCD_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LCD_DB1 | LCD_DB2;
	GPIO_Init(LCD_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LCD_RS | LCD_RW	| LCD_E;
	GPIO_Init(LCD_CTRL,&GPIO_InitStruct);
}

void RCC_Config(void)
{
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);

	RCC_WaitForHSEStartUp();

	 //RCC->CFGR |=  RCC_CFGR_PLLXTPRE;


	/* HCLK = SYSCLK  = 72 MHz*/
	 RCC_HCLKConfig(RCC_SYSCLK_Div1);

	/* PCLK2 = HCLK */
	 RCC_PCLK2Config(RCC_HCLK_Div1);

	/* PCLK1 = HCLK/2 */
	 RCC_PCLK1Config(RCC_HCLK_Div2);

	 /* PLLCLK = 8MHz * 9 = 72 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

	/* Enable PLL */
	 RCC_PLLCmd(ENABLE);

	/* Wait till PLL is ready */
	  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	    {
		  //
	    }

	/* Select PLL as system clock source */
	  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	/* Wait till PLL is used as system clock source */
	  while(RCC_GetSYSCLKSource() != 0x08)
	    {
		  //
	    }
}

void Delay_ms(__IO uint32_t nTime)
{
	uint32_t nTicks = (SystemCoreClock/1000)*nTime;

	for(; nTicks != 0; nTicks--);
}

inline void DelayLoop(uint32_t delayLoops)
{
  uint16_t  i;

	for(i = 0; i<delayLoops; i++)
		{
			;
		}
}

void gpio_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD ,ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED1;						// LED1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED2;						// LED2
	GPIO_Init(LED_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED3;						// LED3
	GPIO_Init(LED_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED4;						// LED4
	GPIO_Init(LED_PORT, &GPIO_InitStructure);

	LCD_Port_Set_Output();										// config LCD_port Output

//-----------------------------------------------------------------------------------------------------------------------------------------------
	GPIO_InitStructure.GPIO_Pin = pin_TX;						// USART4_TX (PC10)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(port_UART, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = pin_RX;						// USART4_RX (PC11)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(port_UART, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = pin_DE;						// RE-DE pin (PC12)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(port_UART,&GPIO_InitStructure);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = KN_STR3;						// kn6	Out Push Pull
	GPIO_Init(KN_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = KN_STR2;						// kn5	Out Push pull
	GPIO_Init(KN_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = KN_STR1;						// kn4	Out Push pull
	GPIO_Init(KN_PORT, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = KN_COL3;						// kn3	Input Pull Up
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(KN_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = KN_COL2;						// kn2	Input Pull Up
	GPIO_Init(KN_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = KN_COL1;						// kn1	Input Pull Up
	GPIO_Init(KN_PORT, &GPIO_InitStructure);
}
//====================================================================================================================================================
void TIM3_Config(void)					// timer keyboard
{
	TIM_TimeBaseInitTypeDef  tim3;
	NVIC_InitTypeDef NVIC_tim3;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_DeInit(TIM3);

	/* TIMx Mode */
	tim3.TIM_Period = 10;											// 10 ms interrupt
	tim3.TIM_Prescaler = 36000 - 1;
	tim3.TIM_ClockDivision = TIM_CKD_DIV1;
	tim3.TIM_RepetitionCounter = 0x00;
	tim3.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &tim3);

	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	/* TIM IT_Update  enable */
	TIM_ITConfig(TIM3, TIM_IT_Update , ENABLE);

	/* TIMx enable counter */
	TIM_Cmd(TIM3, ENABLE);

	NVIC_tim3.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_tim3.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_tim3.NVIC_IRQChannelSubPriority = 3;
	NVIC_tim3.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_tim3);

	NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM2_Config(void)													// System timer
{
	TIM_TimeBaseInitTypeDef  tim2;
	NVIC_InitTypeDef NVIC_tim2;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);					// затактировали Таймер 2

	tim2.TIM_CounterMode = TIM_CounterMode_Up;
	tim2.TIM_Period = 1000;
	tim2.TIM_Prescaler = 36000 - 1;										//  1000 ms
	tim2.TIM_ClockDivision = TIM_CKD_DIV1;								// без делителя тактирование 36 МГц
	tim2.TIM_RepetitionCounter = 0x00;

	TIM_TimeBaseInit(TIM2,&tim2);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_Cmd(TIM2,ENABLE);

	NVIC_tim2.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_tim2.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_tim2.NVIC_IRQChannelSubPriority = 3;
	NVIC_tim2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_tim2);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);							// разрешено прерывание от переполнения
	NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM5_Config(void)													// HOST
{
	TIM_TimeBaseInitTypeDef  tim5;
	NVIC_InitTypeDef NVIC_tim5;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);					// затактировали Таймер 6

	tim5.TIM_CounterMode = TIM_CounterMode_Up;
	tim5.TIM_Period = 360;
	tim5.TIM_Prescaler = 0;										//  5 ms
	tim5.TIM_ClockDivision = TIM_CKD_DIV1;								// без делителя тактирование 36 МГц

	TIM_TimeBaseInit(TIM5,&tim5);
	TIM_ClearFlag(TIM5,TIM_FLAG_Update);
	TIM_Cmd(TIM5,ENABLE);

	NVIC_tim5.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_tim5.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_tim5.NVIC_IRQChannelSubPriority = 8;
	NVIC_tim5.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_tim5);

	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);							// разрешено прерывание от переполнения
	NVIC_EnableIRQ(TIM5_IRQn);
}

void TIM6_Config(void)
{
	TIM_TimeBaseInitTypeDef  tim6;
	NVIC_InitTypeDef NVIC_tim6;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);					// затактировали Таймер 6

	tim6.TIM_CounterMode = TIM_CounterMode_Up;
	tim6.TIM_Period = 5;
	tim6.TIM_Prescaler = 36000 - 1;										//  5 ms
	tim6.TIM_ClockDivision = TIM_CKD_DIV1;								// без делителя тактирование 36 МГц

	TIM_TimeBaseInit(TIM6,&tim6);
	TIM_ClearFlag(TIM6,TIM_FLAG_Update);
	TIM_Cmd(TIM6,ENABLE);

	NVIC_tim6.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_tim6.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_tim6.NVIC_IRQChannelSubPriority = 3;
	NVIC_tim6.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_tim6);

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);							// разрешено прерывание от переполнения
	NVIC_EnableIRQ(TIM6_IRQn);
}
//-----------------------------------------------------------------------------  M & C HOST (USART 4) ---------------------------------------------------------------
void USART_HOST_Config(void)
{
	USART_InitTypeDef host_usart;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);

	host_usart.USART_WordLength = USART_WordLength_8b;
	host_usart.USART_Parity = USART_Parity_No;
	host_usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	host_usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	host_usart.USART_BaudRate = 38400;
	host_usart.USART_StopBits = USART_StopBits_2;

	USART_Init(UART4,&host_usart);

	USART_Cmd(UART4,ENABLE);
}
//====================================================================================================================================================
void NVIC_UART4_Config(void)
{
	NVIC_InitTypeDef NVIC_host;

  /* Enable the UART HOST Interrupt */

	 NVIC_host.NVIC_IRQChannelSubPriority = 0;
	 NVIC_host.NVIC_IRQChannelPreemptionPriority = 2;
	 NVIC_host.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_host.NVIC_IRQChannel = UART4_IRQn;

	 NVIC_Init(&NVIC_host);

	 USART_ITConfig( UART4, USART_IT_RXNE, ENABLE );
	 USART_ITConfig( UART4, USART_IT_TC, DISABLE );
	 USART_ITConfig( UART4, USART_IT_TXE, DISABLE);

	 NVIC_EnableIRQ(UART4_IRQn);
}

//====================================================================================================================================================
inline void Tx_ON()
{
	port_UART->BSRR = pin_DE;
}

inline void Tx_OFF()
{
	port_UART->BRR = pin_DE;
}
inline void HOST_DE_OFF(void)
{
	port_UART->BRR = pin_DE;
}

inline void HOST_DE_ON(void)
{
	port_UART->BSRR = pin_DE;
}

//====================================================================================================================================================
inline void CS_ON()
{
	port_SPI->BSRR = CS_AT45;
}

inline void CS_OFF()
{
	port_SPI->BRR = CS_AT45;
}
//------------------------------------------------------------------------------------------------------------------------------------------
inline void KN_STR_ON(GPIO_TypeDef* Port,uint16_t Pin)
{
	Port->BSRR = Pin;
}

inline void KN_STR_OFF(GPIO_TypeDef* Port,uint16_t Pin)
{
	Port->BRR = Pin;
}

inline Bool Check_Bit(GPIO_TypeDef* Port, uint16_t Pin)
{
	return (Port->IDR & Pin)? True : False;

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
inline void Pin_Toggle(GPIO_TypeDef* Port, uint16_t GPIO_Pin)
{
	Port->ODR ^= GPIO_Pin;
}

inline void Pin_Off(GPIO_TypeDef* Port, uint16_t GPIO_Pin)
{
	Port->BRR = GPIO_Pin;
}

inline void Pin_On(GPIO_TypeDef* Port, uint16_t GPIO_Pin)
{
	Port->BSRR = GPIO_Pin;
}

//====================================================================================================================================================

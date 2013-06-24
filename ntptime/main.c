#include "stm32f10x.h"
#include "config.h"

const unsigned char ReklamaText[2][24] =
{
  {" RadioComm Technologies "},
  {"   						"}
};


volatile uint8_t  TimerSec;							// переменная таймера 1 Сек
volatile uin32_t timer10usec;

void TIM3_IRQHandler(void);							// 1 sec Interval timer

void TIM2_IRQHandler(void);							// 1 sec timer
void TIM6_IRQHandler(void);

void TIM5_IRQHandler(void);
void ReklamaShow(void);
void UserValueInitialization(void);
void Timer_Sec(void);
void Timer10usec(void);

int main(void)
{
	uint8_t crcH,crcL;							// для проверки CRC
	uint16_t crc;

	//RCC_Config();
	SystemInit();

	gpio_init();
	UserValueInitialization();
	Delay_ms(30);
	LCD_ON();
	ReklamaShow();
	LCD_Display_Driver();
	USART_HOST_Config();
	NVIC_UART4_Config();

	uart_host.delay = 1;
	uart_host.rxgap = 0;
	uart_host.rxcnt = 0;
	uart_host.rxtimer = 0xFFFF;

	TIM2_Config();								// 1 sec timer
	TIM3_Config();								// 10 ms timer
	TIM6_Config();								// Timer HOST

	TIM5_Config();

    while(1)
    {

        if((uart_host.rxgap == 1) && (uart_host.rxcnt>2))
        {
        	Pin_Off(LED_PORT,LED_HOST);
        	crc = MBCRC16(uart_host.buffer_rx,uart_host.rxcnt - 2);

        	crcL = crc & 0x00FF;
        	crcH = (crc & 0xFF00) >> 8;

      //  if ((crcL == uart_host.buffer_rx[uart_host.rxcnt - 2]) && (crcH == uart_host.buffer_rx[uart_host.rxcnt - 1]))
     //   {
        	if((uart_host.buffer_rx[0] == AdressBP) || (uart_host.buffer_rx[0] == AdressAll))		// ответ от HOST
        	{
        		RxDispatchHOST();
        		uart_host.rxcnt = 0;
        		uart_host.rxgap = 0;
        		uart_host.rxtimer = 0xFFFF;
        	}
       // }
        	else
        	{
        		uart_host.rxcnt = 0;
        		uart_host.rxgap = 0;
        		uart_host.rxtimer = 0xFFFF;
        	}
       }

        Timer_Sec();
       	//Timer_10msec();
       	LCD_Display_Driver();
       	Keyboard_Driver();
    	//KeyButtonPressed();
    }
}

void TIM5_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM5,TIM_IT_Update)) != RESET)
	{
		Pin_Toggle(LED_PORT,LED2);
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}

void TIM2_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM2,TIM_IT_Update)) != RESET)
	{
		TimerSec++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}


void TIM3_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM3,TIM_IT_Update)) != RESET)
	{
		Timer10mSec++;

		if(TimerKeyFLAG == 0)
		{
			TimerKeyFLAG = 1;
		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}

}

void TIM6_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM6,TIM_IT_Update)) != RESET)
	{
	if((uart_host.rxtimer++ > uart_host.delay) & (uart_host.rxcnt > 1))
		{
			uart_host.rxgap = 1;
		}
		  else
		  {
			uart_host.rxgap = 0;
		  }

		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
	}
}

void UART4_IRQHandler(void)
{
	//Receive Data register not empty interrupt
 if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
   {
	 USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	 uart_host.rxtimer = 0;
	 uart_host.buffer_rx[uart_host.rxcnt++] = USART_ReceiveData (UART4);
   }

 if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)
   {
	 USART_ClearITPendingBit(UART4, USART_IT_TC);
	 if(uart_host.txcnt < uart_host.txlen)
		{

		  USART_SendData(UART4,uart_host.buffer_tx[uart_host.txcnt++]);
		 }
		else
		{
			uart_host.txlen = 0;
			HOST_DE_OFF();
		  	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
		  	USART_ITConfig(UART4, USART_IT_TC, DISABLE);
		}
	}
}

void Timer_Sec(void)
{
 if(TimerSec != 0)
 {
	Pin_Toggle(LED_PORT,LED1);

/*
	if (ReklamaTimer<ReklamaList)
	  {
	    ReklamaTimer++;
	    ReklamaShow();                    				// показывает рекламную заставку
	    if (ReklamaTimer == ReklamaList)
	    {
	      PsevdoCodButton = ButtonOK;
	      Tablo.OkButton = 100;           				// на просмотр текущ.состояния
	      KeyButtonPressed();             				// обработчик нажатия кнопок
	    }
	  }
	  else
	  {
	       if  (EditMode == Off) WriteToDispley(); 		// выдаем на экран - если не в редакторе
	      else
	      {
	       if (NumberPunkt == 536) WriteToDispley(); 	// обновляем экран для этого пункта
	      }
	  }
*/
	TimerSec = 0;
  }
}

void ReklamaShow(void)
{
  unsigned char m=0;
  unsigned char k;
  unsigned char p;

  for (k=0;k<2;k++)
  {
   for (p=0;p<24;p++)
	{
	   BuferLCD[m++] = ReklamaText[k][p];
	 }
  }

  LCDbusyFLAG = 1;
}

void UserValueInitialization(void)
{
	uint8_t j;

	CursorOnOff = Off;
	CursorX = 0;
	CursorX_save = 0;
	ReklamaTimer = 1;
	LCDbusyFLAG = 0;
	ButtonTek = ButtonNULL;
	TimerKeyFLAG = 0;

	PsevdoCodButton = ButtonNULL;

	ButtonNumber = 0;
	NumberKey = 0;

	PriznakStatusView = 0;
	ResetAlarmSummary = 0;
	TemporaryBitRateLCD = 0;
	AVARIA_SUMMARY_FLAQ = 0;
	PointerTekAvarion = 0;

	TimerSec = 0;
	Timer10mSec = 0;
	timer10usec = 0;

	for (j=0;j<9;j++)
	 {
	   Button0[j] = 0;
	   Button1[j] = 0;
	   ButtonPress[j] = 0;

	  }

}


#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "macros.h"
#include "keyboard.h"
#include "stdtypes.h"
#include "LCD.h"

#define LOBYTE(w)   ((char) (w))
#define HIBYTE(w)   ((char) ((w >> 8) & 0xFF))

#define BUF_SZ 64						  // размер буфера УАРТ 32 байта

//пароль доступа к параметрам
#define  PASSWORD   00000                  //временно, для отладки 14142
#define  AsWatchValue 300                 //время таймера спасателя АС, в секундах

//struct TIMER timers;
											//РАСКЛАДКА ПО SPI Flash
#define StAdr  0x10                                         //адрес, с которого начинаются хранимые данные в ЕЕПРОМ
#define Adress_ADDRES_RS485  StAdr                         //L=1 байт-  адрес в сети RS485
#define Adress_BitRate_RS485 Adress_ADDRES_RS485+1           //L=1 байт-  скорость в сети RS485 host
#define Adress_StatusLNB  Adress_BitRate_RS485+1             //L=1 байт - адрес, где хранится состояние LNB

#define Adress_MaxPorogLNB1  Adress_StatusLNB+1             //L=2 байта- адрес, где хранится макс.порог LNB1
#define Adress_MaxPorogLNB2  Adress_MaxPorogLNB1+2           //L=2 байта- адрес, где хранится макс.порог LNB2
#define Adress_MaxPorogLNB3  Adress_MaxPorogLNB2+2           //L=2 байта- адрес, где хранится макс.порог LNB2
#define Adress_MaxPorogLNB4  Adress_MaxPorogLNB3+2           //L=2 байта- адрес, где хранится макс.порог LNB2
#define Adress_MinPorogLNB1  Adress_MaxPorogLNB4+2           //L=2 байта- адрес, где хранится макс.порог LNB2
#define Adress_MinPorogLNB2  Adress_MinPorogLNB1+2           //L=2 байта- адрес, где хранится макс.порог LNB2
#define Adress_MinPorogLNB3  Adress_MinPorogLNB2+2           //L=2 байта- адрес, где хранится макс.порог LNB2
#define Adress_MinPorogLNB4  Adress_MinPorogLNB3+2           //L=2 байта- адрес, где хранится макс.порог LNB2
#define Adress_JornalAlarm   Adress_MinPorogLNB4+2           //26 байт на журнал

volatile FlagStatus FLAGwriteZAPROS_HOST;
volatile FlagStatus FLAGreadZAPROS_HOST;

unsigned char Timer10mSec;          // переменная таймера 10 мСек
unsigned char Timer10mSecTasck;     // счетчик таймера подзадач

struct ElementMenu
{
  unsigned char Info[24],Info2[24];
  unsigned int Up,Down,EscButton,OkButton;
  unsigned int Left,Right,AlarmButton,KrestButton,TypRedButton;
  unsigned char INVERSION,UpSTRELKA,DownSTRELKA,LeftSTRELKA,RightSTRELKA;
};
  //клавиатура
  //unsigned char TimerKeyFLAG; 				// флаг =1 пора проводить тестирование клавиатуры
  unsigned char NumberKey; 					// число проходов по клавиатуре
  unsigned char Button0[10]; 				// счетчик нулей
  unsigned char Button1[10]; 				// счетчик единиц
  unsigned char ButtonPress[10];			// состояние кнопок
  //описание  ButtonPress
  // 0 - кнопка не нажата
  // 1 - кнопка нажата, но не отработано нажатие
  // 2 - кнопка нажата, отработано нажатие
  // 3 - кнопка отпущена, но не отработано отпускание
 // unsigned char ButtonPressASK[10]; //квитанции  об отсылке кнопок в СОМ-порт
  unsigned char  PsevdoCodButton; 			// псевдокод кнопки
  unsigned char  ButtonNumber;				// просто номер нажатой кнопки

/*
 //СомПорт1 - шина HOSTBUS  - по этой шине работаем как SLAVE
 unsigned char TxPacketHOST[MAXBUFU1];//байтовый пакет на передачу
 unsigned char cntTxHOST = 0;//счетчик байт на передачу
 unsigned char PriemHOST = 0;//сброс флага приема
 unsigned char StatusRxHOST = 0; //признак приема
 unsigned char TimerGuardHOST = 0;//тайм-аут защиты приема по СОМ1
 unsigned char cntRxHOST = 0; //счетчик принятых  байтов
 unsigned char RxPacketHOST[MAXBUFU1];//принятый байтовый пакет
 unsigned char uartHOST_flagTrans = 0;//флаг сом1
 unsigned char cntOutHOST = 0; //счетчик передачи
 char *pointer_bufOutHOST; //указатель на массив передаваемых данных по СОМ1
 unsigned char FLAGwriteZAPROS_HOST = 0;//флаг запроса на запись в КЛУп
 unsigned char FLAGreadZAPROS_HOST = 0;//флаг запроса на чтение из КЛУп
*/

//переменные индикатора LCD
unsigned char CursorOnOff,CursorX;          //управление курсором
unsigned char EditMode;                     //флаг режима редактирования
struct ElementMenu Tablo;                   //запись для элемента меню

 unsigned int NumberPunkt;                  //текущий пункт меню
 unsigned int NumberPunktOLD;               //предыдущий пункт меню
 unsigned char BLANK;                       //для моргалки на ЖКИ
 unsigned char ReklamaTimer;                //переменная таймера для рекламы
 unsigned char ButtonTek;                   //текущая нажатая кнопка

  unsigned char TemporaryBitLCD;           //экранный буфер для битового числа
  unsigned char TemporaryNCharLCD;         //экранный буфер для char-числа N
  unsigned char TemporaryCharLCD;          //экранный буфер для char-числа NN
  unsigned short TemporaryShortLCD;        //экранный буфер для short-числа NNNN
  signed long TemporaryLongLCD;
  float TemporaryFloatLCD;
  unsigned char TemporaryNameLCD[10];      //массив имени

  unsigned long BufLong;
  unsigned char BufChar;
  unsigned char BufChar2;
  unsigned short BufShort;                     //буфер Short
  unsigned char TemporaryPriznakNChar;         //рисовать битовое число
  unsigned char TemporaryPriznakChar;          //рисовать char число
  unsigned short TemporaryPriznakShort;        //рисовать short число
  signed long TemporaryPriznakLong;

 unsigned char TemporaryBitRateLCD;

#define MAX_ALARM	4

 unsigned char MASSIV_AVARIA[MAX_ALARM];      	// массив аварий
 unsigned char PointerTekAvarion;         		// номер показываемой на ЖКИ аварии

 unsigned char AVARIA_SUMMARY_FLAQ; 	      // флаг общей аварии
 unsigned char ALARM_LNB_Current_Max[2];      // авария превышения тока LNB
 unsigned char ALARM_LNB_Current_Min[2];      // авария занижения тока LNB
 unsigned short LNB_Current[2];               // токи LNB
 unsigned char CurrentNumber;                 // текущийц номер измеряемого LNB
 unsigned short  CurrentPOROGmax[2];          // максимальный порог по току
 unsigned short  CurrentPOROGmin[2];          // минимальный порог по току


 unsigned char PriznakStatusView; 	        // признак - показать статус

 unsigned char ResetAlarmSummary; 		     // флаг общего сброса аварий
 unsigned char AdresRS485; 		            // адрес в сети RS485
 unsigned char BitRate; 	                // скорость в сети RS485 38400
 unsigned char CursorX_save;            	// запомненная позиция курсора

 unsigned char StatusLNB;                  // состояние LNB1-LNB2

typedef enum
{
  False = 0,
  True = 1
} Bool;

typedef struct
{
	unsigned char buffer_rx[BUF_SZ];
	unsigned char buffer_tx[BUF_SZ];
	unsigned int rxtimer;
	unsigned char rxcnt;
	unsigned char txcnt;
	unsigned char txlen;
	unsigned char rxgap;
	unsigned char delay;
} UART_DATA;

UART_DATA uart_host;

uint8_t ntp_time[8];							// время в формате NTP

#define  ReklamaList 2 							 // длительность в секундах рекламного ролика

#define  SETBIT(BYTE,BIT)    (BYTE |=  (1<<BIT))
#define  CLRBIT(BYTE,BIT)    (BYTE &= ~(1<<BIT))
#define  CHKBIT(BYTE,BIT)    (BYTE &   (1<<BIT))
#define  STATBIT(BYTE,BIT)   (1 & (BYTE>>BIT))
#define  INVERTBIT(BYTE,BIT) (BYTE ^= (1<<BIT))

#define AdressBP		0x06				// адрес ПУ (Панели Управления) со стороны HOST
#define AdressAll		0xFF

#define FuncRead		0x03				// Чтение регистра (2 байта)
#define FuncWrite		0x06				// Запись регистра (2 байта)
#define FuncDWrite		0x10				// запись 2 слов (4-х байт)

//====================================================================================================================================================
#define LED_ALARM  	 GPIO_Pin_11
#define LED_HOST     GPIO_Pin_12

#define LED1         GPIO_Pin_6
#define LED2         GPIO_Pin_7
#define LED3         GPIO_Pin_8
#define LED4         GPIO_Pin_9
#define LED_PORT	 GPIOC
//====================================================================================================================================================
#define LCD_CTRL	GPIOA
#define LCD_PORT	GPIOB

#define LCD_RS		 GPIO_Pin_1
#define LCD_RW		 GPIO_Pin_3
#define LCD_E		 GPIO_Pin_2

#define LCD_DB0		 GPIO_Pin_0
#define LCD_DB1		 GPIO_Pin_1
#define LCD_DB2		 GPIO_Pin_2
#define LCD_DB3		 GPIO_Pin_5
#define LCD_DB4		 GPIO_Pin_6
#define LCD_DB5		 GPIO_Pin_7
#define LCD_DB6		 GPIO_Pin_8
#define LCD_DB7		 GPIO_Pin_9
//====================================================================================================================================================
#define KN_COL1      GPIO_Pin_0
#define KN_PORT      GPIOC
#define KN1_CLK      RCC_APB2Periph_GPIOC

#define KN_COL2      GPIO_Pin_1
#define KN2_CLK      RCC_APB2Periph_GPIOC

#define KN_COL3      GPIO_Pin_2
#define KN3_CLK      RCC_APB2Periph_GPIOC

//====================================================================================================================================================
#define KN_STR1      GPIO_Pin_3
#define KN4_CLK      RCC_APB2Periph_GPIOC

#define KN_STR2      GPIO_Pin_4
#define KN5_CLK      RCC_APB2Periph_GPIOC

#define KN_STR3      GPIO_Pin_5
#define KN6_CLK      RCC_APB2Periph_GPIOC
//====================================================================================================================================================

//====================================================================================================================================================
#define pin_DE		GPIO_Pin_12
#define pin_TX		GPIO_Pin_10
#define pin_RX		GPIO_Pin_11
#define port_UART	GPIOC
//====================================================================================================================================================

#define port_SPI	GPIOA
#define SPI_SCK		GPIO_Pin_5
#define SPI_MISO	GPIO_Pin_6
#define SPI_MOSI	GPIO_Pin_7
#define CS_AT45		GPIO_Pin_8

//====================================================================================================================================================
void RCC_Config(void);

void Delay_ms(__IO uint32_t nTime);
inline void DelayLoop(uint32_t delayLoops);		// задержка

void gpio_init(void);

void LCD_Port_Set_Output(void);
void TIM2_Config(void);							// status timer
void TIM3_Config(void);							// timer keyboard
void TIM6_Config(void);

void TIM5_Config(void);
//====================================================================================================================================================

void USART_HOST_Config(void);					// UART4 M & C
void NVIC_UART4_Config(void);
//====================================================================================================================================================
inline void KN_STR_ON(GPIO_TypeDef* Port, uint16_t Pin);
inline void KN_STR_OFF(GPIO_TypeDef* Port, uint16_t Pin);

inline Bool Check_Bit(GPIO_TypeDef* Port, uint16_t Pin);

inline void Tx_ON();
inline void Tx_OFF();

inline void HOST_DE_OFF(void);
inline void HOST_DE_ON(void);

inline void CS_ON();
inline void CS_OFF();

inline void Pin_Toggle(GPIO_TypeDef*, uint16_t );
inline void Pin_Off(GPIO_TypeDef*, uint16_t );
inline void Pin_On(GPIO_TypeDef*, uint16_t);


#endif /* CONFIG_H_ */


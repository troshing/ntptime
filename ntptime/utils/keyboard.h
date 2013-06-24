#ifndef _keyboard_H
#define _keyboard_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "config.h"
//обозначения клавиш

#define ButtonNULL        0
#define ButtonLeft        1
#define ButtonUP          2
#define ButtonRight       3
#define ButtonDown        4
#define ButtonOK          5
#define ButtonRedit       6
#define ButtonALARM       7
#define ButtonKrest       8
#define ButtonESCAPE      9
#define ButtonAR          10

#define NumberKeyDefault 		10			// антидребезг по клавиатуре
/*
  описание  ButtonPress
   0 - кнопка не нажата
   1 - кнопка нажата, но не отработано нажатие
   2 - кнопка нажата, отработано нажатие
   3 - кнопка отпущена, но не отработано отпускание
   */

//клавиатура

  unsigned char NumberKey; 						// число проходов по клавиатуре
  unsigned char Button0[10]; 					// счетчик нулей
  unsigned char Button1[10]; 					// счетчик единиц
  unsigned char ButtonPress[10];				// состояние кнопок
  unsigned char  PsevdoCodButton; 				// псевдокод кнопки
  unsigned char  ButtonNumber;					// просто номер нажатой кнопки
  unsigned char ButtonTek;						// текущая нажатая кнопка

volatile unsigned char TimerKeyFLAG;

//====================================================================================================================================================

void Keyboard_Driver(void); 		// сканирует кнопки и пишет их в массив KeyButton[6]

#endif

#ifndef _keyboard_H
#define _keyboard_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "config.h"
//����������� ������

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

#define NumberKeyDefault 		10			// ����������� �� ����������
/*
  ��������  ButtonPress
   0 - ������ �� ������
   1 - ������ ������, �� �� ���������� �������
   2 - ������ ������, ���������� �������
   3 - ������ ��������, �� �� ���������� ����������
   */

//����������

  unsigned char NumberKey; 						// ����� �������� �� ����������
  unsigned char Button0[10]; 					// ������� �����
  unsigned char Button1[10]; 					// ������� ������
  unsigned char ButtonPress[10];				// ��������� ������
  unsigned char  PsevdoCodButton; 				// ��������� ������
  unsigned char  ButtonNumber;					// ������ ����� ������� ������
  unsigned char ButtonTek;						// ������� ������� ������

volatile unsigned char TimerKeyFLAG;

//====================================================================================================================================================

void Keyboard_Driver(void); 		// ��������� ������ � ����� �� � ������ KeyButton[6]

#endif

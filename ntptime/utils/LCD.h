#ifndef __LCD_H
#define __LCD_H

#include "config.h"


// Этот раздел не править!!!!!!!
#define	Shift		0x1C
#define Max_Column	0x3F			// 256/4-1
#define Max_Row		0x3F			// 64-1
#define	Brightness	0x0F

//========================================================
// Этот раздел можно частично править

#define String1_Column    0       // позиция начала строки 1 по оси Х ( не править )
#define String2_Column    0       // позиция начала строки 2 по оси Х ( не править )

// настройка промежутка между строками!!!!!!!!!!!!!!
// рекомендуется менять разность между String2_High_Row и String1_High_Row - 
// это есть промежуток между строками (разность >= 10)
#define String1_High_Row  10      // позиция строки 1 по оси Y (верхняя точка) ( можно править )
#define String1_Low_Row   (String1_High_Row + 8) //( не править )
#define String2_High_Row  30      // позиция строки 2 по оси Y (верхняя точка) ( можно править )
#define String2_Low_Row   (String2_High_Row + 8) //( не править )

// настройка положения картинки по осям Х и Y !!!!!!!!!!!!!!!
#define	XShift		0   // сдвиг картинки по оси Х
#define	YShift		0   // сдвиг картинки по оси Y

//============================================================================================================================
//управление курсором
#define Off            0
#define On             1
//============================================================================================================================
unsigned char BuferLCD[48];				//обменная страница LCD
unsigned char TabloLCD[48];				//страница экрана LCD
unsigned char LCDbusyFLAG;				// флаг ЖКИ

unsigned char CursorOnOff,CursorX;
//============================================================================================================================
//объявления функций
void LCD_ON( void );                                //Включение LCD
unsigned char Cyr_to_LCD( unsigned char Symbol );   //Конвертит русские буквы в шрифт LCD     
void LCD_Display_Driver( void );                    //сравнивает страницы из буфера и экрана, если не совпадают,то обновляет экран

void LCD_CursorXY( unsigned char CursorX );

//==========================================   прототипы локальных функций OLED   ================================================
void OLED_Init( void );

unsigned char CharToOLED(unsigned char ch, unsigned char cIndex);
void OLED_PrintSymbol(unsigned char cPos, unsigned char bCursor);

void OLED_LoadCommand (unsigned char Data);
void OLED_LoadChar (unsigned char Data);

void OLED_Set_Column_Address (unsigned char a, unsigned char b);
void OLED_Set_Row_Address (unsigned char a, unsigned char b);
void OLED_Set_Write_RAM();
void OLED_Set_Read_RAM();
void OLED_Set_Remap_Format (unsigned char d);
void OLED_Set_Start_Line (unsigned char d);
void OLED_Set_Display_Offset (unsigned char d);
void OLED_Set_Display_Mode (unsigned char d);
void OLED_Set_Partial_Display (unsigned char a, unsigned char b, unsigned char c);
void OLED_Set_Function_Selection (unsigned char d);
void OLED_Set_Display_On_Off (unsigned char d);
void OLED_Set_Phase_Length (unsigned char d);
void OLED_Set_Display_Clock (unsigned char d);
void OLED_Set_Display_Enhancement_A (unsigned char a, unsigned char b);
void OLED_Set_GPIO (unsigned char d);
void OLED_Set_Precharge_Period (unsigned char d);
void OLED_Set_Precharge_Voltage (unsigned char d);
void OLED_Set_VCOMH (unsigned char d);
void OLED_Set_Contrast_Current (unsigned char d);
void OLED_Set_Master_Current (unsigned char d);
void OLED_Set_Multiplex_Ratio (unsigned char d);
void OLED_Set_Display_Enhancement_B (unsigned char d);
void OLED_Set_Command_Lock (unsigned char d);
void OLED_Fill_RAM (unsigned char cData);
void OLED_Set_Gray_Scale_Table();

//============================================================
#endif

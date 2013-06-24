#include "Modbus_H.h"

void RxDispatchHOST(void)
{
	unsigned char Buf = 0;
	unsigned char Buf2 = 0;
	unsigned char NumByte;
	uint16_t i;
	uint16_t KolvoRegistrov;
	uint16_t StartReadRegistr;
	uint16_t WriteRegistr;
	uint16_t WriteValue;
	uint16_t BufShort;
	unsigned char ErrorFlag = 0;
	float BufFLOAT;

	if(uart_host.buffer_rx[1] == FuncRead)
	{
		Pin_Toggle(LED_PORT,LED2);

		StartReadRegistr = (uart_host.buffer_rx[2]<<8) | uart_host.buffer_rx[3];

		KolvoRegistrov = (uart_host.buffer_rx[4]<<8) | uart_host.buffer_rx[5];
		uart_host.txlen = 0;

		uart_host.buffer_tx[uart_host.txlen++] = AdresRS485;					// [0]
		uart_host.buffer_tx[uart_host.txlen++] = 0x03;							// [1]
		uart_host.buffer_tx[uart_host.txlen++] = uart_host.buffer_rx[3];

		for(i = 0;i < KolvoRegistrov;i++)
		{
			if((StartReadRegistr>0) && (StartReadRegistr<25))
			{
				NumByte = (unsigned char)(StartReadRegistr & 0xFF);

				if (NumByte == 1)
				   {
						uart_host.buffer_tx[uart_host.txlen++] = TabloLCD[0];
						uart_host.buffer_tx[uart_host.txlen++] = TabloLCD[1];
				   }
				else
				  {
				     NumByte = NumByte + (NumByte-2);
				     uart_host.buffer_tx[uart_host.txlen++] = TabloLCD[NumByte];
				     uart_host.buffer_tx[uart_host.txlen++] = TabloLCD[NumByte+1];
				   }
			}
			else
			{
				switch(StartReadRegistr)
				{
					case 0:
					{

						break;
					}
					case 25:												// ток 27V
					{
						break;
					}
					case 26:
					{

						break;
					}
					case 27:
					{

						break;
					}
					case 28:
					{

						break;
					}
					case 30:
					{

						break;
					}
					case 31:
					{

						break;
					}
					case 32:
					{

						break;
					}
					case 33:
					{

						break;
					}
					case 34:
					{

						break;
					}
					case 35:
					{

						break;
					}
					case 36:
					{

						break;
					}
					case 37:
					{

						break;
					}
					case 38:
					{

						break;
					}
					case 39:
					{


						uart_host.buffer_tx[uart_host.txlen++] = 0xFF;			// ст байт
						uart_host.buffer_tx[uart_host.txlen++] = 0xF5;			// мл байт
						break;
					}
					case 40:
					{

						break;
					}
					case 41:
					{

						break;
					}
					case 42:
					{

						break;
					}
					case 43:
					{

						break;
					}
					case 44:
					{

						break;
					}
					case 45:
					{

						break;
					}
					case 46:
					{

						break;
					}
					case 47:
					{

						break;
					}
					case 48:
					{

						break;
					}
					case 49:
					{

						break;
					}

					case 104:
					case 105:
					case 106:
					case 107:
					case 108:
					case 109:
					case 110:
					case 111:
					case 112:
					{

						break;
					}
					default:
					{
						uart_host.buffer_tx[uart_host.txlen++] = 0x86;
						uart_host.buffer_tx[uart_host.txlen++] = 0x01;
						break;
					}
				}
			}
		StartReadRegistr++;
		}

		SendHOST(uart_host.buffer_tx,uart_host.txlen);
	}

	if(uart_host.buffer_rx[1] == FuncDWrite)
	{
		Pin_Toggle(LED_PORT,LED4);
		//
	}

	if(uart_host.buffer_rx[1] == FuncWrite)
	{
		Pin_Toggle(LED_PORT,LED3);
		WriteRegistr = (uart_host.buffer_rx[2]<<8) | uart_host.buffer_rx[3];
		WriteValue = (uart_host.buffer_rx[4]<<8) | uart_host.buffer_rx[5];
		uart_host.txlen = 0;

		if(WriteRegistr != 29)
		{
			switch(WriteRegistr)
			{
			case 30:
			{
				break;
			}
			case 31:
			{

			    break;
			}
			case 32:
			{

				break;
			}
			case 33:
			{

				break;
			}
			case 34:
			{

				break;
			}
			case 35:
			{

				break;
			}
			case 36:
			{

				break;
			}
			case 37:
			{

				break;
			}
			case 38:
			{

				break;
			}
			case 39:
			{
				break;
			}

			case 104:
			case 105:
			case 106:
			case 107:
			case 108:
			case 109:
			case 110:
			case 111:
			{

				break;
			}
			case 112:
			{

				break;
			}
			case 0xFFFF:
			{
				//
			}
			default:
			{
				ErrorFlag = 1;
			}

			}
		}
		else
		{
			switch(WriteValue)
			{
				case 0:
				{
					PsevdoCodButton = ButtonNULL;
					break;
				}
				case 1:
				{
					PsevdoCodButton = ButtonLeft;
					break;
				}
				case 2:
				{
					PsevdoCodButton = ButtonUP;
					break;
				}
				case 3:
				{
					PsevdoCodButton = ButtonRight;
					break;
				}
				case 4:
				{
					PsevdoCodButton = ButtonDown;
					break;
				}
				case 5:
				{
					PsevdoCodButton = ButtonOK;
					break;
				}
				case 6:
				{
					PsevdoCodButton = ButtonRedit;
					break;
				}
				case 7:
				{
					PsevdoCodButton = ButtonALARM;
					break;
				}
				case 8:
				{
					PsevdoCodButton = ButtonKrest;
					break;
				}
				case 9:
				{
					PsevdoCodButton = ButtonESCAPE;
					break;
				}
				case 10:
				{
					PsevdoCodButton = ButtonAR;
					break;
				}
				default:
				{
					PsevdoCodButton = ButtonNULL;
					break;
				}
			}
		 if (PsevdoCodButton != ButtonNULL)  ErrorFlag = 0;
		}

		if(ErrorFlag == 0)
		{
			uart_host.buffer_rx[uart_host.txlen++] = AdresRS485;
			uart_host.buffer_rx[uart_host.txlen++] = 0x06;
			uart_host.buffer_rx[uart_host.txlen++] = (unsigned char)((WriteRegistr & 0xFF00)>>8);
			uart_host.buffer_rx[uart_host.txlen++] = (unsigned char)(WriteRegistr & 0xFF);

			uart_host.buffer_rx[uart_host.txlen++] = (unsigned char)((WriteValue & 0xFF00)>>8);
			uart_host.buffer_rx[uart_host.txlen++] = (unsigned char)(WriteValue & 0xFF);

			SendHOST(uart_host.buffer_tx,uart_host.txlen);
		}
		else
		{
			uart_host.buffer_rx[uart_host.txlen++] = AdresRS485;
			uart_host.buffer_rx[uart_host.txlen++] = 0x86;
			uart_host.buffer_rx[uart_host.txlen++] = 0x01;

			SendHOST(uart_host.buffer_tx,uart_host.txlen);
		}
	}
}

void SendHOST(uint8_t* buffer,uint8_t cnt)
{
	uint8_t i;
	uint16_t crc;

	uart_host.txcnt = 0;

	crc = MBCRC16(uart_host.buffer_tx,uart_host.txlen);

	uart_host.buffer_tx[uart_host.txlen++] = LOBYTE(crc);
	uart_host.buffer_tx[uart_host.txlen++] = HIBYTE(crc);

	uart_host.txcnt = 0;

	HOST_DE_ON();

	USART_ITConfig(UART4, USART_IT_TC, ENABLE);
	USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);

	USART_SendData(UART4, uart_host.buffer_tx[uart_host.txcnt++]);
}

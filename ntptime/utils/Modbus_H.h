#ifndef	_Modbus_H
#define _Modbus_H


#include "mbcrc.h"
#include "config.h"


uint8_t buffer_rx[8];


void RxDispatchHOST(void);							// ������ �������� ������ �� ���

void SendHOST(uint8_t*, uint8_t);					// �������� ������ � ���


#endif

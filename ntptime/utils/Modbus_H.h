#ifndef	_Modbus_H
#define _Modbus_H


#include "mbcrc.h"
#include "config.h"


uint8_t buffer_rx[8];


void RxDispatchHOST(void);							// парсер принятых данных от АРМ

void SendHOST(uint8_t*, uint8_t);					// отправка данных в АРМ


#endif

#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

#include "main.h"
#include "menu.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define COMMANDS_BUFFER_SIZE 100

void bluetooth_IRQHandler(void);
void bluetooth_CommandsHandler(void);
void bluetooth_Init(void);

#endif

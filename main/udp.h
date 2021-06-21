/**
  ******************************************************************************
  * @file    udp.h
  * @author  Pichugin Nickita
  * @version V0.0.1
  * @date    21.06.2021
  * @brief   This file contains all UDP public functions
  ******************************************************************************
  */
#ifndef __UDP_H
#define __UDP_H
#include "defines.h"
TaskHandle_t xTask_udp_handle;
void udp_task(void *pvParameters);
#endif
/**
  ******************************************************************************
  * @file    udp.h
  * @author  Pichugin Nickita
  * @version V1.0.0
  * @date    21.06.2021
  * @brief   This file contains all UDP public functions
  ******************************************************************************
  */
#ifndef __UDP_H
#define __UDP_H
#include "defines.h"
TaskHandle_t xTask_udp_handle;
TaskHandle_t xTask_udp_2_handle;

char udp_ip[64];
uint16_t udp_port;

void udp_task(void *arg);
#endif
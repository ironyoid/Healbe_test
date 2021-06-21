/**
  ******************************************************************************
  * @file    uart.h
  * @author  Pichugin Nickita
  * @version V1.0.0
  * @date    21.06.2021
  * @brief   This file contains all UART public functions
  ******************************************************************************
  */
#ifndef __UART_H
#define __UART_H
#include "defines.h"
int8_t *receive_data;
esp_err_t uart_init();
void uart_task(void *arg);
TaskHandle_t xTask_uart_handle;
#endif
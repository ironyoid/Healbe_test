/**
  ******************************************************************************
  * @file    defines.h
  * @author  Pichugin Nickita
  * @version V1.0.0
  * @date    21.06.2021
  * @brief   This file contains all the defines
  ******************************************************************************
  */
#ifndef __DEFINES_H
#define __DEFINES_H

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/api.h"
#include "lwip/netdb.h"
#include "lwip/netbuf.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/sockets.h"
#include <lwip/netdb.h>
#include "driver/uart.h"
SemaphoreHandle_t   xUDP_sync_semaphore;
#define LEN_MAC_ADDR                20
#define ESP_WIFI_SSID               "Keenetic-5919"     /*Add your AP SSID here */
#define ESP_WIFI_PASS               "2kcdbL5b"          /*Add your AP password here */
#define MAX_STA_CONN                16
#define CSI_QUEUE_LEN               10
#define MAC_LIST_LEN                16                  /*Maximal number of transmitters */
#define NUMBER_OF_CHARS             18                  /* Yep, 18 - magic number from desdoc */
#define MOVING_AVERAGE_WINDOW       5                   /* Yep, I have just decided that */
#define UDP_IP                      "192.168.88.172"
#define UDP_PORT                    6350
#endif
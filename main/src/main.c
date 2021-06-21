/**
  ******************************************************************************
  * @file    main.c
  * @author  Pichugin Nickita
  * @version V1.0.0
  * @date    21.06.2021
  * @brief   This file contains all main routine
  ******************************************************************************
  */
#include "defines.h"
#include "wifi.h"
#include "udp.h"
#include "uart.h"
static const char *TAG = "HEALBE_TEST_MAIN";

/* It's necessary for Wi-Fi */
static void nvs_init() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void app_main() {
    xUDP_sync_semaphore = xSemaphoreCreateMutex(); 
    nvs_init();
    sta_init();
    uart_init();
    xTaskCreate(&udp_task, "udp_task", 2048, NULL, 18, &xTask_udp_handle);      /* higher than the  task to immediately switch */
    xTaskCreate(&uart_task, "uart_task", 2048, NULL, 17, &xTask_uart_handle);
}

/**
  ******************************************************************************
  * @file    uart.c
  * @author  Pichugin Nickita
  * @version V1.0.0
  * @date    21.06.2021
  * @brief   This file contains UART task
  ******************************************************************************
  */
#include "inc/uart.h"
#define DEBUG
static const char *TAG = "UART";
/**
 * @brief   Initialisation Tuya module and USART
 * @param   Null
 * @return  Error
 * @note    
 */
esp_err_t uart_init()
{
    esp_err_t answear = ESP_OK;
    uart_driver_delete(UART_NUM_1);
    uart_config_t uart_config = {
        .baud_rate = 57600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_2,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
    };
#ifdef DEBUG
    ESP_LOGW(TAG, "Start configure UART");
    ESP_LOGW(TAG, "UART set pins, mode and install driver.");
#endif
    // Configure UART parameters
    ESP_ERROR_CHECK_WITHOUT_ABORT(uart_param_config(UART_NUM_1, &uart_config));

    // Set UART1 pins(TX: IO9, RX: I010, RTS: IO18, CTS: IO19)
    if (uart_set_pin(UART_NUM_1, GPIO_NUM_9, GPIO_NUM_10, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ESP_OK)
    {
        answear = ESP_FAIL;
    }
    // Install UART driver (we don't need an event queue here)
    // In this example we don't even use a buffer for sending data.
    if ((answear != ESP_FAIL) && (uart_driver_install(UART_NUM_1, 256, 256, 0, NULL, 0) != ESP_OK))
    {
        answear = ESP_FAIL;
    }
    // Set regular UART mode
    if ((answear != ESP_FAIL) && (uart_set_mode(UART_NUM_1, UART_MODE_UART) != ESP_OK))
    {
        answear = ESP_FAIL;
    }
    receive_data = (int8_t *)malloc(128);

    if (receive_data == NULL)
    {
        answear = ESP_FAIL;
    }

    return answear;
}

void uart_task(void *arg)
{
    uint16_t num_of_bytes_received = 0;
    while (1)
    {
        ESP_LOGE(TAG, "Block task and wait NUMBER_OF_CHARS in FIFO...");
        num_of_bytes_received = uart_read_bytes(UART_NUM_1, (uint8_t *)receive_data,
                                                NUMBER_OF_CHARS, portMAX_DELAY); /* Zero ticks to wait bc we actually 
                        `                                                               trust the transmitter 
                                                                                        (never do that in real project) */
        ESP_LOGW(TAG, "We've got it! Read 18 bytes...");
        uart_flush(UART_NUM_1);
#ifdef DEBUG
        ESP_LOGW(TAG, "Read %d bytes...", num_of_bytes_received);
        ESP_LOG_BUFFER_HEXDUMP(TAG, receive_data, num_of_bytes_received, ESP_LOG_WARN);
#endif
        ESP_LOGI(TAG, "So, now just sleep in 30 seconds...");
        xSemaphoreGive(xUDP_sync_semaphore);
        vTaskDelay(30000 / portTICK_PERIOD_MS);
    }
}
#include "uart.h"
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
    if (uart_set_pin(UART_NUM_1, GPIO_NUM_10, GPIO_NUM_9, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ESP_OK)
    {
        answear = ESP_FAIL;
    }
    // Install UART driver (we don't need an event queue here)
    // In this example we don't even use a buffer for sending data.
    if ((answear != ESP_FAIL) && (uart_driver_install(UART_NUM_1, 2048, 2048, 0, NULL, 0) != ESP_OK))
    {
        answear = ESP_FAIL;
    }
    // Set regular UART mode
    if ((answear != ESP_FAIL) && (uart_set_mode(UART_NUM_1, UART_MODE_UART) != ESP_OK))
    {
        answear = ESP_FAIL;
    }
     receive_data = (int8_t *)malloc(18);

    return answear;
}

void uart_task(void *arg)
{

    while(1)
    {
        ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_1, (size_t*)&num_of_bytes_buffer));
        num_of_bytes_received = uart_read_bytes(UART_NUM_1, (uint8_t *)receive_data, num_of_bytes_buffer, 300 / portTICK_PERIOD_MS); 
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

}
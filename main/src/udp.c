/**
  ******************************************************************************
  * @file    udp.c
  * @author  Pichugin Nickita
  * @version V1.0.0
  * @date    21.06.2021
  * @brief   This file contains all UDP task and SMA filter
  ******************************************************************************
  */
#include "udp.h"
#include "uart.h"
static const char *TAG = "HEALBE_TEST_UDP";
#define DEBUG

/**
 * @brief   Simple moving average filter for buffer
 * @param   data - int8_t data, note that it's mutable!
 * @return  void
 * @note    
 */
static void sma_filter(int8_t *data)
{
    static uint8_t n;
    static int8_t m[MOVING_AVERAGE_WINDOW][NUMBER_OF_CHARS];

    memcpy(&m[n][0], data, NUMBER_OF_CHARS*sizeof(int8_t));

    for (uint8_t i = 0; i < NUMBER_OF_CHARS; i++)
    {
        data[i] = 0;
        for (uint8_t j = 0; j < MOVING_AVERAGE_WINDOW; j++)
        {
            data[i] = data[i] + m[j][i];
        }
        data[i] = data[i] / MOVING_AVERAGE_WINDOW;
    }
    n = (n + 1) % MOVING_AVERAGE_WINDOW;

}

/**
 * @brief   UDP task 
 * @param   pvParameters
 * @return  void
 * @note    
 */
void udp_task(void *arg)
{
    int addr_family = 0;
    int ip_protocol = 0;
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    dest_addr.sin_addr.s_addr = inet_addr(UDP_IP);
    dest_addr.sin_port = htons(UDP_PORT);
    while (1)
    {
        xSemaphoreTake(xUDP_sync_semaphore, portMAX_DELAY );    /* waiting for UART */
        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0)
        {
#ifdef DEBUG
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
#endif
        }
        else
        {
#ifdef DEBUG
            ESP_LOGI(TAG, "Socket created, sending to %s:%d", UDP_IP, UDP_PORT);
#endif
            sma_filter(receive_data);
            ESP_LOG_BUFFER_HEXDUMP(TAG, receive_data, NUMBER_OF_CHARS*sizeof(int8_t), ESP_LOG_WARN);
            /* Started from data.rx_ctrl and go to mac */
            int err = sendto(sock, receive_data, NUMBER_OF_CHARS*sizeof(int8_t), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
            if (err < 0)
            {
#ifdef DEBUG
                ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
#endif
            }
            else
            {
#ifdef DEBUG
                ESP_LOGI(TAG, "Message sent");
#endif
                if (sock != -1)
                {
#ifdef DEBUG
                    ESP_LOGE(TAG, "Shutting down socket and restarting...");
#endif
                    shutdown(sock, 0);
                    close(sock);
                }
            }
        }
    }
}
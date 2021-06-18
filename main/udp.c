#include "udp.h"

static const char *TAG = "HEALBE_TEST_UDP";
//#define DEBUG
/**
 * @brief   UDP task 
 * @param   pvParameters
 * @return  void
 * @note    
 */
void udp_task(void *arg)
{
    portBASE_TYPE xStatus = pdTRUE;
    int addr_family = 0;
    int ip_protocol = 0;
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    while (1)
    {

        wifi_csi_info_t data;
       // xStatus = xQueueReceive(csi_queue, &data, portMAX_DELAY);
        if (xStatus == pdPASS)
        {
            if ((udp_ip[0] != '\0') && (udp_port != 0))
            {
                dest_addr.sin_addr.s_addr = inet_addr(udp_ip);
                dest_addr.sin_port = htons(udp_port);
               // if (check_mac_list(data.mac) != -1)
                {
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
                        ESP_LOGI(TAG, "Socket created, sending to %s:%d", udp_ip, udp_port);
#endif
                        /* Started from data.rx_ctrl and go to mac */
                        int err = sendto(sock, &data.rx_ctrl, sizeof(data.rx_ctrl) + sizeof(data.mac), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
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
        }
        else
        {
#ifdef DEBUG
            ESP_LOGE(TAG, "Could not recive data from the queue...");
#endif
        }
#ifdef DEBUG
        printf("\n");
#endif
    }
}
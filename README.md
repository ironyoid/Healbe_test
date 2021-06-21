#  Healbe_test

## Architecture
There are three main functions: 
- udp_task - Task which takes UART data and send it by UDP
- uart_task - Task which wakes up every 30 seconds to read 18 bytes from UART FIFO. If FIFO is empty, task blocked until data will receive 
- sma_filter - Simple moving average filter for buffer

## Settings
- ESP_WIFI_SSID - your Wi-Fi router SSID
- ESP_WIFI_PASS - your Wi-Fi router password
- NUMBER_OF_CHARS - UART data size
- MOVING_AVERAGE_WINDOW - SMA window size
- UDP_IP - your UDP node IP adress
- UDP_PORT - your UDP node port

## How to build
Just downolad project and build with
```c
idf.py build
```
## Note
- We should fill SMA first, that's why firts MOVING_AVERAGE_WINDOW transmission are useless
- UART code is totally useless in real apps, because it based on assumption that the transmitter is a really good guy who knows timings and send only 18 bytes per 30 seconds

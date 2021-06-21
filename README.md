#  Healbe_test

## Architecture
There are three main functions: 
- udp_task - Task which takes UART data and send it by UDP
- uart_task - Task which wakes up every 30 seconds to read 18 bytes from UART FIFO. If FIFO is empty, task blocked until data will receive 
- sma_filter - Simple moving average filter for buffer

## DE
## How to build
Just downolad project and build with
```c
idf.py build
```
## Note
- We should fill SMA first, that's why firts MOVING_AVERAGE_WINDOW transmission are useless

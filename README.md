# README

1. Run the user app on the device
2. Connect USART2 of the P2 to an FTDI that connects to computer. On P2:
```
#define TX1                 D4
#define RX1                 D5
#define CTS1                D3
#define RTS1                D2
```
3. Run the python app - Change the Serial port. Baud / other settings need to be modified with in the app if needed
4. Ensure flow control is working; You will see that the data is transfered continuously both ways. Momentarily disconnect CTS line and verify that data should stop

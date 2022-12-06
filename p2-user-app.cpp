#include "Particle.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

SerialLogHandler lg(LOG_LEVEL_ALL);

const auto rxBufSize = 32;
const auto txBufSize = 32;

uint8_t txBuff[txBufSize] = {};
uint8_t rxBuff[rxBufSize] = {};

hal_usart_interface_t serial = HAL_USART_SERIAL2;

void setup() {

    hal_usart_buffer_config_t c = {
        .size = sizeof(hal_usart_buffer_config_t),
        .rx_buffer = new (std::nothrow) uint8_t[rxBufSize],
        .rx_buffer_size = rxBufSize,
        .tx_buffer = new (std::nothrow) uint8_t[txBufSize],
        .tx_buffer_size = txBufSize
    };

    hal_usart_init_ex(serial, &c, nullptr);

    uint32_t config = SERIAL_8N1 | SERIAL_FLOW_CONTROL_RTS_CTS;
    hal_usart_begin_config(serial, 460800, config, 0);

}

void loop() {
    Particle.process();
    bool txData = false;
    int availBytes = hal_usart_available(serial);
    // Read through continuously
    if (availBytes > 0) {
        memset(rxBuff, 0, sizeof(rxBuff));
        auto bytesRead = hal_usart_read_buffer(serial, rxBuff, availBytes, sizeof(char));
        Log.info("Bytes read: %d / %s", bytesRead, rxBuff);
        txData = true;
    }
    if (txData) {
        int txBytes = random(1, txBufSize);
        for (int i = 0; i < txBytes; i++) {
            txBuff[i] = 'a';
            hal_usart_write_buffer(serial, txBuff, txBufSize, sizeof(char));
            Log.info("TX Done : %d", txBytes);
        }
    }
}
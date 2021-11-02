#include "uart_hub.h"
#include "uart.h"

#define BUFFER_SIZE 128
#define UART1_INSTANCE 0
#define UART2_INSTANCE 1

static uart_config_t uart1_config;
static uart_config_t uart2_config;

static struct {
    uint8_t read[BUFFER_SIZE];
    uint8_t write[BUFFER_SIZE];
    uint16_t index;
} buffer;

static void uart1_handler(uart_event_t const *p_event)
{
    switch (p_event->type) {
        case UART_EVENT_TYPE_TX_DONE:
            // not used
            break;
        case UART_EVENT_TYPE_RX_BYTE_READY:
            buffer.read[buffer.index] = p_event->rx_byte;
            if (++buffer.index >= BUFFER_SIZE)
            {
                buffer.index = 0;
                memcpy(buffer.write, buffer.read, BUFFER_SIZE);
                memset(buffer.read, 0, BUFFER_SIZE);
                uart_ret_code_t err = uart_write(UART1_INSTANCE, buffer.write, BUFFER_SIZE);
                if (err != UART_RET_CODE_SUCCESS)
                {
                    // handle error
                }
            }
            break;
        case UART_EVENT_TYPE_ERROR:
            // handle error
            break;
    }
}

static void uart2_handler(uart_event_t const *p_event)
{
    switch (p_event->type) {
        case UART_EVENT_TYPE_TX_DONE:
            // does not need to be used because rx uart1 speed < tx uart2 speed
            break;
        case UART_EVENT_TYPE_RX_BYTE_READY:
            // not used
            break;
        case UART_EVENT_TYPE_ERROR:
            // handle error
            break;
    }
}

void uart_hub_init()
{
    uart1_config.baudrate = UART_BAUDRATE_9600;
    uart1_config.parity = UART_PARITY_BIT_DISABLE;
    uart1_config.stop_bit = UART_STOP_BIT_1;

    uart2_config.baudrate = UART_BAUDRATE_115200;
    uart2_config.parity = UART_PARITY_BIT_DISABLE;
    uart2_config.stop_bit = UART_STOP_BIT_1;

    uart_init(UART1_INSTANCE, &uart1_config, uart1_handler);
    uart_init(UART2_INSTANCE, &uart2_config, uart2_handler);
}

void test_wrapper_uart1_handler(uart_event_t const *p_event)
{
    uart1_handler(p_event);
}

void test_wrapper_uart2_handler(uart_event_t const *p_event)
{
    uart2_handler(p_event);
}


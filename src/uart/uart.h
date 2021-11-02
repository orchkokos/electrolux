#ifndef ELECROLUX_UART_H
#define ELECROLUX_UART_H

typedef enum {
    UART_RET_CODE_SUCCESS,
    UART_RET_CODE_SOME_MISTAKE,
} uart_ret_code_t;

typedef enum
{
    UART_EVENT_TYPE_TX_DONE,
    UART_EVENT_TYPE_RX_BYTE_READY,
    UART_EVENT_TYPE_ERROR,
} uart_event_type_t;

typedef enum
{
    UART_EVENT_ERROR_SOME_MISTAKE,
} uart_event_error_t;

typedef struct
{
    uart_event_type_t type;
    union
    {
        uint8_t rx_byte;
        uart_event_error_t error;
    };
} uart_event_t;

typedef void (*uart_event_handler_t)(uart_event_t const *p_event);

typedef enum
{
    UART_BAUDRATE_1200,
    UART_BAUDRATE_2400,
    UART_BAUDRATE_4800,
    UART_BAUDRATE_9600,
    UART_BAUDRATE_14400,
    UART_BAUDRATE_19200,
    UART_BAUDRATE_28800,
    UART_BAUDRATE_31250,
    UART_BAUDRATE_38400,
    UART_BAUDRATE_56000,
    UART_BAUDRATE_57600,
    UART_BAUDRATE_76800,
    UART_BAUDRATE_115200,
    UART_BAUDRATE_230400,
    UART_BAUDRATE_250000,
    UART_BAUDRATE_460800,
    UART_BAUDRATE_921600,
} uart_baudrate_t;

typedef enum
{
    UART_PARITY_BIT_DISABLE,
    UART_PARITY_BIT_ENABLE,
} uart_parity_bit_t;

typedef enum
{
    UART_STOP_BIT_0_5,
    UART_STOP_BIT_1,
    UART_STOP_BIT_1_5,
    UART_STOP_BIT_2,
} uart_stop_bit_t;

typedef struct
{
    uart_baudrate_t baudrate;
    uart_parity_bit_t parity;
    uart_stop_bit_t stop_bit;
} uart_config_t;

uart_ret_code_t uart_init(uint8_t instance,
                          uart_config_t const *uart_config,
                          uart_event_handler_t uart_event_handler);

uart_ret_code_t uart_write(uint8_t instance, uint8_t *p_data, uint16_t size);

#endif //ELECROLUX_UART_H

#include <stdint.h>
#include <stdio.h>
#include "uart.h"

static uart_event_handler_t evt_handler = NULL;

uart_ret_code_t uart_init(uint8_t instance,
              uart_config_t const *uart_config,
              uart_event_handler_t uart_event_handler)
{

}

uart_ret_code_t uart_write(uint8_t instance, uint8_t *p_data, uint16_t size)
{

}


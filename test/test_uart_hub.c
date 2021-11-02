#include "unity.h"
#include "uart_hub.h"
#include "mock_uart.h"

const char *test_message = "zxcvbnmasdfghqwezxcvbnmasdfghqwezxcvbnmasdfghqwezxcvbnmasdfghqwezxcvbnmasdfghqwezxcvbnmasdfghqwezxcvbnmasdfghqwezxcvbnmasdfghqwe";

void setUp(void)
{
}
void tearDown(void)
{
}
void test_uart_hub( void )
{
    uart_event_t evt;
    memset(&evt, 0, sizeof(uart_event_t));
    evt.type = UART_EVENT_TYPE_RX_BYTE_READY;

    uart_write_ExpectWithArrayAndReturn(1, test_message, sizeof(test_message), 128, 0);

    for (uint16_t i = 0; i < 128; i++)
    {
        evt.rx_byte = test_message[i];
        test_wrapper_uart1_handler(&evt);
    }
}

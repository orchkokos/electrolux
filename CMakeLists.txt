cmake_minimum_required(VERSION 3.20)
project(electrolux C)

set(CMAKE_C_STANDARD 99)

include_directories(src/uart src/uart_hub)

add_executable(electrolux src/main.c src/uart/uart.c src/uart_hub/uart_hub.c)
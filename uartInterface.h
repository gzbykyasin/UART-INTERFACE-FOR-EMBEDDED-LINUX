#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include <stdio.h>
#include <fcntl.h>   // File Control Definitions
#include <termios.h> // POSIX Terminal Control Definitions
#include <unistd.h>  // UNIX Standard Definitions
#include <errno.h>   // ERROR Number Definitions
#include <stdint.h>  // Integer Types

#define SERIAL_PORT_ERROR               1
#define SERIAL_PORT_OPEN                2
#define SERIAL_PORT_WRITE_SUCCESS       3
#define SERIAL_PORT_READ_SUCCESS        4
#define SERIAL_PORT_WRITE_ERROR         5
#define SERIAL_PORT_READ_ERROR          6


uint8_t UARTConfiguration();
uint8_t* UARTReceive(uint8_t *data,const uint16_t length);
uint8_t UARTTransmitter(uint8_t *data,const uint16_t length);

#endif
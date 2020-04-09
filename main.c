#include "stdio.h"
#include "uartInterface.h"

int filedesc;
extern int errno;
uint8_t sendData[16] = {
    0x00,0x01,0x02,0x03,
    0x04,0x05,0x06,0x07,
    0x08,0x09,0x0A,0x0B,
    0x0C,0x0D,0x0E,0x0F
};

int main(int argc,char **argv){
    // In "NAME", enter the name of the bus that goes into serial communication.
    if(filedesc= open("/dev/ttyNAME",O_RDWR | O_NOCTTY) < 0){
        printf("\nERROR! in Opening Serial Port",strerror(errno));
        close(filedesc);
        return 0;
    }
    //UART Configuration Settings
    if(UARTConfiguration() != SERIAL_PORT_ERROR){
        printf("\nSerial Port Open");
    }
    
    //UART Send Data. Total 16 bytes
    if(UARTTransmitter(sendData,16) != SERIAL_PORT_WRITE_ERROR);{
        printf("\nData Sent from Serial Port");
    }
    
    //Close UART 
    close(filedesc);
    //Finish the Program
    return 1;
}
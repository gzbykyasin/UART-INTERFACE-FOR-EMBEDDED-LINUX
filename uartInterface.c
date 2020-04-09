#include "uartInterface.h"

extern int filedesc;
extern int errno;
/**  @brief Serial Port Configuration   */
uint8_t UARTConfiguration() {
    // Create the structure
    struct termios SerialPortSettings;	
    // Get the current attributes of the Serial port
    tcgetattr(filedesc, &SerialPortSettings);
    // Setting the Baud rate
    // Set Read  Speed as B115200
    cfsetispeed(&SerialPortSettings,B115200); 
    // Set Write Speed as B115200
    cfsetospeed(&SerialPortSettings,B115200);
    // 8N1 Mode
    // Disables the Parity Enable bit(PARENB),So No Parity
    SerialPortSettings.c_cflag &= ~PARENB;   
    // CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit
    SerialPortSettings.c_cflag &= ~CSTOPB;   
    // Clears the mask for setting the data size
    SerialPortSettings.c_cflag &= ~CSIZE;	
    // Set the data bits = 8 
    SerialPortSettings.c_cflag |=  CS8;     
    // No Hardware flow Control
    SerialPortSettings.c_cflag &= ~CRTSCTS;       
    // Enable receiver,Ignore Modem Control lines
    SerialPortSettings.c_cflag |= CREAD | CLOCAL;
    // Disable XON/XOFF flow control both i/p and o/p
    SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          
    // Non Cannonical mode
    SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  
    // No Output Processing
    SerialPortSettings.c_oflag &= ~OPOST;
    // Setting Time outs
    // Read at least 10 characters
    SerialPortSettings.c_cc[VMIN] = 1; 
    // Wait indefinetly
    SerialPortSettings.c_cc[VTIME] = 0;
    // Set the attributes to the termios structure
    if((tcsetattr(filedesc,TCSANOW,&SerialPortSettings)) != 0){
        printf("\nERROR! in Setting attributes",strerror(errno));
        return SERIAL_PORT_ERROR;
    }
    else{
        printf("\nBaudRate= B115200\nStopBits=1\nParity=none\n");       
        return SERIAL_PORT_OPEN;
    }
}

/** @brief Serial Port Read
 *  @param length The number of bytes to be read from the serial port.
 *  @return Data read from the serial port 
 */
uint8_t* UARTReceive(uint8_t *data,const uint16_t length){
    // Discards old data in the rx buffer
    tcflush(filedesc, TCIFLUSH);
    int  bytes_read = 0;    
    bytes_read = read(filedesc,data,length);
    if(bytes_read < 1){
        printf("\nError receiving data:%s",strerror(errno));
        return SERIAL_PORT_READ_ERROR;
    }
    return data;
}

/** @brief Serial Port Write
 *  @param data Data to be sent from the serial port.
 *  @param length The number of bytes to be write from the serial port.
 *  @return Data send result from the serial port 
 */
uint8_t UARTTransmitter(uint8_t *data,const uint16_t length){        
    if(data < 1){
        printf("\nWrong Address");
        return SERIAL_PORT_WRITE_ERROR;
    }
    int bytes_write = 0;    
    bytes_write = write(filedesc,data,length);
    
    if(bytes_write < 1){
        printf("\nError sending data",strerror(errno));
        return SERIAL_PORT_WRITE_ERROR;
    }
     return SERIAL_PORT_WRITE_SUCCESS;
}
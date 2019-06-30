/* ************************************************************************** */
/** X2CComm.c

  @Company
    Microchip Technology

  @Summary
    Implements the X2C Lin protocol connection with MCC Peripheral drivers.

 */
/* ************************************************************************** */

#include "X2CComm.h"
#include "../uart1.h"

static void sendSerial (tSerial* serial, uint8 data);
static uint8 receiveSerial (tSerial* serial);
static uint8 isReceiveDataAvailable (tSerial* serial);
static uint8 isSendReady (tSerial* serial);

/**
 * @brief Link serial functions to X2C
 * 
 * @param[in] serial Serial interface object.
 */
void initX2CSerial (tSerial* serial)
{
  serial->send = (void (*)(tInterface*, uint8))sendSerial;
  serial->receive = (uint8 (*)(tInterface*))receiveSerial;
  serial->isReceiveDataAvailable = (uint8 (*)(tInterface*))isReceiveDataAvailable;
  serial->isSendReady = (uint8 (*)(tInterface*))isSendReady;
}

/** 
  @brief
    Puts the data to the hardware layer. (UART)
   @param[in] serial Serial interface object. (Not used)
   @param[in] data Data to send 
 */
static void sendSerial (tSerial* serial, uint8 data)
{

#if defined (__dsPIC33E__)
  U1TXREG = data;   
  
#elif defined (__dsPIC33C__)
  U1TXREG = data;   
  
#elif defined (__PIC32M__)
  U1TXREG = data; 
  
#else
  #error "Please check device family or implement own interface."
#endif

}

/** 
  @brief
   Get serial data from hardware. Reset the hardware in case of error. (UART2)
  @param[in] serial Serial interface object. (Not used)
  @return
    Return with the received data
 */
static uint8 receiveSerial (tSerial* serial)
{
#if defined (__dsPIC33E__)
    if (U1STA & 0x0E) {
        U1STAbits.OERR = 0; /* reset error */
        return (0);
    }
    return U1RXREG; 

#elif defined (__dsPIC33C__)
    if ((U1STAbits.OERR == 1))
    {
        U1STAbits.OERR = 0;
        return(0);
    }
    return U1RXREG;

#elif defined (__PIC32M__)
    if (U1STA & 0x0E) {
        U1STAbits.OERR = 0; /* reset error */
        return (0);
    }
    return U1RXREG;
    
#else
  #error "Please check device family or implement own interface."
#endif

}

/** 
  @brief  Check data availability (UART).
  @param[in] serial Serial interface object. (Not used)
  @return
    True -> Serial data ready to read.
    False -> No data.
 */
static uint8 isReceiveDataAvailable (tSerial* serial)
{
#if defined (__dsPIC33E__)
    return (U1STAbits.URXDA == 1);

#elif defined (__dsPIC33C__)
    return (U1STAHbits.URXBE == 0);
  
#elif defined (__PIC32M__)
    return (U1STAbits.URXDA == 1);
  
#else
  #error "Please check device family or implement own interface."
#endif


}

/** 
  @brief
   Check output buffer. (UART)
  @param[in] serial Serial interface object. (Not used)
  @return    
    True -> Transmit buffer is not full, at least one more character can be written.
    False -> Transmit buffer is full.
 */
static uint8 isSendReady (tSerial* serial)
{
#if defined (__dsPIC33E__)
    return (U1STAbits.UTXBF == 0); //TX Buffer full

#elif defined (__dsPIC33C__)
    return (U1STAHbits.UTXBF == 0);//TX Buffer full

#elif defined (__PIC32M__)
    return (U1STAbits.UTXBF == 0); //TX Buffer full
  
#else
  #error "Please check device family or implement own interface."
#endif

}
/* *****************************************************************************
 End of File
 */
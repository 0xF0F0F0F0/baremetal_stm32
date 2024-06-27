#include "serial.h"

/**
 * @brief
 * 
 * 1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
 * 2. Program the M bit in USART_CR1 to define the word length.
 * 3. Program the number of stop bits in USART_CR2.
 * 4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
 *    place. Configure the DMA register as explained in multibuffer communication.
 * 5. Select the desired baud rate using the USART_BRR register.
 * 6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
 * 7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
 *    for each data to be transmitted in case of single buffer.
 * 8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
 *    that the transmission of the last frame is complete. This is required for instance when
 *    the USART is disabled or enters the Halt mode to avoid corrupting the last
 *    transmission.
 * 9. Set the RE bit USART_CR1. This enables the receiver which begins searching for a
 *    start bit.
 * 10. When a character is received
 *     - The RXNE bit is set. It indicates that the content of the shift register is transferred to the
 *       RDR. In other words, data has been received and can be read (as well as its
 *       associated error flags).
 *     - An interrupt is generated if the RXNEIE bit is set.
 *     - The error flags can be set if a frame error, noise or an overrun error has been detected
 *       during reception.
 *     - In multibuffer, RXNE is set after every byte received and is cleared by the DMA read to
 *       the Data Register.
 *     - In single buffer mode, clearing the RXNE bit is performed by a software read to the
 *       USART_DR register. The RXNE flag can also be cleared by writing a zero to it. The
 *       RXNE bit must be cleared before the end of the reception of the next character to avoid
 *       an overrun error.*
*/

//USART1
//PA9 -> TX
//PA10 -> RX

err_t serial_init(uint8_t tx_pin, uint8_t rx_pin, baud_t baud_rate) {
    
    USART1->CR1 |= USART_CR1_UE;        // enable uart1
    USART1->CR1 &= ~(USART_CR1_M);      // word length = 8
    USART1->CR2 |= USART_CR2_STOP_1;    // stop bits = 2

    switch(baud_rate){

        case BAUD_9600: {
        } break;

        case BAUD_115200: {
        } break;

        default: {

        }
    }

    
    return EOK;
}
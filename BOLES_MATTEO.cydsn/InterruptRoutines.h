
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H

    #include "cytypes.h"
    #include "stdio.h"
    
    #define BYTE_TO_SEND 2
    #define TRANSMIT_BUFFER_SIZE 1+BYTE_TO_SEND+1

    CY_ISR_PROTO(Custom_ISR_ADC);
    CY_ISR_PROTO(received_datum);
    
    uint8 DataBufferPhotoresistor [TRANSMIT_BUFFER_SIZE];
    uint8 DataBufferPotentiometer [TRANSMIT_BUFFER_SIZE];
#endif
/* [] END OF FILE */

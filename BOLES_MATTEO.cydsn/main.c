
#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"

int main(void)
{
    CyGlobalIntEnable; // Enable global interrupts.
    // Start the components
    ADCDelSig_Start();
    UART_Start();
    PWM_Start();
    ISR_ADC_StartEx(Custom_ISR_ADC);
    ISR_Received_StartEx(received_datum);
    // Initialize send flag
    PacketReadyFlag = 0;   
    DataBufferPhotoresistor[0]=0xB0;
    DataBufferPhotoresistor[TRANSMIT_BUFFER_SIZE-1]=0xE0;
    DataBufferPotentiometer[0]=0xA0;
    DataBufferPotentiometer[TRANSMIT_BUFFER_SIZE-1]=0xC0;
    // Start the ADC conversion
    ADCDelSig_StartConvert();
    
    for(;;)
    {
        if (PacketReadyFlag == 1)
        {
            UART_PutArray(DataBufferPotentiometer, TRANSMIT_BUFFER_SIZE);
            UART_PutArray(DataBufferPhotoresistor, TRANSMIT_BUFFER_SIZE);
            PacketReadyFlag = 0;
        }
        
    }
}

// Include header
#include "InterruptRoutines.h"
// Include required header files
#include "project.h"
#include "math.h"
// Variables declaration 
#define THRESHOLD 30000

int32 value_digit_photo, value_digit_pot;
uint8 ch_received;
uint8 SendBytesFlag=0;

CY_ISR (Custom_ISR_ADC)
{
// Read Timer status register to bring interrupt line low
    Timer_ReadStatusRegister();
    if (SendBytesFlag)
    {
        AMux_FastSelect(0);
        value_digit_photo = ADCDelSig_Read32();       
        if (value_digit_photo < 0)      value_digit_photo = 0;
        if (value_digit_photo > 65535)  value_digit_photo = 65535;
        
        AMux_FastSelect(1);
        value_digit_pot = ADCDelSig_Read32();
        if (value_digit_pot < 0)        value_digit_pot = 0;
        if (value_digit_pot > 65535)    value_digit_pot = 65535; 
        
        if (value_digit_photo < THRESHOLD)
        {       
            PWM_WriteCompare(value_digit_pot);
        }
        else
        {
            PWM_WriteCompare(0);
        }
        
        DataBufferPhotoresistor[1] = value_digit_photo >> 8;
        DataBufferPhotoresistor[2] = value_digit_photo & 0xFF;
        DataBufferPotentiometer[1] = value_digit_pot >> 8;
        DataBufferPotentiometer[2] = value_digit_pot & 0xFF;  
        
        PacketReadyFlag = 1;
    }
}

CY_ISR (received_datum)
{
    ch_received = UART_GetChar();
    
    switch(ch_received)
    {
        case 'B':
        case 'b':
            SendBytesFlag=1;
            InternalLED_Write(1);
            Timer_Start();
            break;
        case 'S':
        case 's':
            SendBytesFlag=0;
            InternalLED_Write(0);
            PWM_WriteCompare(0);
            Timer_Stop();   
        default:
            break;
    }
}
/* [] END OF FILE */

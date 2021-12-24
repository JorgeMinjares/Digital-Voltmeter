/**
 * @file main.c
 * @author Jorge Minjares (https://github.com/JorgeMinjares)
 * @brief This program will emulates a Digital Voltmeter using ARM-microprocessor (MSP432).
 * @version 0.1
 * @date 2021-12-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "msp.h"
#include "lcdLib.h"
#include <stdlib.h>

#define DATA_SIZE 5              // Create Macro for rawData array size
#define VREF_POS 3.04            // VCC reference, measure output of 3.3V
#define VREF_NEG 0.0             // VSS reference
#define VOLTAGE_RESOLUTION 16384 // 14-bit resolution

uint8_t index = 0;           // global variable used in rawData array
uint16_t rawData[DATA_SIZE]; // Create array to store ADC Memory

// convertes adc digital value to analog or "voltage"
float volts(uint16_t adc)
{
    return (VREF_POS - VREF_NEG) * ((float)adc / (VOLTAGE_RESOLUTION - 1)); // return voltage from ADC
}
void displayVolts(uint16_t adc, float volt)
{
    lcdClear();                               // clear LCD screen
    lcdSetText("Voltmeter", 4, 0);            // Set text for LCD Screen
    char buffer[16];                          // Create character array named Buffer
    lcdSetText(buffer, 2, 1);                 // Display buffer text onto LCD Screen
    sprintf(buffer, "%u->%.2f V", adc, volt); // Update Buffer
    lcdSetText(buffer, 2, 1);                 // Display Buffer onto LCD Screen
}

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
    lcdInit();                                  // Initiate LCD Screen
    lcdClear();                                 // Clear LCD Screen

    lcdSetText("Voltmeter", 4, 0); // Display text onto LCD Screen

    P5->SEL0 |= BIT4; // Bit set SEL0 for P5.4 -- Enable special functions
    P5->SEL1 |= BIT4; // Bit set SEL1 for P5.4 -- Enable special functions
    // Enable ADC
    ADC14->CTL0 |= ADC14_CTL0_SHP | ADC14_CTL0_CONSEQ_0 | ADC14_CTL0_ON;
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_1;  // mem 0 channel A1 = P5.4
    ADC14->CTL1 |= ADC14_CTL1_RES__14BIT; // 14 bit resolution
    ADC14->IER0 |= ADC14_IER0_IE0;        // enable interrupts for mem 0
    // Enable Timer_A0
    // TASSEL_2 = SMClock        MC_1 = Up-mode
    TIMER_A0->CTL |= TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1;
    TIMER_A0->CCR[0] |= 60000 - 1;           // Select value to declare Frequency -- 3000000/(60000-1) = 50Hz
    TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE; // Enable Timer_A0 interrupts

    NVIC->ISER[0] |= 1 << ((ADC14_IRQn)&31); // Enable NVIC
    NVIC->ISER[0] |= 1 << ((TA0_0_IRQn)&31); // Enable NVIC
    __enable_irq();                          // Enable global interrupts

    while (1) // infinite-loop for embedded system
    {
    }
}
void TA0_0_IRQHandler(void)
{
    // runs every 20ms * 5 -> 100ms
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC; // start conversion and enable conversion
    TIMER_A0->CCTL[0] &= ~(TIMER_A_CCTLN_CCIFG);   // Clear Timer_A0 Interrupt Flag
}

void ADC14_IRQHandler(void)
{
    // Vread = Vref * (ADCread)/ (2^n - 1) - > 3.3 - 0.0 * (adcRaw)/ 16384
    rawData[index++] = ADC14->MEM[0]; // Store ADC reading onto rawData array

    if (index > DATA_SIZE)
    {
        uint32_t data = 0; // Initialize data variable
        int i;
        // for-loop stores all raw data onto data
        for (i = 0; i < DATA_SIZE; i++)
        {
            data += rawData[i];
        }
        data /= DATA_SIZE;               // store data divided by rawData size onto data
        displayVolts(data, volts(data)); // use function to display data and the voltage of the ADC
        index = data = 0;                // Clear both variables
    }
}

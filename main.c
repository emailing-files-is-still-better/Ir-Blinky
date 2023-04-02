#include "mcc_generated_files/mcc.h"

// ========== DEFINES ==========
#define DATA_LENGTH   8                 // Number of bits transmitted in a packet (not including preamble))
#define DEFAULT_DATA  0b11011101        // Default Data to transmit

#define LED_PIN     LATAbits.LATA3      // Write to this to force the pin high (1) or low (0)
#define PWM_EN      PWM3CONbits.EN      // Enables (1) or Disables (0) the PWM Output
 

// ========== GLOBAL VARIABLES ==========
const bool preamble[] = {1, 1, 1, 0, 1, 1, 0, 0, 0, 0,
                         1, 1, 1, 0, 1, 1, 0, 0, 0, 0};       // Preamble
bool data[DATA_LENGTH] = {0};                                 // Data of our packet                             
const bool delayBetweenTransmissions[61] = {0};               // Fill an array of zeros
bool* arrayStartPtr = NULL;                                   // Points to the beginning of an array
uint8_t bitIndex = 0;                                         // Keeps track of our bit position


// ========== FUNCTION PROTOTYPES ==========
void bitTimerInterrupt();
void transmitBits(bool* arrayStart, uint8_t size);
void setDataPattern(uint16_t newDataPattern);
void stepThroughDataPatterns(uint16_t repeatEachPatternNTimes);

// ========== MAIN ==========
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    PWM3_Initialize();
    TMR0_Initialize();
    
    TMR0_SetInterruptHandler(bitTimerInterrupt);

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    // Set the data pattern
    setDataPattern(DEFAULT_DATA);

    while (1)
    {
      transmitBits(&preamble[0], sizeof(preamble));
      transmitBits(&data[0], sizeof(data));
      transmitBits(&delayBetweenTransmissions[0], sizeof(delayBetweenTransmissions));
    }
    
    // Or
    
    // while(1) {
    //   stepThroughDataPatterns(10);       // Repeat each pattern 10 times
    // }
}


// ========== LOCAL FUNCTIONS ==========
void bitTimerInterrupt() {
    PWM_EN = arrayStartPtr[bitIndex++];   // Enable or Disable PWM based on current bit, then increment index
}


void transmitBits(bool* arrayStart, uint8_t size) {
  bitIndex = 0;               // Re-initialize bit index
  arrayStartPtr = arrayStart; // Point to the start of the array we want to transmit
  while(bitIndex < size);     // Wait here until the bit index reaches the end of the array
}

/* Loads data[] with bools to correspond to an input
 *   For instance: setDataPattern(0b11011101) or setDataPattern(0xDD) or setDataPattern(221)
 *   Will result in data[] being set to {1, 1, 0, 1, 1, 1, 0, 1}
 */
void setDataPattern(uint16_t newDataPattern) {
    for(uint8_t i=0; i<DATA_LENGTH; i++) {
        // To set the left most array element (element 0), you need to address
        // the left most bit (bit 7 in an 8 bit number). Bit 0 is the right most bit.
        data[i] = ((newDataPattern & 1<<((DATA_LENGTH-1)-i)) != 0);
    }
}

void stepThroughDataPatterns(uint16_t repeatEachPatternNTimes) {
    uint16_t firstPattern = 0;
    uint16_t lastPattern = (1<<DATA_LENGTH)-1;  // 0b11111111 for an 8-bit pattern
    for(uint16_t currPattern = firstPattern; currPattern <= lastPattern; currPattern++) {
        for(uint16_t repeatNum = 0; repeatNum < repeatEachPatternNTimes; repeatNum++) {
            setDataPattern(currPattern);
            transmitBits(&preamble[0], sizeof(preamble));
            transmitBits(&data[0], sizeof(data));
            transmitBits(&delayBetweenTransmissions[0], sizeof(delayBetweenTransmissions));
        }
    }
}

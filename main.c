#include "mcc_generated_files/mcc.h"
#include "addresses.h"

// ========== DEFINES ==========
#define DEFAULT_DATA                    ADDRESS_10  // Default address to transmit
#define TRANSMISSION_INTERVAL           30000       // Time between transmissions (in us)

#define LED_PIN     LATAbits.LATA4      // Write to this to force the pin high (1) or low (0)
#define PWM_EN      PWM3CONbits.EN      // Enables (1) or Disables (0) the PWM Output

#define BITS_TO_DELAY   ((TRANSMISSION_INTERVAL/135) - DATA_LENGTH)


// ========== GLOBAL VARIABLES ==========
bool data1[DATA_LENGTH] = {0};        // Data of our packet including delay (slot 1)
bool data2[DATA_LENGTH] = {0};        // Data of our packet including delay (slot 2)
bool* currArrayStartPtr = &data1[0];  // Points to the beginning of an array
bool* nextArrayStartPtr = &data2[0];  // Points to the beginning of the next array to transmit
uint8_t dataBitIndex = 0;             // Keeps track of data bits
uint32_t delayBitIndex = 0;           // Keeps track of delay bits


// ========== FUNCTION PROTOTYPES ==========
void bitTimerInterrupt(void);
void stepThroughDataPatterns(uint32_t firstPattern, uint32_t finalPattern, uint16_t repeatEachPatternNTimes);
void repeatTransmission(uint16_t numOfTimes);
void beginTransmission(void);
void waitForTransmissionFinish(void);
void setDataPattern(uint32_t newDataPattern, uint8_t bitSize, bool* startPtr);
void switchArrays(void);

// ========== MAIN ==========
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    PWM3_Initialize();
    TMR0_Initialize();
    
    TMR0_SetInterruptHandler(bitTimerInterrupt);
    PWM_EN = false;                                 // Begin with LED off
    TMR0_StopTimer();                               // Begin with bit timer stopped

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    // Set the data pattern
    setDataPattern(DEFAULT_DATA, DATA_LENGTH, currArrayStartPtr);
    
    // Send a known good address once
    beginTransmission();
    repeatTransmission(9);
    waitForTransmissionFinish();

    while(1) {
        stepThroughDataPatterns(103535, ((1UL<<DATA_LENGTH) - 1), 9);
     }
}


// ========== LOCAL FUNCTIONS ==========
/* Every time the bit timer ticks, set PWM_EN to the value of the current bit, then
 * move on to the next bit. Once you run out of data bits, start incrementing the
 * delay index.
*/
void bitTimerInterrupt(void) {
    if(dataBitIndex < DATA_LENGTH) {
        PWM_EN = currArrayStartPtr[dataBitIndex++];   // Enable or Disable PWM based on current bit, then increment index
    } else {
        PWM_EN = false;                               // Ensure you're not outputing anything
        delayBitIndex++;                              // Delay another bit
    }
}


/* It loads an array space starting at currArrayStartPtr with the first pattern,
 * then it transmits that pattern a certain number of times. During the final 
 * transmission, it calculates the next value and loads a second array with the
 * right bits. After the last transmission finishes, it swaps in the next array
 * for the current one, then repeats this process until it reaches its final pattern.
*/
void stepThroughDataPatterns(uint32_t firstPattern, uint32_t finalPattern, uint16_t repeatEachPatternNTimes) {
    setDataPattern(firstPattern, DATA_LENGTH, currArrayStartPtr);
    uint32_t nextPattern = firstPattern;                // Next Pattern to transmit. Initialized to firstPattern, will be incremented before used
    do {
        beginTransmission();
        repeatTransmission(repeatEachPatternNTimes - 1);
        // Final transmission is still underway at this point
        nextPattern++;
        setDataPattern(nextPattern, 20, &nextArrayStartPtr[10]);
        for(int i=0; i<10; i++) {
            nextArrayStartPtr[i] = nextArrayStartPtr[i+10];
            }
        waitForTransmissionFinish();
        switchArrays();
    } while(nextPattern <= finalPattern);
}


/* Waits for the current transmission/delay cycle to finish, then starts a new one,
 * repeats numOfTimes.
*/
void repeatTransmission(uint16_t numOfTimes) {
    for(uint16_t timesLeft=numOfTimes; timesLeft>0; timesLeft--) {
        waitForTransmissionFinish();
        beginTransmission();
    }
}


/* Starts the bit timer and initializes the indicies. This kicks off a
 * transmission/delay cycle, but does not stick around for it to end.
*/
void beginTransmission(void) {
  dataBitIndex = 0;           // Re-initialize data bit index
  delayBitIndex = 0;          // Re-initialize delay bit index
  TMR0_StartTimer();          // Start bit timer
}


/* This function waits for a current transmission/delay cycle to finish.
 * Since delayBitIndex gets incremented after dataBitIndex, we just have
 * to watch for the delay to finish. Then stop the timer to avoid junk
 * bits from possibly being transmitted.
*/
void waitForTransmissionFinish(void) {
  while(delayBitIndex < BITS_TO_DELAY);        // Wait here until the delay bit index reaches the desired bits to delay
  TMR0_StopTimer();                            // Stop bit timer
}


/* Loads data[] with bools to correspond to an input
 *   For instance: setDataPattern(0b11011101) or setDataPattern(0xDD) or setDataPattern(221)
 *   Will result in data[] being set to {1, 1, 0, 1, 1, 1, 0, 1}
 */
void setDataPattern(uint32_t newDataPattern, uint8_t bitSize, bool* startPtr) {
    for(uint8_t i=0; i<bitSize; i++) {
        // To set the left most array element (element 0), you need to address
        // the left most bit (bit 7 in an 8 bit number). Bit 0 is the right most bit.
        startPtr[i] = ((newDataPattern & 1UL<<((bitSize-1)-i)) != 0);
    }
}

/* Swaps currArrayStartPtr and nextArrayStartPtr.
*/
void switchArrays(void) {
    bool* lastArrayStartPtr = currArrayStartPtr;
    currArrayStartPtr = nextArrayStartPtr;
    nextArrayStartPtr = lastArrayStartPtr;
}

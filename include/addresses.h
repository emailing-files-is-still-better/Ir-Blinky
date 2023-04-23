#define DATA_LENGTH   30                 // Number of bits transmitted in a packet

#if DATA_LENGTH > 32
    #error "Data length has to be 32 bits or less"
#endif

#define ADDRESS_10  0b000000000000000000000100100111 //295
#define ADDRESS_36  0b010011010101001101010011010110 //316630
#define ADDRESS_60

//#define ADDRESS_65  0b01101110100110111010001101101 //226413 Not Consistent
#define ADDRESS_65  0b01101110100110111010001101001 //226409 Much Better   

#define ADDRESS_70  0b101110010010111001001011010000 //190030
#define ADDRESS_73  0b101010010010101001000100111000 //173130
#define ADDRESS_75  
#define ADDRESS_75  0b110100010011010001101001100000 //214670
#define ADDRESS_76  0b111011100011101110001011010010 //Bought Transponder
#define ADDRESS_77  0b011001110001100111000010010100 //105509
                    
#define ADDRESS_80  0b110101100011010110000101101100 //219225
//#define ADDRESS_80  0b1101011000110101100001111011 //219259 pings but not on as accurate of time

#define ADDRESS_86  0b110010100011001010001101011000 //103530
#define ADDRESS_89  0b110100100011010010000111101000 //215160
#define ADDRESS_90  0b011101000001110100000000101100
#define ADDRESS_92  0b111011000011101100001101110100 //Bought Transponder




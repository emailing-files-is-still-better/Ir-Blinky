#define DATA_LENGTH   30                 // Number of bits transmitted in a packet

#if DATA_LENGTH > 32
    #error "Data length has to be 32 bits or less"
#endif

#define ADDRESS_10  0b000000000000000000000100100111 //295 - Brute Force - Free to use
#define ADDRESS_36  0b010011010101001101010011010110 //316630 - Brute Force - Free to use

#define ADDRESS_49  0b11011000101101100010111100110 //Bought Transponder - In Use
#define ADDRESS_50  0b11001000101100100010110110110 //Bought Transponder - Free to Use
#define ADDRESS_51  0b11110111001111011100100100010 //Bought Transponder - Free to Use
#define ADDRESS_52  0b10110111001011011100100101011 //Bought Transponder - Free to Use
#define ADDRESS_53  0b11010111001101011100101100011 //Bought Transponder - Free to Use
#define ADDRESS_54  0b10010111001001011100101101010 //Bought Transponder - Free to Use
#define ADDRESS_55  0b11100111001110011100101110010 //Bought Transponder - Free to Use
#define ADDRESS_56  0b11000111001100011100100110011 //Bought Transponder - Free to Use
#define ADDRESS_57  0b10111011001011101100110111011 //Bought Transponder - Free to Use
#define ADDRESS_58  0b11101011001110101100111100010 //Bought Transponder - Free to Use

#define ADDRESS_64  0b10010011001001001100111101110  //Bought Transponder - In Use
//#define ADDRESS_65  0b01101110100110111010001101001 //226409 Brute Force - For Comparison Only  
#define ADDRESS_65  0b11011101001101110100110100100 //Bought Transponder - In Use
#define ADDRESS_66  0b10011101001001110100110101101 //Bought Transponder - In Use
#define ADDRESS_67  0b11101101001110110100110110101 //Bought Transponder - In Use
#define ADDRESS_68  0b10010101001001010100110111001 //Bought Transponder - In Use
#define ADDRESS_69  0b10100101001010010100110101000 //Bought Transponder - In Use
#define ADDRESS_70  0b10111001001011100100101101000 //Bought Transponder - In Use
//#define ADDRESS_70  0b10111001001011100100101101000 //190030 Brute Force - For Comparison Only
#define ADDRESS_71  0b10011001001001100100100101001 //Bought Transponder - In Use
#define ADDRESS_72  0b11101001001110100100100110001 //Bought Transponder - In Use
#define ADDRESS_73  0b10101001001010100100100111000 //Bought Transponder - In Use
//#define ADDRESS_73  0b101010010010101001000100111000 //173130 Brute Force - For Comparison Only

#define ADDRESS_75  0b110100010011010001101001100000 //214670 - Brute Force - Free to use
#define ADDRESS_76  0b111011100011101110001011010010 //Bought Transponder - In Use
#define ADDRESS_77  0b011001110001100111000010010100 //105509 - Brute Force - Free to use
                    
#define ADDRESS_80  0b110101100011010110000101101100 //219225 - Brute Force - Free to use
//#define ADDRESS_80  0b1101011000110101100001111011 //219259 pings but not on as accurate - Brute Force For Comparison Only 
#define ADDRESS_86  0b110010100011001010001101011000 //103530 - Brute Force - Free to use
#define ADDRESS_89  0b110100100011010010000111101000 //215160 - Brute Force - Free to use
#define ADDRESS_92  0b111011000011101100001101110100 //Bought Transponder - In Use




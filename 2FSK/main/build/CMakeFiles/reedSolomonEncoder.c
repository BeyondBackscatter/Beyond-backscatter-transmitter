#include <stdint.h>
#include <stdio.h>
// This are tables generated using python.
uint8_t exp_table[]={0b1 ,0b10 ,0b100 ,0b1000 ,0b10000 ,0b100000 ,0b1000000 ,0b10000000 ,0b11101 ,0b111010 ,0b1110100 ,0b11101000 ,0b11001101 ,0b10000111 ,0b10011 ,0b100110 ,0b1001100 ,0b10011000 ,0b101101 ,0b1011010 ,0b10110100 ,0b1110101 ,0b11101010 ,0b11001001 ,0b10001111 ,0b11 ,0b110 ,0b1100 ,0b11000 ,0b110000 ,0b1100000 ,0b11000000 ,0b10011101 ,0b100111 ,0b1001110 ,0b10011100 ,0b100101 ,0b1001010 ,0b10010100 ,0b110101 ,0b1101010 ,0b11010100 ,0b10110101 ,0b1110111 ,0b11101110 ,0b11000001 ,0b10011111 ,0b100011 ,0b1000110 ,0b10001100 ,0b101 ,0b1010 ,0b10100 ,0b101000 ,0b1010000 ,0b10100000 ,0b1011101 ,0b10111010 ,0b1101001 ,0b11010010 ,0b10111001 ,0b1101111 ,0b11011110 ,0b10100001 ,0b1011111 ,0b10111110 ,0b1100001 ,0b11000010 ,0b10011001 ,0b101111 ,0b1011110 ,0b10111100 ,0b1100101 ,0b11001010 ,0b10001001 ,0b1111 ,0b11110 ,0b111100 ,0b1111000 ,0b11110000 ,0b11111101 ,0b11100111 ,0b11010011 ,0b10111011 ,0b1101011 ,0b11010110 ,0b10110001 ,0b1111111 ,0b11111110 ,0b11100001 ,0b11011111 ,0b10100011 ,0b1011011 ,0b10110110 ,0b1110001 ,0b11100010 ,0b11011001 ,0b10101111 ,0b1000011 ,0b10000110 ,0b10001 ,0b100010 ,0b1000100 ,0b10001000 ,0b1101 ,0b11010 ,0b110100 ,0b1101000 ,0b11010000 ,0b10111101 ,0b1100111 ,0b11001110 ,0b10000001 ,0b11111 ,0b111110 ,0b1111100 ,0b11111000 ,0b11101101 ,0b11000111 ,0b10010011 ,0b111011 ,0b1110110 ,0b11101100 ,0b11000101 ,0b10010111 ,0b110011 ,0b1100110 ,0b11001100 ,0b10000101 ,0b10111 ,0b101110 ,0b1011100 ,0b10111000 ,0b1101101 ,0b11011010 ,0b10101001 ,0b1001111 ,0b10011110 ,0b100001 ,0b1000010 ,0b10000100 ,0b10101 ,0b101010 ,0b1010100 ,0b10101000 ,0b1001101 ,0b10011010 ,0b101001 ,0b1010010 ,0b10100100 ,0b1010101 ,0b10101010 ,0b1001001 ,0b10010010 ,0b111001 ,0b1110010 ,0b11100100 ,0b11010101 ,0b10110111 ,0b1110011 ,0b11100110 ,0b11010001 ,0b10111111 ,0b1100011 ,0b11000110 ,0b10010001 ,0b111111 ,0b1111110 ,0b11111100 ,0b11100101 ,0b11010111 ,0b10110011 ,0b1111011 ,0b11110110 ,0b11110001 ,0b11111111 ,0b11100011 ,0b11011011 ,0b10101011 ,0b1001011 ,0b10010110 ,0b110001 ,0b1100010 ,0b11000100 ,0b10010101 ,0b110111 ,0b1101110 ,0b11011100 ,0b10100101 ,0b1010111 ,0b10101110 ,0b1000001 ,0b10000010 ,0b11001 ,0b110010 ,0b1100100 ,0b11001000 ,0b10001101 ,0b111 ,0b1110 ,0b11100 ,0b111000 ,0b1110000 ,0b11100000 ,0b11011101 ,0b10100111 ,0b1010011 ,0b10100110 ,0b1010001 ,0b10100010 ,0b1011001 ,0b10110010 ,0b1111001 ,0b11110010 ,0b11111001 ,0b11101111 ,0b11000011 ,0b10011011 ,0b101011 ,0b1010110 ,0b10101100 ,0b1000101 ,0b10001010 ,0b1001 ,0b10010 ,0b100100 ,0b1001000 ,0b10010000 ,0b111101 ,0b1111010 ,0b11110100 ,0b11110101 ,0b11110111 ,0b11110011 ,0b11111011 ,0b11101011 ,0b11001011 ,0b10001011 ,0b1011 ,0b10110 ,0b101100 ,0b1011000 ,0b10110000 ,0b1111101 ,0b11111010 ,0b11101001 ,0b11001111 ,0b10000011 ,0b11011 ,0b110110 ,0b1101100 ,0b11011000 ,0b10101101 ,0b1000111 ,0b10001110 ,0b1 ,0b10 ,0b100 ,0b1000 ,0b10000 ,0b100000 ,0b1000000 ,0b10000000 ,0b11101 ,0b111010 ,0b1110100 ,0b11101000 ,0b11001101 ,0b10000111 ,0b10011 ,0b100110 ,0b1001100 ,0b10011000 ,0b101101 ,0b1011010 ,0b10110100 ,0b1110101 ,0b11101010 ,0b11001001 ,0b10001111 ,0b11 ,0b110 ,0b1100 ,0b11000 ,0b110000 ,0b1100000 ,0b11000000 ,0b10011101 ,0b100111 ,0b1001110 ,0b10011100 ,0b100101 ,0b1001010 ,0b10010100 ,0b110101 ,0b1101010 ,0b11010100 ,0b10110101 ,0b1110111 ,0b11101110 ,0b11000001 ,0b10011111 ,0b100011 ,0b1000110 ,0b10001100 ,0b101 ,0b1010 ,0b10100 ,0b101000 ,0b1010000 ,0b10100000 ,0b1011101 ,0b10111010 ,0b1101001 ,0b11010010 ,0b10111001 ,0b1101111 ,0b11011110 ,0b10100001 ,0b1011111 ,0b10111110 ,0b1100001 ,0b11000010 ,0b10011001 ,0b101111 ,0b1011110 ,0b10111100 ,0b1100101 ,0b11001010 ,0b10001001 ,0b1111 ,0b11110 ,0b111100 ,0b1111000 ,0b11110000 ,0b11111101 ,0b11100111 ,0b11010011 ,0b10111011 ,0b1101011 ,0b11010110 ,0b10110001 ,0b1111111 ,0b11111110 ,0b11100001 ,0b11011111 ,0b10100011 ,0b1011011 ,0b10110110 ,0b1110001 ,0b11100010 ,0b11011001 ,0b10101111 ,0b1000011 ,0b10000110 ,0b10001 ,0b100010 ,0b1000100 ,0b10001000 ,0b1101 ,0b11010 ,0b110100 ,0b1101000 ,0b11010000 ,0b10111101 ,0b1100111 ,0b11001110 ,0b10000001 ,0b11111 ,0b111110 ,0b1111100 ,0b11111000 ,0b11101101 ,0b11000111 ,0b10010011 ,0b111011 ,0b1110110 ,0b11101100 ,0b11000101 ,0b10010111 ,0b110011 ,0b1100110 ,0b11001100 ,0b10000101 ,0b10111 ,0b101110 ,0b1011100 ,0b10111000 ,0b1101101 ,0b11011010 ,0b10101001 ,0b1001111 ,0b10011110 ,0b100001 ,0b1000010 ,0b10000100 ,0b10101 ,0b101010 ,0b1010100 ,0b10101000 ,0b1001101 ,0b10011010 ,0b101001 ,0b1010010 ,0b10100100 ,0b1010101 ,0b10101010 ,0b1001001 ,0b10010010 ,0b111001 ,0b1110010 ,0b11100100 ,0b11010101 ,0b10110111 ,0b1110011 ,0b11100110 ,0b11010001 ,0b10111111 ,0b1100011 ,0b11000110 ,0b10010001 ,0b111111 ,0b1111110 ,0b11111100 ,0b11100101 ,0b11010111 ,0b10110011 ,0b1111011 ,0b11110110 ,0b11110001 ,0b11111111 ,0b11100011 ,0b11011011 ,0b10101011 ,0b1001011 ,0b10010110 ,0b110001 ,0b1100010 ,0b11000100 ,0b10010101 ,0b110111 ,0b1101110 ,0b11011100 ,0b10100101 ,0b1010111 ,0b10101110 ,0b1000001 ,0b10000010 ,0b11001 ,0b110010 ,0b1100100 ,0b11001000 ,0b10001101 ,0b111 ,0b1110 ,0b11100 ,0b111000 ,0b1110000 ,0b11100000 ,0b11011101 ,0b10100111 ,0b1010011 ,0b10100110 ,0b1010001 ,0b10100010 ,0b1011001 ,0b10110010 ,0b1111001 ,0b11110010 ,0b11111001 ,0b11101111 ,0b11000011 ,0b10011011 ,0b101011 ,0b1010110 ,0b10101100 ,0b1000101 ,0b10001010 ,0b1001 ,0b10010 ,0b100100 ,0b1001000 ,0b10010000 ,0b111101 ,0b1111010 ,0b11110100 ,0b11110101 ,0b11110111 ,0b11110011 ,0b11111011 ,0b11101011 ,0b11001011 ,0b10001011 ,0b1011 ,0b10110 ,0b101100 ,0b1011000 ,0b10110000 ,0b1111101 ,0b11111010 ,0b11101001 ,0b11001111 ,0b10000011 ,0b11011 ,0b110110 ,0b1101100 ,0b11011000 ,0b10101101 ,0b1000111 ,0b10001110 ,0b1 ,0b10};
uint8_t log_table[]={0b0 ,0b0 ,0b1 ,0b11001 ,0b10 ,0b110010 ,0b11010 ,0b11000110 ,0b11 ,0b11011111 ,0b110011 ,0b11101110 ,0b11011 ,0b1101000 ,0b11000111 ,0b1001011 ,0b100 ,0b1100100 ,0b11100000 ,0b1110 ,0b110100 ,0b10001101 ,0b11101111 ,0b10000001 ,0b11100 ,0b11000001 ,0b1101001 ,0b11111000 ,0b11001000 ,0b1000 ,0b1001100 ,0b1110001 ,0b101 ,0b10001010 ,0b1100101 ,0b101111 ,0b11100001 ,0b100100 ,0b1111 ,0b100001 ,0b110101 ,0b10010011 ,0b10001110 ,0b11011010 ,0b11110000 ,0b10010 ,0b10000010 ,0b1000101 ,0b11101 ,0b10110101 ,0b11000010 ,0b1111101 ,0b1101010 ,0b100111 ,0b11111001 ,0b10111001 ,0b11001001 ,0b10011010 ,0b1001 ,0b1111000 ,0b1001101 ,0b11100100 ,0b1110010 ,0b10100110 ,0b110 ,0b10111111 ,0b10001011 ,0b1100010 ,0b1100110 ,0b11011101 ,0b110000 ,0b11111101 ,0b11100010 ,0b10011000 ,0b100101 ,0b10110011 ,0b10000 ,0b10010001 ,0b100010 ,0b10001000 ,0b110110 ,0b11010000 ,0b10010100 ,0b11001110 ,0b10001111 ,0b10010110 ,0b11011011 ,0b10111101 ,0b11110001 ,0b11010010 ,0b10011 ,0b1011100 ,0b10000011 ,0b111000 ,0b1000110 ,0b1000000 ,0b11110 ,0b1000010 ,0b10110110 ,0b10100011 ,0b11000011 ,0b1001000 ,0b1111110 ,0b1101110 ,0b1101011 ,0b111010 ,0b101000 ,0b1010100 ,0b11111010 ,0b10000101 ,0b10111010 ,0b111101 ,0b11001010 ,0b1011110 ,0b10011011 ,0b10011111 ,0b1010 ,0b10101 ,0b1111001 ,0b101011 ,0b1001110 ,0b11010100 ,0b11100101 ,0b10101100 ,0b1110011 ,0b11110011 ,0b10100111 ,0b1010111 ,0b111 ,0b1110000 ,0b11000000 ,0b11110111 ,0b10001100 ,0b10000000 ,0b1100011 ,0b1101 ,0b1100111 ,0b1001010 ,0b11011110 ,0b11101101 ,0b110001 ,0b11000101 ,0b11111110 ,0b11000 ,0b11100011 ,0b10100101 ,0b10011001 ,0b1110111 ,0b100110 ,0b10111000 ,0b10110100 ,0b1111100 ,0b10001 ,0b1000100 ,0b10010010 ,0b11011001 ,0b100011 ,0b100000 ,0b10001001 ,0b101110 ,0b110111 ,0b111111 ,0b11010001 ,0b1011011 ,0b10010101 ,0b10111100 ,0b11001111 ,0b11001101 ,0b10010000 ,0b10000111 ,0b10010111 ,0b10110010 ,0b11011100 ,0b11111100 ,0b10111110 ,0b1100001 ,0b11110010 ,0b1010110 ,0b11010011 ,0b10101011 ,0b10100 ,0b101010 ,0b1011101 ,0b10011110 ,0b10000100 ,0b111100 ,0b111001 ,0b1010011 ,0b1000111 ,0b1101101 ,0b1000001 ,0b10100010 ,0b11111 ,0b101101 ,0b1000011 ,0b11011000 ,0b10110111 ,0b1111011 ,0b10100100 ,0b1110110 ,0b11000100 ,0b10111 ,0b1001001 ,0b11101100 ,0b1111111 ,0b1100 ,0b1101111 ,0b11110110 ,0b1101100 ,0b10100001 ,0b111011 ,0b1010010 ,0b101001 ,0b10011101 ,0b1010101 ,0b10101010 ,0b11111011 ,0b1100000 ,0b10000110 ,0b10110001 ,0b10111011 ,0b11001100 ,0b111110 ,0b1011010 ,0b11001011 ,0b1011001 ,0b1011111 ,0b10110000 ,0b10011100 ,0b10101001 ,0b10100000 ,0b1010001 ,0b1011 ,0b11110101 ,0b10110 ,0b11101011 ,0b1111010 ,0b1110101 ,0b101100 ,0b11010111 ,0b1001111 ,0b10101110 ,0b11010101 ,0b11101001 ,0b11100110 ,0b11100111 ,0b10101101 ,0b11101000 ,0b1110100 ,0b11010110 ,0b11110100 ,0b11101010 ,0b10101000 ,0b1010000 ,0b1011000 ,0b10101111};

uint8_t multiplicationGaliosField(uint8_t input1,uint8_t input2)
{
    if (input1==0||input2==0)
        return 0;
    else 
        return exp_table[log_table[input1]+log_table[input2]];
}
uint8_t xor1(uint8_t input1, uint8_t input2)
{
    uint8_t output=0x00;
    for (int i=0;i<8;i++)
        output=output|(((input1&(((uint8_t)1)<<i))!=(input2&(((uint8_t)1)<<i)))<<i);
    return output;
}
void encodeReedSolomon(uint8_t* input,uint8_t* messageOut)// This accepts 10 bytes and returns 20 bytes
{
    uint8_t polynomial[]={1, 14, 54, 114, 70, 174, 151, 43, 158, 195, 127, 166, 210, 234, 163};
    for (int i=0;i<14;i++)
        messageOut[i]=input[i];
    for (int i=14;i<28;i++)
        messageOut[i]=0;
    for (int i=0;i<14;i++)
    {
        uint8_t coefficent=messageOut[i];
        if(coefficent!=0)
            for (int j=1;j<15;j++)
                messageOut[i+j]=xor1(messageOut[i+j],multiplicationGaliosField(coefficent,polynomial[j]));
    }
    for (int i=0;i<14;i++)
        messageOut[i]=input[i];
}
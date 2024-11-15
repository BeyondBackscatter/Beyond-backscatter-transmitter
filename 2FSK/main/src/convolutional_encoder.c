#include <stdbool.h>
#include<stdint.h>
#include <stdio.h>
bool convolutional_registers[]={0,0,0,0,0,0,0};
uint16_t pseudo_random_register= 0xace1;
bool choose_bits_and_xor(bool bit0_or_bit1)
{
    if (!bit0_or_bit1) // for bit0
        return (((convolutional_registers[0] != convolutional_registers[1]) != (convolutional_registers[2] != convolutional_registers[3]))) != (convolutional_registers[6]);

    else // for bit(1)
        return ((((convolutional_registers[0])!=(convolutional_registers[2]))!=((convolutional_registers[3])!=(convolutional_registers[5])))!=(convolutional_registers[6]));
}
uint16_t encode (uint8_t input)
{ uint16_t output=0;
    uint8_t mask_to_select_bit=0b10000000;
    for (int index=0;index<7;index++)
    {   
        if (choose_bits_and_xor(1))
            output|=0x00000001;
        if (choose_bits_and_xor(0))
            output|=0x00000002;

        for (int i=0;i<6;i++)
        {
            convolutional_registers[i]=convolutional_registers[i+1];
        }
        output=output<<2;
        convolutional_registers[6]=(bool)((input&mask_to_select_bit)>>(7-index));
        mask_to_select_bit=mask_to_select_bit>>1;

    }
    if (choose_bits_and_xor(1))
        output|=0x00000001;
    if (choose_bits_and_xor(0))
        output|=0x00000002;
    for (int i=0;i<6;i++)
    {
            convolutional_registers[i]=convolutional_registers[i+1];
    }
    convolutional_registers[6]=(bool)((input&mask_to_select_bit)>>(0));
    // printf("%8x\n",output);
    return output;

}
uint64_t spread_by_4(uint16_t input)
    {
        uint64_t output =0;
        uint16_t mask=0x8000;
        for (int i=0;i<16;i++)
        {
            bool bit=(mask&input)>>15;
            if (bit)
                output|=0x0000000c;
            else
                output|=0x00000003;
            input=input<<1;
            if (i<15)
                output=output<<4;
        }
        return output;
    }
uint32_t encode_and_spread (uint8_t input)
{   uint32_t output=0;
    uint8_t mask_to_select_bit=0b10000000;

    for (int index=0;index<8;index++)
    {   
        for (int i=0;i<6;i++)
            convolutional_registers[i]=convolutional_registers[i+1];
        convolutional_registers[6]=(bool)((input&mask_to_select_bit)>>(7-index));
        mask_to_select_bit=mask_to_select_bit>>1;
        if (choose_bits_and_xor(1))
            output|=0x00000003;
        if (choose_bits_and_xor(0))
            output|=0x0000000c;
        if (index<7) 
            output=output<<4;
}
    // printf("%8x\n",output);
    return output;
}
uint16_t whitening_register=0b0000000111111111;
bool first_time=1;
uint8_t generate_whitening_bits()
{   uint16_t mask0=0x0001;
    uint16_t mask1=0x0020;
    if(first_time==1)
    {
        first_time=0;
        return (uint8_t)(whitening_register&0x00ff);
    }
    for(int i=0;i<8;i++)
    {
        uint16_t new_bit=(((bool)(whitening_register&mask0))!=((bool)((whitening_register&mask1)>>5)))<<8;
        whitening_register=((whitening_register>>1)&0x00ff)|new_bit;
    }
    
    return (uint8_t)(whitening_register&0x00ff);
}
uint8_t xor(uint8_t input1, uint8_t input2)
{
    uint8_t output=0x00;
    for (int i=0;i<8;i++)
        output=output|(((input1&(((uint8_t)1)<<i))!=(input2&(((uint8_t)1)<<i)))<<i);
    return output;
}
uint8_t whiten(uint8_t input)
{
    return xor(generate_whitening_bits(),input);
}
void reset()
{
    whitening_register=0b0000000111111111;
    first_time=1;
}

// uint64_t encode_and_spread_twice (uint8_t input)
// {   uint64_t output=0;
//     uint8_t mask_to_select_bit=0b10000000;
//     for (int index=0;index<7;index++)
//     {   
//         if (choose_bits_and_xor(1))
//             output|=0x0000000c;
//         else
//             output|=0x00000003;
//         if(choose_bits_and_xor(0))
//             output|=0x000000c0;
//         else
//             output|=0x00000030;
//         // *(bool*)(output+31)=choose_bits_and_xor(0);
//         // *(bool*)(output+30)=choose_bits_and_xor(0);
//         // *(bool*)(output+29)=choose_bits_and_xor(1);
//         // *(bool*)(output+28)=choose_bits_and_xor(1);
//         for (int i=0;i<6;i++)
//         {
//             convolutional_registers[i]=convolutional_registers[i+1];
//         }
//         output=output<<8;
//         convolutional_registers[6]=(bool)((input&mask_to_select_bit)>>(7-index));
//         mask_to_select_bit=mask_to_select_bit>>1;

//     }
//         if (choose_bits_and_xor(1))
//             output|=0x0000000c;
//         else
//             output|=0x00000003;
//         if(choose_bits_and_xor(0))
//             output|=0x000000c0;
//         else
//             output|=0x00000030;
//     for (int i=0;i<6;i++)
//     {
//             convolutional_registers[i]=convolutional_registers[i+1];
//     }
//     convolutional_registers[6]=(bool)((input&mask_to_select_bit)>>(0));
    
//     // *(bool*)(output+31)=choose_bits_and_xor(0);
//     // *(bool*)(output+30)=choose_bits_and_xor(0);
//     // *(bool*)(output+29)=choose_bits_and_xor(1);
//     // *(bool*)(output+28)=choose_bits_and_xor(1);
//     return output;
// }9
uint64_t encode_and_spread_twice(uint8_t input)
{   
    return spread_by_4(encode(input));
}
void update_psedo_random_register()
{
    uint16_t mask0=0x0001;
    uint16_t mask1=0x0004;
    uint16_t mask2=0x0008;
    uint16_t mask3=0x0020;
    for(int i=0;i<8;i++)
    {
        uint16_t new_bit=((((bool)(pseudo_random_register&mask0))!=((bool)((pseudo_random_register&mask1)>>2)))!=(((bool)((pseudo_random_register&mask2)>>3))!=((bool)((pseudo_random_register&mask3)>>5))))<<15;
        pseudo_random_register=((pseudo_random_register>>1))|new_bit;
    }
}
uint8_t generate_pseudo_random_8_bit_value()
{   update_psedo_random_register();
    return (uint8_t)(pseudo_random_register&0x00ff);
}
void reset_pseudo_random_register()
{    pseudo_random_register=0xace1;
}
void generate_pseudo_random_payload(uint8_t* payload,uint8_t length)
{
    for (int i=0;i<length;i++)
        payload[i]= generate_pseudo_random_8_bit_value();
}
void fill_buffer_in_long_range_mode_1(uint32_t* buffer, uint8_t* payload,uint8_t payload_size, uint16_t sequence_number)
{
    buffer[0]=0x00cc3cc3;
    buffer[1]=0x33c3c333;
    buffer[2]=0xcccc3cc3;
    buffer[3]=0x33c3c333;
    buffer[4]=0x3333c33c;
    buffer[5]=0xcc3c3ccc;
    for (int i=0;i<payload_size;i++)
    {  
        buffer[i+6]=encode_and_spread(payload[i]);
    }
    for (int i=0;i<7;i++)
        convolutional_registers[i]=0;

}
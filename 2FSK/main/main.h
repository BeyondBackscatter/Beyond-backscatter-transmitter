#ifndef MAIN_H_
#define MAIN_H_

#define MAX_PACKET_LEN 128
#define HEADER_LEN 9                 // 4 preamble, 4 sync, 1 payload len


/************************************************************
* STANDARD BITS
************************************************************/

#define BIT0                (0x0001) /**< Constant for bit 0 (=least significant bit) */
#define BIT1                (0x0002) /**< Constant for bit 1 (bit 0 is least significant bit) */
#define BIT2                (0x0004) /**< Constant for bit 2 (bit 0 is least significant bit) */
#define BIT3                (0x0008) /**< Constant for bit 3 (bit 0 is least significant bit) */
#define BIT4                (0x0010) /**< Constant for bit 4 (bit 0 is least significant bit) */
#define BIT5                (0x0020) /**< Constant for bit 5 (bit 0 is least significant bit) */
#define BIT6                (0x0040) /**< Constant for bit 6 (bit 0 is least significant bit) */
#define BIT7                (0x0080) /**< Constant for bit 7 (bit 0 is least significant bit) */
#define BIT8                (0x0100) /**< Constant for bit 8 (bit 0 is least significant bit) */
#define BIT9                (0x0200) /**< Constant for bit 9 (bit 0 is least significant bit) */
#define BITA                (0x0400) /**< Constant for bit 10 (bit 0 is least significant bit) */
#define BITB                (0x0800) /**< Constant for bit 11 (bit 0 is least significant bit) */
#define BITC                (0x1000) /**< Constant for bit 12 (bit 0 is least significant bit) */
#define BITD                (0x2000) /**< Constant for bit 13 (bit 0 is least significant bit) */
#define BITE                (0x4000) /**< Constant for bit 14 (bit 0 is least significant bit) */
#define BITF                (0x8000) /**< Constant for bit 15 (bit 0 is least significant bit) */

#endif /* MAIN_H_ */
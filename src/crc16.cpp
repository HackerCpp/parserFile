#include "inc/crc16.h"



unsigned short Crc16::crcFast(unsigned char const message[], int nBytes)
{
    unsigned short remainder = INITIAL_REMAINDER;
    unsigned char  data;
    int            byte;


    /*
     * Divide the message by the polynomial, a byte at a time.
     */
    for (byte = 0; byte < nBytes; ++byte)
    {
        data = (message[byte]) ^ (remainder >> (WIDTH - 8));
        remainder = crcTable[data] ^ (remainder << 8);
    }

    /*
     * The final remainder is the CRC.
     */
    return ((remainder) ^ FINAL_XOR_VALUE);

}   /* crcFast() */

unsigned short Crc16::crcSlow(unsigned char const message[], int nBytes){
    unsigned short remainder = INITIAL_REMAINDER;
    int            byte;
    unsigned char  bit;


    /*
     * Perform modulo-2 division, a byte at a time.
     */
    for (byte = 0; byte < nBytes; ++byte)
    {
        /*
         * Bring the next byte into the remainder.
         */
        remainder ^= ((message[byte]) << (WIDTH - 8));

        /*
         * Perform modulo-2 division, a bit at a time.
         */
        for (bit = 8; bit > 0; --bit)
        {
            /*
             * Try to divide the current data bit.
             */
            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }

    /*
     * The final remainder is the CRC result.
     */
    return ((remainder) ^ FINAL_XOR_VALUE);

}   /* crcSlow() */
Crc16::Crc16(){
    unsigned short remainder;
    int			   dividend;
    unsigned char  bit;


/*
 * Compute the remainder of each possible dividend.
 */
    for (dividend = 0; dividend < 256; ++dividend){
        /*
        * Start with the dividend followed by zeros.
        */
        remainder = dividend << (WIDTH - 8);

        /*
         * Perform modulo-2 division, a bit at a time.
        */
        for (bit = 8; bit > 0; --bit)
        {
            /*
             * Try to divide the current data bit.
            */
            if (remainder & TOPBIT){
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else{
                remainder = (remainder << 1);
            }
        }

        /*
        * Store the result into the table.
        */
        crcTable[dividend] = remainder;
    }
}

#ifndef CRC16_H
#define CRC16_H


class Crc16{
    unsigned short  crcTable[256];
    const unsigned short POLYNOMIAL = 0x8005;
    const unsigned short INITIAL_REMAINDER = 0x0000;
    const unsigned short FINAL_XOR_VALUE = 0x0000;
    const bool REFLECT_DATA = 0;
    const bool REFLECT_REMAINDER = 0;
    const unsigned short CHECK_VALUE = 0xBB3D;
    const unsigned short WIDTH  = 16;
    const unsigned int TOPBIT = 0x8000;
public:
    Crc16();
    unsigned short   crcSlow(unsigned char const message[], int nBytes);
    unsigned short   crcFast(unsigned char const message[], int nBytes);
};

#endif // CRC16_H

#ifndef REEDSOLOMONCODING_H
#define REEDSOLOMONCODING_H


class ReedSolomonCoding{
    static const short M = 8;
    static const short LENGTH_WORD = 255;
    static const short Tn = 16;
    const short Kn = (LENGTH_WORD-2*Tn);
    static const short Ts = 3;
    const short Ks = (LENGTH_WORD-2*Ts);
    bool deepness = 0; //!< 0 - deepness nasa; 1 - deepness shortened
    const int pp[M + 1] = { 1, 0, 1, 1, 1, 0, 0, 0, 1 };
    int alpha_to[LENGTH_WORD + 1];
    int index_of[LENGTH_WORD + 1];
    unsigned char gn[2 * Tn + 1];
    unsigned char gs[2 * Ts + 1];
    void generate_gf(void);
    void gen_poly(unsigned short TT, unsigned char *g);
    void encode_rs(unsigned char* address, char rsDeepness);

public:
    int decode_rs_nasa(unsigned char* recd);
    int decode_rs_short(unsigned char* recd);
    ReedSolomonCoding();
};

#endif // REEDSOLOMONCODING_H

#include <stdint.h>
#include <byte.h>

typedef struct
{
    byte RES; //result
    byte STRPD_RES[8]; //striped_result
    uint8_t Z; //zero
    uint8_t N; //negative
    uint8_t C; //carrier
    uint8_t V; //overflow

} ALU_OUTPUT;

ALU_OUTPUT ALU(byte A, byte B, byte A_S) {
    // I: (int A, int B, int A_S) -> O: (int8_t RES, int8_t Z, int8_t N, int8_t C, int8_t V)
    int8_t S0    = ((A >> 0 & 1) ^ ((B >> 0 & 1) ^ A_S));
    int8_t Cout0 = ((A >> 0 & 1) & ((B >> 0 & 1) ^ A_S)) | (S0 & A_S);
    S0 = S0 ^ A_S;

    int8_t S1    = ((A >> 1 & 1) ^ ((B >> 1 & 1) ^ A_S));
    int8_t Cout1 = ((A >> 1 & 1) & ((B >> 1 & 1) ^ A_S)) | (S1 & Cout0);
    S1 = S1 ^ Cout0;

    int8_t S2    = ((A >> 2 & 1) ^ ((B >> 2 & 1) ^ A_S));
    int8_t Cout2 = ((A >> 2 & 1) & ((B >> 2 & 1) ^ A_S)) | (S2 & Cout1);
    S2 = S2 ^ Cout1;

    int8_t S3    = ((A >> 3 & 1) ^ ((B >> 3 & 1) ^ A_S));
    int8_t Cout3 = ((A >> 3 & 1) & ((B >> 3 & 1) ^ A_S)) | (S3 & Cout2);
    S3 = S3 ^ Cout2;

    int8_t S4    = ((A >> 4 & 1) ^ ((B >> 4 & 1) ^ A_S));
    int8_t Cout4 = ((A >> 4 & 1) & ((B >> 4 & 1) ^ A_S)) | (S4 & Cout3);
    S4 = S4 ^ Cout3; 

    int8_t S5    = ((A >> 5 & 1) ^ ((B >> 5 & 1) ^ A_S));
    int8_t Cout5 = ((A >> 5 & 1) & ((B >> 5 & 1) ^ A_S)) | (S5 & Cout4);
    S5 = S5 ^ Cout4;

    int8_t S6    = ((A >> 6 & 1) ^ ((B >> 6 & 1) ^ A_S));
    int8_t Cout6 = ((A >> 6 & 1) & ((B >> 6 & 1) ^ A_S)) | (S6 & Cout5);
    S6 = S6 ^ Cout5;

    int8_t S7    = ((A >> 7 & 1) ^ ((B >> 7 & 1) ^ A_S));
    int8_t Cout7 = ((A >> 7 & 1) & ((B >> 7 & 1) ^ A_S)) | (S7 & Cout6);
    S7 = S7 ^ Cout6;

    return (ALU_OUTPUT) {
        .RES = 1*S0 + 2*S1 + 4*S2 + 8*S3 + 16*S4 + 32*S5 + 64*S6 + 128*S7, 
        .STRPD_RES =  {S0 , S1 , S2 , S3 , S4 , S5 , S6 , S7},
        .Z   = !(S0 | S1 | S2 | S3 | S4 | S5 | S6 | S7),
        .N   =  (S7),
        .C   =  (Cout7),
        .V   =  (Cout6 ^ Cout7)
    };
}
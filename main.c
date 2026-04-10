#include <stdio.h>
#include <stdint.h>

typedef struct
{
    int8_t RES; //result
    uint8_t Z; //zero
    uint8_t N; //negative
    uint8_t C; //carrier
    uint8_t V; //overflow

} ALU_OUTPUT;


int8_t dec2bin (int n) {
    for (int i = 31; i >= 0; i--) {
        printf("%i", n >> i & 1);
        if (!(i % 8)) printf(" ");
    }
    printf("\n");

    return (int8_t)n;
}

int8_t MUX (int a, int b, int s) {
    return (a & !s) | (b & s);
}

ALU_OUTPUT ALU(int A, int B, int A_S) {
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
        .RES =  (uint8_t)(S0 + S1*2 + S2*4 + S3*8 + S4*16 + S5*32 + S6*64 + S7*128),
        .Z   = !(S0 | S1 | S2 | S3 | S4 | S5 | S6 | S7),
        .N   =  (S7),
        .C   =  (Cout7),
        .V   =  (Cout6 ^ Cout7)
    };
}

int main() {
    //printf("%i\n", MUX(0, 0, 0));
    //printf("%i\n", RCA(17, 23));
    ALU_OUTPUT a = ALU(127, 1, 1);
    printf("RES: %.8b\n", (uint8_t)a.RES);
    printf("RES: %i\n", a.RES);
    printf("Z  : %.8b\n", a.Z);
    printf("N  : %.8b\n", a.N);
    printf("C  : %.8b\n", a.C);
    printf("V  : %.8b\n", a.V);
    return 0;
}

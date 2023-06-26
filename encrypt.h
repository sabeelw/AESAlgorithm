#include "common.h"
#ifndef CRYPTO_ENCRYPT_H
#define CRYPTO_ENCRYPT_H

void ShiftRow(unsigned char *state){
    unsigned int bits = 0;
    for (int n = 1; n < 4; n++) {
        auto *i = (unsigned int *) (state+(4*n));
        bits |= 0xFF;
        *i = (*i >> 8*(n)) | ((*i & bits) << (32-(8*n)));
        bits <<= 8;
    }

}
void MixColumn(unsigned char *column){
    for(int n = 0; n < 4; n++){
        unsigned char temp[4];
        temp[0] = *(column+((4*n)+0));
        temp[1] = *(column+((4*n)+1));
        temp[2] = *(column+((4*n)+2));
        temp[3] = *(column+((4*n)+3));
        *(column+((4*n)+0)) = mul_table_2[temp[0]] ^ mul_table_3[temp[1]] ^ temp[2] ^ temp[3];
        *(column+((4*n)+1)) = mul_table_2[temp[1]] ^ mul_table_3[temp[2]] ^ temp[3] ^ temp[0];
        *(column+((4*n)+2)) = mul_table_2[temp[2]] ^ mul_table_3[temp[3]] ^ temp[0] ^ temp[1];
        *(column+((4*n)+3)) = mul_table_2[temp[3]] ^ mul_table_3[temp[0]] ^ temp[1] ^ temp[2];
    }
}
void ByteSub(unsigned char *state){
    for(int i = 0; i < 16; i++){
        state[i] = sBox[state[i]];
    }
}
void AES_encrypt(unsigned char *msg, unsigned char *expandedKey){
    unsigned char state[16];
    for (int i = 0; i < 16; ++i) {
        state[i] = msg[i];
    }

    int rounds = 9;

    AddRoundKey(state, expandedKey);



    for (int i = 0; i < rounds; i++) {
        ByteSub(state);
        TransposeMatrix(state);
        ShiftRow(state);
        TransposeMatrix(state);
        MixColumn(state);
        AddRoundKey(state, expandedKey + (16 * (i + 1)));
    }
    ByteSub(state);
    TransposeMatrix(state);
    ShiftRow(state);
    TransposeMatrix(state);
    AddRoundKey(state, expandedKey + 160);
    for (int i = 0; i < 16; i++) {
        msg[i] = state[i];
    }
}
#endif //CRYPTO_ENCRYPT_H

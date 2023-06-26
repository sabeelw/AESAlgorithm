#include "common.h"
#ifndef CRYPTO_DECRYPT_H
#define CRYPTO_DECRYPT_H


void InvShiftRow(unsigned char *state){
    unsigned int bits = 0;
    for (int n = 1; n < 4; n++) {
        auto *i = (unsigned int *) (state+(4*n));
        bits |= 0xFF000000;
        *i = (*i << 8*(n)) | ((*i & bits) >> (32-(8*n)));
        bits |= bits >> 8;
    }

}
void InvMixColumn(unsigned char *column){
    for(int n = 0; n < 4; n++){
        unsigned char temp[4];
        temp[0] = *(column+((4*n)+0));
        temp[1] = *(column+((4*n)+1));
        temp[2] = *(column+((4*n)+2));
        temp[3] = *(column+((4*n)+3));
        *(column+((4*n)+0)) = mul14[temp[0]] ^ mul11[temp[1]] ^ mul13[temp[2]] ^ mul9[temp[3]];
        *(column+((4*n)+1)) = mul14[temp[1]] ^ mul11[temp[2]] ^ mul13[temp[3]] ^ mul9[temp[0]];
        *(column+((4*n)+2)) = mul14[temp[2]] ^ mul11[temp[3]] ^ mul13[temp[0]] ^ mul9[temp[1]];
        *(column+((4*n)+3)) = mul14[temp[3]] ^ mul11[temp[0]] ^ mul13[temp[1]] ^ mul9[temp[2]];
    }
}
void InvByteSub(unsigned char *state){
    for(int i = 0; i < 16; i++){
        state[i] = inv_s[state[i]];
    }
}
void AES_decrypt(unsigned char *msg, unsigned char *expandedKey){
    unsigned char state[16];
    for (int i = 0; i < 16; ++i) {
        state[i] = msg[i];
    }
    int rounds = 9;
    AddRoundKey(state, expandedKey + 160);
    TransposeMatrix(state);
    InvShiftRow(state);
    TransposeMatrix(state);
    InvByteSub(state);


    for (int i = rounds-1; i >= 0; i--) {
        AddRoundKey(state, expandedKey + (16 * (i + 1)));
        InvMixColumn(state);
        TransposeMatrix(state);
        InvShiftRow(state);
        TransposeMatrix(state);
        InvByteSub(state);
    }
    AddRoundKey(state, expandedKey);



    for (int i = 0; i < 16; i++) {
        msg[i] = state[i];
    }
}

#endif //CRYPTO_DECRYPT_H

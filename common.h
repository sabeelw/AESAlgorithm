

#ifndef CRYPTO_COMMON_H
#define CRYPTO_COMMON_H

using namespace std;
void AddRoundKey(unsigned char *state, unsigned char *key){
    for (int i = 0; i < 16; ++i) {
        state[i] ^= key[i];
    }
}
void TransposeMatrix(unsigned char *state){
    unsigned char temp;
    for (int i = 0; i < 4; ++i) {
        for (int j = i+1; j < 4; ++j) {
            if(i != j){
                temp = *(state+((4*i)+j));
                *(state+((4*i)+j)) = *(state+((4*j)+i));
                *(state+((4*j)+i)) = temp;
            }
        }
    }
}
void KeyExpansionCore(unsigned char* in, unsigned char i){
    unsigned char t = in[0];
    in[0] = in[1];
    in[1] = in[2];
    in[2] = in[3];
    in[3] = t;
    in[0] = sBox[in[0]];
    in[1] = sBox[in[1]];
    in[2] = sBox[in[2]];
    in[3] = sBox[in[3]];
    in[0] ^= rcon[i];
}
void KeyExpansion(unsigned char *key, unsigned char *expandedKey, unsigned int keySize){
    for (int i = 0; i < keySize; ++i) {
        expandedKey[i] = key[i];
    }

    unsigned int bytesGenerated = keySize;
    unsigned int RconIter = 1;
    unsigned char temp[4];
    while (bytesGenerated < 176){
        for(int j = 0; j < 4; j++){
            temp[j] = expandedKey[j + bytesGenerated - 4];
        }
        if(bytesGenerated % 16 == 0){
            KeyExpansionCore(temp, RconIter);
            RconIter++;
        }
        for(unsigned char a = 0; a < 4; a++){
            expandedKey[bytesGenerated] = expandedKey[bytesGenerated - keySize] ^ temp[a];
            bytesGenerated++;
        }
    }
}
#endif //CRYPTO_COMMON_H

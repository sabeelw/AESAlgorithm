#include "common.h"
void TestByteSub(){
    unsigned char state[] = {
            0xD4,0x01,0xF2, 'D',
            0xD4, 0x01, 0x0A, 'H',
            0xD4, 0x01, 0x22, 'L',
            0xD5,0x01, 0x5C, 'P'
    };
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << hex<< (int)(*(state+((4*i)+j))) << " ";
        }
        cout << endl;
    }

    cout << endl << "After ByteSub" << endl;
    ByteSub(state);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << hex<< (int)(*(state+((4*i)+j))) << " ";
        }
        cout << endl;
    }

}
void TestMixColumn(){
    unsigned char state[] = {
            0xD4,0x01,0xF2, 'D',
            0xD4, 0x01, 0x0A, 'H',
            0xD4, 0x01, 0x22, 'L',
            0xD5,0x01, 0x5C, 'P'
    };
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << hex<< (int)(*(state+((4*i)+j))) << " ";
        }
        cout << endl;
    }

    cout << endl << "After MixColumns" << endl;
    MixColumn(state);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << hex<< (int)(*(state+((4*i)+j))) << " ";
        }
        cout << endl;
    }

}
void TestRotate(){
    unsigned char state[] = {
            0xD4,0x01,0xF2, 'D',
            0xD4, 0x01, 0x0A, 'H',
            0xD4, 0x01, 0x22, 'L',
            0xD5,0x01, 0x5C, 'P'
    };
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << hex<< (int)(*(state+((4*i)+j))) << " ";
        }
        cout << endl;
    }

    cout << endl << "After Rotate" << endl;
    Rotate(state);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << hex<< (int)(*(state+((4*i)+j))) << " ";
        }
        cout << endl;
    }
}
void TestKeyExpansion(){
    unsigned char key[16] = {
            0x00, 0x01, 0x02, 0x03 , 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 ,0x0A ,0x0B, 0x0C, 0x0D ,0x0E, 0x0F
    };
    unsigned char e[176];
    KeyExpansion(key, e);
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 16; j++){
            cout << hex<< (int)(*(e+((16*i)+j))) << " ";
        }
        cout << endl;
    }
}
void TestShiftRow(){
    unsigned char state[]= {
            0,1,2,3,
            4,5,6,7,
            8,9,10,11,
            12,13,14,15
    };

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << hex<< (int)(*(state+((4*i)+j))) << " ";
        }
        cout << endl;
    }

    cout << endl << "After ShiftRow" << endl;

    ShiftRow(state);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << hex<< (int)(*(state+((4*i)+j))) << " ";
        }
        cout << endl;
    }
    cout << endl << "After Transpose" << endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << hex<< (int)(*(state+((4*i)+j))) << " ";
        }
        cout << endl;
    }
    cout << endl << "After Transpose" << endl;

    InvShiftRow(state);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << hex<< (int)(*(state+((4*i)+j))) << " ";
        }
        cout << endl;
    }
    cout << endl;
}
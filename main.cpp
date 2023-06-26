#include <iostream>
#include <fstream>
#include <string>
#include "tables.h"
#include "encrypt.h"
#include "decrypt.h"
#include "common.h"




int main(int argc, char **argv) {
    if(argc < 3){
        std::cout << "Usage:" << std::endl;
        std::cout << "\t-s To encrypt a file."<< std::endl;
        std::cout << "\t-d To decrypt a file."<< std::endl;
        std::cout << "\t-p [passsword] Password used for encryption."<< std::endl;
        exit(0);
    }
    string filename;
    cout << "File to be En/Decrypted (data.txt): ";
    getline(cin,filename);
    if(filename.empty()){
        filename = "data.txt";
    }
    fstream file(filename, ios_base::in | ios_base::out);
    string text;
    while(!file.eof()){
        int c = file.get();
        if(c != EOF)
            text.push_back((char)c);
    }
    string key;
    if(argc > 2){
        if(string(argv[2]) == ("-p")){
            if(!string(argv[3]).empty()){
                key = string(argv[3]);
                cout << "From args :" << key << endl;
                if(key.size() % 16 != 0){
                    unsigned keyPadding = (key.size() / 16 + 1) * 16;
                    string paddedKey;
                    for (unsigned i = 0; i < keyPadding; ++i) {
                        if(i >= key.size()){
                            paddedKey.push_back(0);
                        }
                        else{
                            paddedKey.push_back(key[i]);
                        }
                    }
                    key = paddedKey;
                    cout << "Password : " << key << endl;
                }

            }else{
                cout << "Password Not Entered.";
                return 0;
            }
        }
    }
    auto *c = (unsigned char *) text.data();
    unsigned long long int len = text.size();
    unsigned long long int padding = len;
    unsigned char* paddedMsg;
    if(len % 16 != 0){
        padding = (len / 16 + 1) * 16;
        paddedMsg = new unsigned char[padding];
        for (int i = 0; i < padding; ++i) {
            if(i >= len) paddedMsg[i] = 0;
            else paddedMsg[i] = c[i];
        }
    }else{
        paddedMsg = c;
    }
    cout << "Key size: " << key.length() << endl;
    cout << "input from the file: " << endl;
    for(int i = 0; i < padding; i++){
        cout << hex<< (int)(*(paddedMsg+i)) << " ";
    }

    if(argc > 1){
        if(string(argv[1]) == ("-s")){
            ofstream out(filename+".enc", ios_base::out);
            cout << "Encrypting :" << filename << endl;
            unsigned char e[176];
            KeyExpansion((unsigned char *)key.c_str(), e, key.size());

            for (unsigned long long int i = 0; i < padding; i += 16) {
                AES_encrypt(paddedMsg+i, e);
            }
            for (unsigned int i = 0; i < padding; i++) {
                out.put((char)*(paddedMsg + i));
            }
            cout << "Encrypted data written in file: " << filename+".enc" << endl;
            cout << "After Encrypt\n";
        }
        if(string(argv[1]) == ("-d")){
            cout << "Decryption" << filename << endl;
            ofstream out(filename+".dec", ios_base::out);
            unsigned char e[176];
            KeyExpansion((unsigned char *)key.c_str(), e, key.size());

            for (int i = 0; i < padding; i += 16) {
                AES_decrypt(paddedMsg+i, e);
            }
            for (unsigned int i = 0; i < padding; i++) {
                if(*(paddedMsg + i) != 0)
                    out.put((char)*(paddedMsg + i));
            }
            cout << "Decrypted data written in file: " << filename+".dec" << endl;
            cout << "After Decrypt\n";
        }
    }
    for(int i = 0; i < padding; i++){
        cout << hex<< (int)(*(paddedMsg+i)) << " ";
    }
    return 0;
}


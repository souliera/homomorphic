#include <iostream>
#include <fstream>
#include <string>

#include "image_ppm.h"

using namespace std;

// void genMsg(int size) {
//     srand(time(NULL));
//
//     ofstream ofs("message.txt");
//
//     char c;
//     string msg = "";
//
//     for(int i = 0; i < size; i++) {
//         c = rand() % 93 + 32;
//         msg += c;
//     }
//
//     ofs << msg;
//
//     ofs.close();
// }

string readMsg(char *filename) {
    ifstream ifs(filename);
    string msg;

    msg.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());

    ifs.close();

    return msg;
}

void writeToLSB1(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j--) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x01) : res[k] = (img[k] & 0xFE);
            k++;
        }
    }
}

void writeToLSB2(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j -= 2) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x02) : res[k] = (img[k] & 0xFD);
            ((msg[i] >> (j-1)) & 0x01) ? res[k] = (res[k] | 0x01) : res[k] = (res[k] & 0xFE);
            k++;
        }
    }
}

void writeToLSB4(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j -= 4) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x08) : res[k] = (img[k] & 0xF7);
            ((msg[i] >> (j-1)) & 0x01) ? res[k] = (res[k] | 0x04) : res[k] = (res[k] & 0xFB);
            ((msg[i] >> (j-2)) & 0x01) ? res[k] = (res[k] | 0x02) : res[k] = (res[k] & 0xFD);
            ((msg[i] >> (j-3)) & 0x01) ? res[k] = (res[k] | 0x01) : res[k] = (res[k] & 0xFE);
            k++;
        }
    }
}

void writeToLSB8(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        ((msg[i] >> 7) & 0x01) ? res[k] = (img[k] | 0x80) : res[k] = (img[k] & 0x7F);
        ((msg[i] >> 6) & 0x01) ? res[k] = (res[k] | 0x40) : res[k] = (res[k] & 0xBF);
        ((msg[i] >> 5) & 0x01) ? res[k] = (res[k] | 0x20) : res[k] = (res[k] & 0xDF);
        ((msg[i] >> 4) & 0x01) ? res[k] = (res[k] | 0x10) : res[k] = (res[k] & 0xEF);
        ((msg[i] >> 3) & 0x01) ? res[k] = (res[k] | 0x08) : res[k] = (res[k] & 0xF7);
        ((msg[i] >> 2) & 0x01) ? res[k] = (res[k] | 0x04) : res[k] = (res[k] & 0xFB);
        ((msg[i] >> 1) & 0x01) ? res[k] = (res[k] | 0x02) : res[k] = (res[k] & 0xFD);
        ((msg[i] >> 0) & 0x01) ? res[k] = (res[k] | 0x01) : res[k] = (res[k] & 0xFE);
        k++;
    }
}

string readToLSB(OCTET *img, int size) {
    string msg = "";
    char c = ' ';

    for(int i = 0; i < size/8; i++) {
        (img[(i*8)+0] & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        (img[(i*8)+1] & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        (img[(i*8)+2] & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        (img[(i*8)+3] & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        (img[(i*8)+4] & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        (img[(i*8)+5] & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        (img[(i*8)+6] & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        (img[(i*8)+7] & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

    return (string)msg;
}

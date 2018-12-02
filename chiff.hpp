#include <iostream>
#include <string>

#include "image_ppm.h"

using namespace std;

void XORImage(OCTET *imgClr, OCTET *imgEnc, int size, int key) {
    srand(key);

    for(int i = 0; i < size; i++) {
        imgEnc[i] = imgClr[i] ^ (rand() % 256);
    }
}

string XORMessageTo1LSB(string msg, int key) {
    srand(key);

    string tmp;
    char c = ' ';
    int r;

    for(unsigned int i = 0; i < msg.size(); i++) {
        r = rand() % 256;
        (r & 0x01) ^ ((msg[i] >> 7) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        r = rand() % 256;
        (r & 0x01) ^ ((msg[i] >> 6) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        r = rand() % 256;
        (r & 0x01) ^ ((msg[i] >> 5) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        r = rand() % 256;
        (r & 0x01) ^ ((msg[i] >> 4) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        r = rand() % 256;
        (r & 0x01) ^ ((msg[i] >> 3) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        r = rand() % 256;
        (r & 0x01) ^ ((msg[i] >> 2) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        r = rand() % 256;
        (r & 0x01) ^ ((msg[i] >> 1) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        r = rand() % 256;
        (r & 0x01) ^ ((msg[i] >> 0) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        tmp += (char)c;
    }

    return tmp;
}

string XORMessageTo2LSB(string msg, int key) {
    srand(key);

    string tmp;
    char c = ' ';
    int r;

    for(unsigned int i = 0; i < msg.size(); i++) {
        r = rand() % 256;
        ((r >> 1) & 0x01) ^ ((msg[i] >> 7) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((r >> 0) & 0x01) ^ ((msg[i] >> 6) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        r = rand() % 256;
        ((r >> 1) & 0x01) ^ ((msg[i] >> 5) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((r >> 0) & 0x01) ^ ((msg[i] >> 4) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        r = rand() % 256;
        ((r >> 1) & 0x01) ^ ((msg[i] >> 3) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((r >> 0) & 0x01) ^ ((msg[i] >> 2) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        r = rand() % 256;
        ((r >> 1) & 0x01) ^ ((msg[i] >> 1) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((r >> 0) & 0x01) ^ ((msg[i] >> 0) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        tmp += (char)c;
    }

    return tmp;
}

string XORMessageTo4LSB(string msg, int key) {
    srand(key);

    string tmp;
    char c = ' ';
    int r;

    for(unsigned int i = 0; i < msg.size(); i++) {
        r = rand() % 256;
        ((r >> 3) & 0x01) ^ ((msg[i] >> 7) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((r >> 2) & 0x01) ^ ((msg[i] >> 6) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((r >> 1) & 0x01) ^ ((msg[i] >> 5) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((r >> 0) & 0x01) ^ ((msg[i] >> 4) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        r = rand() % 256;
        ((r >> 3) & 0x01) ^ ((msg[i] >> 3) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((r >> 2) & 0x01) ^ ((msg[i] >> 2) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((r >> 1) & 0x01) ^ ((msg[i] >> 1) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((r >> 0) & 0x01) ^ ((msg[i] >> 0) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        tmp += (char)c;
    }

    return tmp;
}

string XORMessageTo8LSB(string msg, int key) {
    srand(key);

    string tmp;
    char c = ' ';
    int r;

    for(unsigned int i = 0; i < msg.size(); i++) {
        r = rand() % 256;
        ((r >> 7) & 0x1) ^ ((msg[i] >> 7) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((r >> 6) & 0x1) ^ ((msg[i] >> 6) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((r >> 5) & 0x1) ^ ((msg[i] >> 5) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((r >> 4) & 0x1) ^ ((msg[i] >> 4) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        ((r >> 3) & 0x1) ^ ((msg[i] >> 3) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((r >> 2) & 0x1) ^ ((msg[i] >> 2) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((r >> 1) & 0x1) ^ ((msg[i] >> 1) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((r >> 0) & 0x1) ^ ((msg[i] >> 0) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        tmp += (char)c;
    }

    return tmp;
}

// void scramblingImage(OCTET *imgIn, OCTET *imgOut, int size, int key) {
//     srand(key);
//
//     for(int i = 0; i < size; i++) {
//         imgOut[i] = imgIn[rand() % size];
//     }
// }

// string scramblingMessage(string msgClr, int key) {
//     srand(key);
//
//     string tmp;
//     int size = msgClr.size();
//     char c = ' ';
//     int r;
//
//     for(int i = 0; i < size; i++) {
//         r = rand() % size / 8;
//         (msgClr[r/8] >> (r % 8)) & 0x01 ? c = c | 0x80 : c = c & 0x7F;
//         r = rand() % size / 8;
//         (msgClr[r/8] >> (r % 8)) & 0x01 ? c = c | 0x40 : c = c & 0xBF;
//         r = rand() % size / 8;
//         (msgClr[r/8] >> (r % 8)) & 0x01 ? c = c | 0x20 : c = c & 0xDF;
//         r = rand() % size / 8;
//         (msgClr[r/8] >> (r % 8)) & 0x01 ? c = c | 0x10 : c = c & 0xEF;
//         r = rand() % size / 8;
//         (msgClr[r/8] >> (r % 8)) & 0x01 ? c = c | 0x08 : c = c & 0xF7;
//         r = rand() % size / 8;
//         (msgClr[r/8] >> (r % 8)) & 0x01 ? c = c | 0x04 : c = c & 0xFB;
//         r = rand() % size / 8;
//         (msgClr[r/8] >> (r % 8)) & 0x01 ? c = c | 0x02 : c = c & 0xFD;
//         r = rand() % size / 8;
//         (msgClr[r/8] >> (r % 8)) & 0x01 ? c = c | 0x01 : c = c & 0xFE;
//         tmp += (char)c;
//     }
//
//     return tmp;
// }

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

string readMsg(string filename) {
    ifstream ifs(filename);
    string msg;

    msg.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());

    ifs.close();

    return msg;
}

void writeMsg(string filename, string msg) {
    ofstream ofs(filename);
    ofs << msg;
    ofs.close();
}



void writeTo1LSB(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j--) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x01) : res[k] = (img[k] & 0xFE);
            k++;
        }
    }
}

void writeTo2LSB(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j -= 2) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x02) : res[k] = (img[k] & 0xFD);
            ((msg[i] >> (j-1)) & 0x01) ? res[k] = (res[k] | 0x01) : res[k] = (res[k] & 0xFE);
            k++;
        }
    }
}

void writeTo4LSB(OCTET *img, OCTET *res, string msg) {
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

void writeTo8LSB(OCTET *img, OCTET *res, string msg) {
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

string readTo1LSB(OCTET *img, int size) {
    string msg;
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

    return msg;
}

string readTo2LSB(OCTET *img, int size) {
    string msg;
    char c = ' ';

    for(int i = 0; i < size/4; i++) {
        ((img[(i*4)+0] >> 1) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((img[(i*4)+0] >> 0) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((img[(i*4)+1] >> 1) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((img[(i*4)+1] >> 0) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        ((img[(i*4)+2] >> 1) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((img[(i*4)+2] >> 0) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((img[(i*4)+3] >> 1) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((img[(i*4)+3] >> 0) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

    return msg;
}

string readTo4LSB(OCTET *img, int size) {
    string msg;
    char c = ' ';

    for(int i = 0; i < size/2; i++) {
        ((img[(i*2)+0] >> 3) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((img[(i*2)+0] >> 2) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((img[(i*2)+0] >> 1) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((img[(i*2)+0] >> 0) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        ((img[(i*2)+1] >> 3) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((img[(i*2)+1] >> 2) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((img[(i*2)+1] >> 1) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((img[(i*2)+1] >> 0) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

    return msg;
}

string readTo8LSB(OCTET *img, int size) {
    string msg;
    char c = ' ';

    for(int i = 0; i < size; i++) {
        ((img[i] >> 7) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((img[i] >> 6) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((img[i] >> 5) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((img[i] >> 4) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        ((img[i] >> 3) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((img[i] >> 2) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((img[i] >> 1) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((img[i] >> 0) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

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
        for(int j = 7; j >= 0; j--) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x02) : res[k] = (img[k] & 0xFD);
            k++;
        }
    }
}

void writeToLSB3(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j--) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x04) : res[k] = (img[k] & 0xFB);
            k++;
        }
    }
}

void writeToLSB4(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j--) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x08) : res[k] = (img[k] & 0xF7);
            k++;
        }
    }
}

void writeToLSB5(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j--) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x10) : res[k] = (img[k] & 0xEF);
            k++;
        }
    }
}

void writeToLSB6(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j--) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x20) : res[k] = (img[k] & 0xDF);
            k++;
        }
    }
}

void writeToLSB7(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j--) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x40) : res[k] = (img[k] & 0xBF);
            k++;
        }
    }
}

void writeToLSB8(OCTET *img, OCTET *res, string msg) {
    int k = 0;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j--) {
            ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x80) : res[k] = (img[k] & 0x7F);
            k++;
        }
    }
}

string readToLSB1(OCTET *img, int size) {
    string msg;
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

    return msg;
}

string readToLSB2(OCTET *img, int size) {
    string msg;
    char c = ' ';

    for(int i = 0; i < size/8; i++) {
        ((img[(i*8)+0] >> 1) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((img[(i*8)+1] >> 1) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((img[(i*8)+2] >> 1) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((img[(i*8)+3] >> 1) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        ((img[(i*8)+4] >> 1) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((img[(i*8)+5] >> 1) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((img[(i*8)+6] >> 1) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((img[(i*8)+7] >> 1) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

    return msg;
}

string readToLSB3(OCTET *img, int size) {
    string msg;
    char c = ' ';

    for(int i = 0; i < size/8; i++) {
        ((img[(i*8)+0] >> 2) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((img[(i*8)+1] >> 2) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((img[(i*8)+2] >> 2) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((img[(i*8)+3] >> 2) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        ((img[(i*8)+4] >> 2) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((img[(i*8)+5] >> 2) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((img[(i*8)+6] >> 2) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((img[(i*8)+7] >> 2) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

    return msg;
}

string readToLSB4(OCTET *img, int size) {
    string msg;
    char c = ' ';

    for(int i = 0; i < size/8; i++) {
        ((img[(i*8)+0] >> 3) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((img[(i*8)+1] >> 3) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((img[(i*8)+2] >> 3) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((img[(i*8)+3] >> 3) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        ((img[(i*8)+4] >> 3) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((img[(i*8)+5] >> 3) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((img[(i*8)+6] >> 3) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((img[(i*8)+7] >> 3) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

    return msg;
}

string readToLSB5(OCTET *img, int size) {
    string msg;
    char c = ' ';

    for(int i = 0; i < size/8; i++) {
        ((img[(i*8)+0] >> 4) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((img[(i*8)+1] >> 4) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((img[(i*8)+2] >> 4) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((img[(i*8)+3] >> 4) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        ((img[(i*8)+4] >> 4) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((img[(i*8)+5] >> 4) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((img[(i*8)+6] >> 4) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((img[(i*8)+7] >> 4) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

    return msg;
}

string readToLSB6(OCTET *img, int size) {
    string msg;
    char c = ' ';

    for(int i = 0; i < size/8; i++) {
        ((img[(i*8)+0] >> 5) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((img[(i*8)+1] >> 5) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((img[(i*8)+2] >> 5) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((img[(i*8)+3] >> 5) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        ((img[(i*8)+4] >> 5) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((img[(i*8)+5] >> 5) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((img[(i*8)+6] >> 5) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((img[(i*8)+7] >> 5) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

    return msg;
}

string readToLSB7(OCTET *img, int size) {
    string msg;
    char c = ' ';

    for(int i = 0; i < size/8; i++) {
        ((img[(i*8)+0] >> 6) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((img[(i*8)+1] >> 6) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((img[(i*8)+2] >> 6) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((img[(i*8)+3] >> 6) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        ((img[(i*8)+4] >> 6) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((img[(i*8)+5] >> 6) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((img[(i*8)+6] >> 6) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((img[(i*8)+7] >> 6) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

    return msg;
}

string readToLSB8(OCTET *img, int size) {
    string msg;
    char c = ' ';

    for(int i = 0; i < size/8; i++) {
        ((img[(i*8)+0] >> 7) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        ((img[(i*8)+1] >> 7) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        ((img[(i*8)+2] >> 7) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        ((img[(i*8)+3] >> 7) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        ((img[(i*8)+4] >> 7) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        ((img[(i*8)+5] >> 7) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        ((img[(i*8)+6] >> 7) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        ((img[(i*8)+7] >> 7) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

    return msg;
}



void writeTo1LSBRandom(OCTET *img, OCTET *res, string msg, int key) {
    srand(key);

    int k = 0;
    int r;

    for(unsigned int i = 0; i < msg.size(); i++) {
        for(int j = 7; j >= 0; j--) {
            r = rand() % 4;
            switch(r) {
                case 0:
                    ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x01) : res[k] = (img[k] & 0xFE);
                    break;
                case 1:
                    ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x02) : res[k] = (img[k] & 0xFD);
                    break;
                case 2:
                    ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x04) : res[k] = (img[k] & 0xFB);
                    break;
                case 3:
                    ((msg[i] >> j) & 0x01) ? res[k] = (img[k] | 0x08) : res[k] = (img[k] & 0xF7);
                    break;
            }
            k++;
        }
    }
}

string readTo1LSBRandom(OCTET *img, int size, int key) {
    srand(key);

    string msg;
    char c = ' ';
    int r;

    for(int i = 0; i < size/8; i++) {
        r = rand() % 4;
        ((img[(i*8)+0] >> r) & 0x01) ? c = c | 0x80 : c = c & 0x7F;
        r = rand() % 4;
        ((img[(i*8)+1] >> r) & 0x01) ? c = c | 0x40 : c = c & 0xBF;
        r = rand() % 4;
        ((img[(i*8)+2] >> r) & 0x01) ? c = c | 0x20 : c = c & 0xDF;
        r = rand() % 4;
        ((img[(i*8)+3] >> r) & 0x01) ? c = c | 0x10 : c = c & 0xEF;
        r = rand() % 4;
        ((img[(i*8)+4] >> r) & 0x01) ? c = c | 0x08 : c = c & 0xF7;
        r = rand() % 4;
        ((img[(i*8)+5] >> r) & 0x01) ? c = c | 0x04 : c = c & 0xFB;
        r = rand() % 4;
        ((img[(i*8)+6] >> r) & 0x01) ? c = c | 0x02 : c = c & 0xFD;
        r = rand() % 4;
        ((img[(i*8)+7] >> r) & 0x01) ? c = c | 0x01 : c = c & 0xFE;
        msg += (char)c;
    }

    return msg;
}

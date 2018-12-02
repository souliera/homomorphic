#include <iostream>
#include <fstream>
#include <string>

#include "image_ppm.h"
#include "stegano.hpp"
#include "chiff.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 4) {
        cout << "Usage: " << argv[0] << " imageIn msgFile key" << endl;
        return 1;
    }

    // declaration

    OCTET *imgClr, *imgEnc, *imgDec, *imgHid;
    int width, height, size;

    string msgClr, msgEnc, msgDec;

    // initialisation

    lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
    size = height * width;
    allocation_tableau(imgClr, OCTET, size);
    allocation_tableau(imgEnc, OCTET, size);
    allocation_tableau(imgDec, OCTET, size);
    allocation_tableau(imgHid, OCTET, size);

    // programme

    /*
    lire_image_pgm(argv[1], imgClr, size);
    msgClr = readMsg(argv[2]);
    writeToLSB1(imgClr, imgHid, msgClr);
    ecrire_image_pgm((char*)"rsc/hide_LSB1.pgm", imgHid, height, width);
    lire_image_pgm(argv[1], imgClr, size);
    msgClr = readMsg(argv[2]);
    writeToLSB2(imgClr, imgHid, msgClr);
    ecrire_image_pgm((char*)"rsc/hide_LSB2.pgm", imgHid, height, width);
    lire_image_pgm(argv[1], imgClr, size);
    msgClr = readMsg(argv[2]);
    writeToLSB3(imgClr, imgHid, msgClr);
    ecrire_image_pgm((char*)"rsc/hide_LSB3.pgm", imgHid, height, width);
    lire_image_pgm(argv[1], imgClr, size);
    msgClr = readMsg(argv[2]);
    writeToLSB4(imgClr, imgHid, msgClr);
    ecrire_image_pgm((char*)"rsc/hide_LSB4.pgm", imgHid, height, width);
    lire_image_pgm(argv[1], imgClr, size);
    msgClr = readMsg(argv[2]);
    writeToLSB5(imgClr, imgHid, msgClr);
    ecrire_image_pgm((char*)"rsc/hide_LSB5.pgm", imgHid, height, width);
    lire_image_pgm(argv[1], imgClr, size);
    msgClr = readMsg(argv[2]);
    writeToLSB6(imgClr, imgHid, msgClr);
    ecrire_image_pgm((char*)"rsc/hide_LSB6.pgm", imgHid, height, width);
    lire_image_pgm(argv[1], imgClr, size);
    msgClr = readMsg(argv[2]);
    writeToLSB7(imgClr, imgHid, msgClr);
    ecrire_image_pgm((char*)"rsc/hide_LSB7.pgm", imgHid, height, width);
    lire_image_pgm(argv[1], imgClr, size);
    msgClr = readMsg(argv[2]);
    writeToLSB8(imgClr, imgHid, msgClr);
    ecrire_image_pgm((char*)"rsc/hide_LSB8.pgm", imgHid, height, width);
    //*/

    lire_image_pgm(argv[1], imgClr, size);
    msgClr = readMsg(argv[2]);
    writeTo1LSBRandom(imgClr, imgHid, msgClr, atoi(argv[3]));
    ecrire_image_pgm((char*)"rsc/hide_1LSB_random.pgm", imgHid, height, width);

    lire_image_pgm(argv[1], imgHid, size);
    msgClr = readTo1LSBRandom(imgHid, size, atoi(argv[3]));
    writeMsg("rsc/messageTest3.txt", msgClr);

    /*
    lire_image_pgm(argv[1], imgClr, size);
    msgClr = readMsg(argv[2]);
    writeToLSB(imgClr, imgHid, msgClr);
    XORImage(imgHid, imgEnc, size, atoi(argv[3]));
    ecrire_image_pgm((char*)"rsc/hide_encrypt_XOR4.pgm", imgEnc, height, width);

    lire_image_pgm(argv[1], imgClr, size);
    XORImage(imgClr, imgEnc, size, atoi(argv[3]));
    msgClr = readMsg(argv[2]);
    msgEnc = XORMessageTo4LSB(msgClr, atoi(argv[3]));
    writeTo4LSB(imgEnc, imgHid, msgEnc);
    ecrire_image_pgm((char*)"rsc/encrypt_hide_XOR4.pgm", imgHid, height, width);
    //*/

    /*
    lire_image_pgm(argv[1], imgEnc, size);
    msgEnc = readTo4LSB(imgEnc, size);
    msgClr = XORMessageTo4LSB(msgEnc, atoi(argv[3]));
    writeMsg("rsc/messageTest1.txt", msgClr);
    XORImage(imgEnc, imgHid, size, atoi(argv[3]));
    ecrire_image_pgm((char*)"rsc/dehide_decrypt_XOR4.pgm", imgHid, height, width);

    lire_image_pgm(argv[1], imgEnc, size);
    XORImage(imgEnc, imgHid, size, atoi(argv[3]));
    msgClr = readTo4LSB(imgHid, size);
    writeMsg("rsc/messageTest2.txt", msgClr);
    ecrire_image_pgm((char*)"rsc/decrypt_dehide_XOR4.pgm", imgHid, height, width);
    //*/

    /*
    string message = "abc!";
    string chiff = XORMessageTo8LSB(message, 12);
    string dechiff = XORMessageTo8LSB(chiff, 12);

    cout << message << endl;
    cout << chiff << endl;
    cout << dechiff << endl;
    //*/

    // end

    free(imgClr);
    free(imgEnc);

    return 0;
}

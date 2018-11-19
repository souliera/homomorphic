#include <iostream>
#include <string>

#include "image_ppm.h"
#include "stegano.hpp"
#include "chiff.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 5 || argv[4] != 'c' || argv[4] != 'd') {
        cout << "Usage: " << argv[0] << " imageIn imageOut msgFile type" << endl;
        cout << "\tType: c - chiffrer / d - dechiffrer" << endl;
        exit(EXIT_FAILURE);
    }

    // declaration

    OCTET *imgIn, *imgOut;
    int width, height, size;

    string msg, msgRes;

    // initialisation

    lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
    size = height * width;
    allocation_tableau(imgIn, OCTET, size);
    allocation_tableau(imgOut, OCTET, size);
    lire_image_pgm(argv[1], imgIn, size);

    // programme

    if(argv[4] == 'c') {
        cout << "generate message..." << endl;
        msg = readMsg(argv[3]);

        cout << "hide message..." << endl;
        writeToLSB8(imgIn, imgOut, msg);

        ecrire_image_pgm(argv[2], imgOut, height, width);
    } else {

    }

    free(imgIn);
    free(imgOut);

    exit(EXIT_SUCCESS);
}

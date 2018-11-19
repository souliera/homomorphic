#include <iostream>

#include "image_ppm.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 3) {
        cout << "Usage: " << argv[0] << " imageRef imageTest" << endl;
        exit(EXIT_FAILURE);
    }

    OCTET *imgRef, *imgTest;
    int width, height, size;

    lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
    size = width * height;
    allocation_tableau(imgRef, OCTET, size);
    allocation_tableau(imgTest, OCTET, size);
    lire_image_pgm(argv[1], imgRef, size);
    lire_image_pgm(argv[2], imgTest, size);

    double mse, psnr;
    mse = psnr = 0.0;

    for(int i = 0; i < size; i++) {
        mse += (double)pow(imgRef[i] - imgTest[i], 2);
    }

    mse /= size;

    psnr = 10.0 * log10(pow(255.0, 2.0) / mse);

    cout << "Le PSNR entre " << argv[1] << " et " << argv[2] << "est de " << psnr << endl;

    free(imgRef);
    free(imgTest);

    exit(EXIT_SUCCESS);
}

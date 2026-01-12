#ifndef ROT_NEG_H
#define ROT_NEG_H

#include "pgm.h"

PGMImage* negateImage(PGMImage *img);
PGMImage* rotateImage(PGMImage *img, int angle);
PGMImage* rotateImageTheta(PGMImage *img, double theta);

#endif

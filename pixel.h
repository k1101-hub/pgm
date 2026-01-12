#ifndef PIXEL_H
#define PIXEL_H

#include "pgm.h"

int getPixel(PGMImage *img, int row, int col);
void setPixel(PGMImage *img, int row, int col, int value);
int isValidPixel(PGMImage *img, int row, int col);

#endif

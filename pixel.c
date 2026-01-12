#include "pixel.h"

int getPixel(PGMImage *img, int row, int col) {
    if (!img) return 0;
    return img->pixels[row][col];
}

void setPixel(PGMImage *img, int row, int col, int value) {
    if (!img) return;
    img->pixels[row][col] = value;
}

int isValidPixel(PGMImage *img, int row, int col) {
    return img && row >= 0 && row < img->rows && col >= 0 && col < img->cols;
}

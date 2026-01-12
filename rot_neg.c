#include <stdlib.h>
#include <math.h>
#include "rot_neg.h"
#include "pixel.h"

PGMImage* negateImage(PGMImage *img) {
    if (!img) return NULL;
    PGMImage *neg = copyImage(img);
    for (int i = 0; i < img->rows; i++)
        for (int j = 0; j < img->cols; j++)
            neg->pixels[i][j] = img->max_gray - img->pixels[i][j];
    return neg;
}

PGMImage* rotateImage(PGMImage *img, int angle) {
    if (!img) return NULL;
    PGMImage *rotated = NULL;

    switch (angle) {
        case 0:
            return copyImage(img);
        case 90:
            rotated = initImage(img->cols, img->rows, img->max_gray);
            for (int i = 0; i < img->rows; i++)
                for (int j = 0; j < img->cols; j++)
                    rotated->pixels[img->cols - 1 - j][i] = img->pixels[i][j];
            break;
        case 180:
            rotated = initImage(img->rows, img->cols, img->max_gray);
            for (int i = 0; i < img->rows; i++)
                for (int j = 0; j < img->cols; j++)
                    rotated->pixels[img->rows - 1 - i][img->cols - 1 - j] = img->pixels[i][j];
            break;
        case 270:
            rotated = initImage(img->cols, img->rows, img->max_gray);
            for (int i = 0; i < img->rows; i++)
                for (int j = 0; j < img->cols; j++)
                    rotated->pixels[j][img->rows - 1 - i] = img->pixels[i][j];
            break;
    }
    return rotated;
}

PGMImage* rotateImageTheta(PGMImage *img, double theta) {
    if (!img) return NULL;
    PGMImage *rot = initImage(img->rows, img->cols, img->max_gray);

    double cx = img->cols / 2.0;
    double cy = img->rows / 2.0;
    double cosT = cos(theta);
    double sinT = sin(theta);

    for (int i = 0; i < rot->rows; i++) {
        for (int j = 0; j < rot->cols; j++) {
            double x = j - cx;
            double y = i - cy;
            double srcX = x * cosT + y * sinT + cx;
            double srcY = -x * sinT + y * cosT + cy;
            int r = (int)(srcY + 0.5);
            int c = (int)(srcX + 0.5);
            if (isValidPixel(img, r, c))
                rot->pixels[i][j] = img->pixels[r][c];
        }
    }
    return rot;
}

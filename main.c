#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pgm.h"
#include "rot_neg.h"

int main() {
    PGMImage *img = loadPGM("sample.pgm");
    if (!img) {
        img = initImage(7, 24, 15);
        for (int i = 0; i < img->rows; i++) {
            for (int j = 0; j < img->cols; j++) {
                img->pixels[i][j] = (i + j) % (img->max_gray + 1);
            }
        }
        savePGM(img, "sample_created.pgm");
    }

    printf("PGM info: rows=%d cols=%d max_gray=%d\n",
           getRows(img), getCols(img), getMaxGray(img));

    int choice;
    printf("Choose rotation type:\n");
    printf("1 - Fixed angle (0, 90, 180, 270)\n");
    printf("2 - Arbitrary angle\n");
    scanf("%d", &choice);

    if (choice == 1) {
        int angle;
        printf("Enter angle (0, 90, 180, 270): ");
        scanf("%d", &angle);
        PGMImage *rot = rotateImage(img, angle);
        if (rot) {
            savePGM(rot, "rotated.pgm");
            freeImage(rot);
        }
    } else if (choice == 2) {
        double degrees;
        printf("Enter angle : ");
        scanf("%lf", &degrees);
        double theta = degrees * M_PI / 180.0;
        PGMImage *rotTheta = rotateImageTheta(img, theta);
        if (rotTheta) {
            savePGM(rotTheta, "rotated_theta.pgm");
            freeImage(rotTheta);
        }
    }

    PGMImage *neg = negateImage(img);
    if (neg) {
        savePGM(neg, "negated.pgm");
        freeImage(neg);
    }

    freeImage(img);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"

PGMImage* initImage(int rows, int cols, int max_gray) {
    PGMImage *img = (PGMImage*)malloc(sizeof(PGMImage));
    if (!img) return NULL;

    strcpy(img->format, "P2");
    img->rows = rows;
    img->cols = cols;
    img->max_gray = max_gray;

    img->pixels = (int**)malloc(rows * sizeof(int*));
    if (!img->pixels) {
        free(img);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        img->pixels[i] = (int*)malloc(cols * sizeof(int));
        if (!img->pixels[i]) {
            for (int k = 0; k < i; k++) free(img->pixels[k]);
            free(img->pixels);
            free(img);
            return NULL;
        }
        for (int j = 0; j < cols; j++)
            img->pixels[i][j] = 0;
    }
    return img;
}

void freeImage(PGMImage *img) {
    if (!img) return;
    if (img->pixels) {
        for (int i = 0; i < img->rows; i++)
            free(img->pixels[i]);
        free(img->pixels);
    }
    free(img);
}

PGMImage* copyImage(PGMImage *src) {
    if (!src) return NULL;
    PGMImage *copy = initImage(src->rows, src->cols, src->max_gray);
    if (!copy) return NULL;

    for (int i = 0; i < src->rows; i++)
        for (int j = 0; j < src->cols; j++)
            copy->pixels[i][j] = src->pixels[i][j];

    return copy;
}

PGMImage* loadPGM(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    char format[3];
    int cols, rows, max_gray;

    if (fscanf(file, "%2s", format) != 1 || strcmp(format, "P2") != 0) {
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d %d %d", &cols, &rows, &max_gray) != 3) {
        fclose(file);
        return NULL;
    }

    PGMImage *img = initImage(rows, cols, max_gray);
    if (!img) {
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fscanf(file, "%d", &img->pixels[i][j]);

    fclose(file);
    return img;
}

int savePGM(PGMImage *img, const char *filename) {
    if (!img) return 0;

    FILE *file = fopen(filename, "w");
    if (!file) return 0;

    fprintf(file, "%s\n", img->format);
    fprintf(file, "%d %d\n", img->cols, img->rows);
    fprintf(file, "%d\n", img->max_gray);

    for (int i = 0; i < img->rows; i++) {
        for (int j = 0; j < img->cols; j++)
            fprintf(file, "%d ", img->pixels[i][j]);
        fprintf(file, "\n");
    }

    fclose(file);
    return 1;
}

int getRows(const PGMImage *img) { return img ? img->rows : -1; }
int getCols(const PGMImage *img) { return img ? img->cols : -1; }
int getMaxGray(const PGMImage *img) { return img ? img->max_gray : -1; }

void setImageInfo(PGMImage *img, int rows, int cols, int max_gray) {
    if (!img) return;
    img->rows = rows;
    img->cols = cols;
    img->max_gray = max_gray;
}

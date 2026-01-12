#ifndef PGM_H
#define PGM_H

typedef struct {
    char format[3];
    int cols;
    int rows;
    int max_gray;
    int **pixels;
} PGMImage;

PGMImage* initImage(int rows, int cols, int max_gray);
void freeImage(PGMImage *img);

PGMImage* copyImage(PGMImage *src);

PGMImage* loadPGM(const char *filename);
int savePGM(PGMImage *img, const char *filename);

int getRows(const PGMImage *img);
int getCols(const PGMImage *img);
int getMaxGray(const PGMImage *img);
void setImageInfo(PGMImage *img, int rows, int cols, int max_gray);

#endif

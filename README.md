# pgm

A small C library and CLI demo for loading, transforming, and saving **PGM (Portable Gray Map)** images supporting fixed and arbitrary-angle rotation, negation, and manual pixel access, with no external dependencies.

## Features

- **Load / save** PGM images from disk (`loadPGM`, `savePGM`)
- **Create images from scratch** with `initImage(rows, cols, max_gray)`
- **Copy / free** images safely (`copyImage`, `freeImage`)
- **Rotate** by fixed angles — 0°, 90°, 180°, 270° (`rotateImage`)
- **Rotate** by an arbitrary angle in radians (`rotateImageTheta`)
- **Negate** an image's grayscale values (`negateImage`)
- **Pixel-level access** helpers (`pixel.c` / `pixel.h`)
- Simple accessors: `getRows`, `getCols`, `getMaxGray`, `setImageInfo`

## Project structure

```
.
├── main.c        # CLI demo: loads/generates an image, applies a rotation, then negates it
├── pgm.c / .h    # Core PGMImage type: init, load, save, copy, free, accessors
├── pixel.c / .h  # Pixel-level read/write helpers
├── rot_neg.c / .h# Rotation (fixed + arbitrary angle) and negation operations
└── sample.pgm    # Example PGM image used by the demo
```

## Build

No build system is included — compile the sources directly with any C compiler (requires linking the math library for `rotateImageTheta`):

```bash
gcc -o pgm main.c pgm.c pixel.c rot_neg.c -lm
```

## Usage

Run the compiled binary from a directory containing `sample.pgm` (or let it generate one automatically if missing):

```bash
./pgm
```

The program will:

1. Try to load `sample.pgm`. If it's not found, it generates a 7×24 gradient test image and saves it as `sample_created.pgm`.
2. Print the image's dimensions and max gray value.
3. Prompt you to choose a rotation mode:
   - `1` — Fixed angle (`0`, `90`, `180`, or `270`) → saved as `rotated.pgm`
   - `2` — Arbitrary angle in degrees → saved as `rotated_theta.pgm`
4. Apply a negation to the (unrotated) original image → saved as `negated.pgm`

### Example session

```
$ ./pgm
PGM info: rows=7 cols=24 max_gray=15
Choose rotation type:
1 - Fixed angle (0, 90, 180, 270)
2 - Arbitrary angle
1
Enter angle (0, 90, 180, 270): 90
```

This produces `rotated.pgm` and `negated.pgm` alongside the original image.

## PGMImage struct

```c
typedef struct {
    char format[3];   // e.g. "P2" / "P5"
    int  cols;
    int  rows;
    int  max_gray;
    int  **pixels;
} PGMImage;
```

## API reference

| Function | Description |
|---|---|
| `PGMImage* initImage(int rows, int cols, int max_gray)` | Allocates a new blank image |
| `void freeImage(PGMImage *img)` | Releases all memory associated with an image |
| `PGMImage* copyImage(PGMImage *src)` | Deep-copies an image |
| `PGMImage* loadPGM(const char *filename)` | Reads a `.pgm` file from disk |
| `int savePGM(PGMImage *img, const char *filename)` | Writes an image to disk |
| `int getRows(const PGMImage *img)` | Returns row count |
| `int getCols(const PGMImage *img)` | Returns column count |
| `int getMaxGray(const PGMImage *img)` | Returns max gray value |
| `void setImageInfo(PGMImage *img, int rows, int cols, int max_gray)` | Updates image metadata |
| `PGMImage* negateImage(PGMImage *img)` | Returns the negative of an image |
| `PGMImage* rotateImage(PGMImage *img, int angle)` | Rotates by 0/90/180/270° |
| `PGMImage* rotateImageTheta(PGMImage *img, double theta)` | Rotates by an arbitrary angle (radians) |

## Requirements

- A C compiler (GCC, Clang, etc.)
- Standard C library + `libm`

## Contributors

- Hamza Mebrouk
- "k1101-hub"

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

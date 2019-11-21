// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }

    // remember filenames and resize factor
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // makes sure n is correct
    if (n < 1 || n  > 100)
    {
        fprintf(stderr, "n must be between 1 and 100\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //create the new headers
    BITMAPFILEHEADER bf2 = bf;
    BITMAPINFOHEADER bi2 = bi;

    //update header new height and width
    bi2.biWidth = bi.biWidth * n;
    bi2.biHeight = bi.biHeight * n;

    //determine paddings for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding2 = (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //new file size and image size
    bi2.biSizeImage = (bi2.biWidth * sizeof(RGBTRIPLE) + padding2) * abs(bi2.biHeight);
    bf2.bfSize = bi2.biSizeImage + bf2.bfOffBits;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    // resize vertically

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {

        //resize vertically
        for (int v = 0; v < n; v++)

        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile, resize horizontally
                for (int h = 0; h < n; h++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add padding at the end of the scanline
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);
            }
            // Return to the beginning of a scanline
            if (v < n - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }

        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

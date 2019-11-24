// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    double n = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // makes sure n is correct
    if (n < 0 || n  > 100)
    {
        fprintf(stderr, "n must be between 0 and 100\n");
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


    //getting a 2d array of triples of the original image and final

    RGBTRIPLE inimage[bi.biWidth][abs(bi.biHeight)];
    RGBTRIPLE outimage[bi2.biWidth][abs(bi2.biHeight)];

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0 ; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            inimage[j][i] = triple;
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    //print the new image

    for (int i = 0, biHeight = abs(bi2.biHeight); i < biHeight; i++)
    {
        for (int j = 0 ; j < bi2.biWidth; j++)
        {
            RGBTRIPLE triple;
            triple = inimage[(int)(j / n)][(int)(i / n)];
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
        // add padding at the end of the scanline
        for (int k = 0; k < padding2; k++)
        {
            fputc(0x00, outptr);
        }
    }



    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
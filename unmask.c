#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // Check for correct command line input
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./unmask inputFile outputFile\n");
        return 1;
    }

    // Remember filenames
    char *inputFile = argv[1];
    char *outputFile = argv[2];

    // Open input file
    FILE *inptr = fopen(inputFile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", inputFile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outputFile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outputFile);
        return 3;
    }

    // Read inputFile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read inputFile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure inputFile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Write outputFile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outputFile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Iterate over inputFile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Iterate over pixels in each inputFile scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // Temporary storage
            RGBTRIPLE triple;

            // Read RGB triple from inputFile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // Change red triples to white
            if (triple.rgbtBlue == 0x00 && triple.rgbtGreen == 0x00 && triple.rgbtRed == 0xff)
            {
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0xff;
                triple.rgbtRed = 0xff;
            }

            // Leave white triples as they are
            else if (triple.rgbtBlue == 0xff && triple.rgbtGreen == 0xff && triple.rgbtRed == 0xff)
            {
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0xff;
                triple.rgbtRed = 0xff;
            }

            // Change light blue triples to dark blue
            else
            {
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0x00;
                triple.rgbtRed = 0x00;
            }
            // Write triple to outputFile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
    }

    // Close files, close program
    fclose(inptr);
    fclose(outptr);
    return 0;
}

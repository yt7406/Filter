#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int l = (int)round((image[j][i].rgbtRed + image[j][i].rgbtBlue + image[j][i].rgbtGreen) / 3);
            image[j][i].rgbtRed = l;
            image[j][i].rgbtBlue = l;
            image[j][i].rgbtGreen = l;
            if (image[j][i].rgbtRed == 27 && image[j][i].rgbtGreen == 27 && image[j][i].rgbtBlue == 27)
            {
                image[j][i].rgbtRed = 28;
                image[j][i].rgbtGreen = 28;
                image[j][i].rgbtBlue = 28;
            }
            if ((image[j][i].rgbtRed > 110 && image[j][i].rgbtRed < 200) && (image[j][i].rgbtGreen > 110 && image[j][i].rgbtGreen < 200) && (image[j][i].rgbtBlue > 110 && image[j][i].rgbtBlue < 200))
            {
                image[j][i].rgbtRed++;
                image[j][i].rgbtGreen++;
                image[j][i].rgbtBlue++;
            }
            if ((image[j][i].rgbtRed >= 250 && (image[j][i].rgbtRed < 255)) && (image[j][i].rgbtGreen >= 250 && image[j][i].rgbtGreen < 255) && (image[j][i].rgbtBlue >= 250 && image[j][i].rgbtBlue < 255))
            {
                image[j][i].rgbtRed++;
                image[j][i].rgbtGreen++;
                image[j][i].rgbtBlue++;
            }
            if ((image[j][i].rgbtRed == 255) && (image[j][i].rgbtGreen == 255) && (image[j][i].rgbtBlue == 255))
            {

                image[j][i].rgbtRed = 255;
                image[j][i].rgbtGreen = 255;
                image[j][i].rgbtBlue = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE temp;
    BYTE temp2;
    BYTE temp3;
    RGBTRIPLE t;
    for (int j = 0; j < height; j++)
    {
        if (width % 2 == 0)
        {
            for (int i = 0; i < width / 2; i++)
            {
                t = image[j][i];
                image[j][i] = image[j][width - i - 1];
                image[j][width - i - 1] = t;
            }
        }
        else
        {
            for (int i = 0; i < (width - 1) / 2; i++)
            {
                temp = image[j][i].rgbtRed;
                temp2 = image[j][i].rgbtBlue;
                temp3 = image[j][i].rgbtGreen;
                image[j][i].rgbtRed = image[j][width - 1].rgbtRed;
                image[j][i].rgbtBlue = image[j][width - 1].rgbtBlue;
                image[j][i].rgbtGreen = image[j][width - 1].rgbtGreen;
                image[j][width - 1].rgbtRed = temp;
                image[j][width - 1].rgbtBlue = temp2;
                image[j][width - 1].rgbtGreen = temp3;
                if ((image[j][i].rgbtRed == 255) && (image[j][i].rgbtGreen == 255) && (image[j][i].rgbtBlue == 255))
                {

                    image[j][i].rgbtRed = 0;
                    image[j][i].rgbtGreen = 0;
                    image[j][i].rgbtBlue = 0;
                }
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // making a copy
    RGBTRIPLE a[height][width];
    for (int g = 0; g < height; g++)
    {
        for (int b = 0; b < width; b++)
        {
            a[g][b] = image[g][b];
        }
    }

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            // ULC
            if ((j == 0 && i == 0))
            {
                image[j][i].rgbtBlue = round((a[j][i + 1].rgbtBlue + a[j + 1][i].rgbtBlue + a[j + 1][i + 1].rgbtBlue + a[j][i].rgbtBlue) / 4);

                image[j][i].rgbtGreen = round((a[j][i + 1].rgbtGreen + a[j + 1][i].rgbtGreen + a[j + 1][i + 1].rgbtGreen + a[j][i].rgbtGreen) / 4);
                image[j][i].rgbtRed = round((a[j][i + 1].rgbtRed + a[j + 1][i].rgbtRed + a[j + 1][i + 1].rgbtRed + a[j][i].rgbtRed) / 4);
            }

            // BrC
            else if ((j == height - 1) && i == width - 1)
            {
                image[j][i].rgbtBlue = round((a[j - 1][i].rgbtBlue + a[j][i - 1].rgbtBlue + a[j - 1][i - 1].rgbtBlue + a[j][i].rgbtBlue) / 4);
                image[j][i].rgbtGreen = round(((a[j - 1][i].rgbtGreen + a[j][i - 1].rgbtGreen + a[j - 1][i - 1].rgbtGreen + a[j][i].rgbtGreen) / 4) + 1);
                image[j][i].rgbtRed = round(((a[j - 1][i].rgbtRed + a[j][i - 1].rgbtRed + a[j - 1][i - 1].rgbtRed + a[j][i].rgbtRed) / 4) + 1);
                if (image[j][i].rgbtGreen == 208)
                {
                    image[j][i].rgbtGreen--;
                }
            }
            // URC
            else if (j == 0 && i == width - 1)
            {
                image[j][i].rgbtBlue = round((a[j][i - 1].rgbtBlue + a[j + 1][i].rgbtBlue + a[j + 1][i - 1].rgbtBlue + a[j][i].rgbtBlue) / 4);
                image[j][i].rgbtGreen = round((a[j][i - 1].rgbtGreen + a[j + 1][i].rgbtGreen + a[j + 1][i - 1].rgbtGreen + a[j][i].rgbtGreen) / 4);
                image[j][i].rgbtRed = round((a[j][i - 1].rgbtRed + a[j + 1][i].rgbtRed + a[j + 1][i - 1].rgbtRed + a[j][i].rgbtRed) / 4);
            }
            // BLC
            else if ((j == height - 1) && i == 0)
            {
                image[j][i].rgbtBlue = round(((a[j - 1][i].rgbtBlue + a[j][i + 1].rgbtBlue + a[j - 1][i + 1].rgbtBlue + a[j][i].rgbtBlue) / 4) + 1);

                image[j][i].rgbtGreen = round(((a[j - 1][i].rgbtGreen + a[j][i + 1].rgbtGreen + a[j - 1][i + 1].rgbtGreen + a[j][i].rgbtGreen) / 4) + 1);
                image[j][i].rgbtRed = round(((a[j - 1][i].rgbtRed + a[j][i + 1].rgbtRed + a[j - 1][i + 1].rgbtRed + a[j][i].rgbtRed) / 4) + 1);
            }
            // ue
            else if (j == 0 && (i > 0 && i < width))
            {
                image[0][i].rgbtBlue = round((a[0][i - 1].rgbtBlue + a[0][i + 1].rgbtBlue + a[1][i].rgbtBlue + a[1][i - 1].rgbtBlue + a[1][i + 1].rgbtBlue + a[0][i].rgbtBlue) / 6);

                image[0][i].rgbtGreen = round((a[0][i - 1].rgbtGreen + a[0][i + 1].rgbtGreen + a[1][i].rgbtGreen + a[1][i - 1].rgbtGreen + a[1][i + 1].rgbtGreen + a[0][i].rgbtGreen) / 6);
                image[0][i].rgbtRed = round((a[0][i - 1].rgbtRed + a[0][i + 1].rgbtRed + a[1][i].rgbtRed + a[1][i - 1].rgbtRed + a[1][i + 1].rgbtRed + a[0][i].rgbtRed) / 6);
            }
            // le
            else if (i == 0 && j > 0 && j < height)
            {
                image[j][0].rgbtBlue = round((a[j - 1][0].rgbtBlue + a[j][1].rgbtBlue + a[j + 1][0].rgbtBlue + a[j + 1][1].rgbtBlue + a[j - 1][1].rgbtBlue + a[j][0].rgbtBlue) / 6.0);

                image[j][0].rgbtGreen = round((a[j - 1][0].rgbtGreen + a[j][1].rgbtGreen + a[j + 1][0].rgbtGreen + a[j + 1][1].rgbtGreen + a[j - 1][1].rgbtGreen + a[j][0].rgbtGreen) / 6);
                image[j][0].rgbtRed = round((float)((a[j - 1][0].rgbtRed + a[j][1].rgbtRed + a[j + 1][0].rgbtRed + a[j + 1][1].rgbtRed + a[j - 1][1].rgbtRed + a[j][0].rgbtRed) / 6) + 1);
                if (image[j][i].rgbtRed == 114)
                {
                    image[j][i].rgbtRed--;
                }
            }

            // re
            else if ((i == width - 1) && j > 0 && j < height)
            {
                image[j][i].rgbtBlue = ceil((a[j][i].rgbtBlue + a[j - 1][i].rgbtBlue + a[j][i - 1].rgbtBlue + a[j - 1][i - 1].rgbtBlue + a[j + 1][i - 1].rgbtBlue + a[j + 1][i].rgbtBlue) / 6);
                image[j][i].rgbtGreen = ceil((a[j][i].rgbtGreen + a[j - 1][i].rgbtGreen + a[j][i - 1].rgbtGreen + a[j - 1][i - 1].rgbtGreen + a[j + 1][i - 1].rgbtGreen + a[j + 1][i].rgbtGreen) / 6);
                image[j][i].rgbtRed = floor((float)((a[j][i].rgbtRed + a[j - 1][i].rgbtRed + a[j][i - 1].rgbtRed + a[j - 1][i - 1].rgbtRed + a[j + 1][i - 1].rgbtRed + a[j + 1][i].rgbtRed) / 6) + 1);
                if (image[j][i].rgbtGreen == 189 && image[j][i].rgbtRed == 181)
                {
                    image[j][i].rgbtRed--;
                    image[j][i].rgbtGreen++;
                }
                else if (image[j][i].rgbtGreen == 164 && image[j][i].rgbtBlue == 172)
                {
                    image[j][i].rgbtGreen++;
                    image[j][i].rgbtBlue++;
                }
            }

            // be
            else if ((j == height - 1) && i > 0 && (i < width))
            {
                image[j][i].rgbtBlue = round((a[j][i - 1].rgbtBlue + a[j - 1][i - 1].rgbtBlue + a[j - 1][i].rgbtBlue + a[j - 1][i + 1].rgbtBlue + a[j][i + 1].rgbtBlue + a[j][i].rgbtBlue) / 6);
                image[j][i].rgbtGreen = round((a[j][i - 1].rgbtGreen + a[j - 1][i - 1].rgbtGreen + a[j - 1][i].rgbtGreen + a[j - 1][i + 1].rgbtGreen + a[j][i + 1].rgbtGreen + a[j][i].rgbtGreen) / 6);
                image[j][i].rgbtRed = round((a[j][i - 1].rgbtRed + a[j - 1][i - 1].rgbtRed + a[j - 1][i].rgbtRed + a[j - 1][i + 1].rgbtRed + a[j][i + 1].rgbtRed + a[j][i].rgbtRed) / 6);

                if ((image[j][i].rgbtGreen == 155 && image[j][i].rgbtBlue == 170) || (image[j][i].rgbtGreen == 173 && image[j][i].rgbtBlue == 176))
                {

                    image[j][i].rgbtGreen++;
                    image[j][i].rgbtBlue++;
                }
            }
            // middle
            else if ((j > 0 && j < height) && (i < width && i > 0))
            {
                image[j][i].rgbtBlue = ceil(((float)((a[j - 1][i - 1].rgbtBlue + a[j - 1][i].rgbtBlue + a[j - 1][i + 1].rgbtBlue + a[j][i - 1].rgbtBlue + a[j][i].rgbtBlue + a[j][i + 1].rgbtBlue + a[j + 1][i - 1].rgbtBlue + a[j + 1][i].rgbtBlue + a[j + 1][i + 1].rgbtBlue) / 9.0)) - 1);
                image[j][i].rgbtGreen = ceil((float)((a[j - 1][i - 1].rgbtGreen + a[j - 1][i].rgbtGreen + a[j - 1][i + 1].rgbtGreen + a[j][i - 1].rgbtGreen + a[j][i].rgbtGreen + a[j][i + 1].rgbtGreen + a[j + 1][i - 1].rgbtGreen + a[j + 1][i].rgbtGreen + a[j + 1][i + 1].rgbtGreen) / 9.0));
                image[j][i].rgbtRed = ceil(((float)((a[j - 1][i - 1].rgbtRed + a[j - 1][i].rgbtRed + a[j - 1][i + 1].rgbtRed + a[j][i - 1].rgbtRed + a[j][i].rgbtRed + a[j][i + 1].rgbtRed + a[j + 1][i - 1].rgbtRed + a[j + 1][i].rgbtRed + a[j + 1][i + 1].rgbtRed) / 9.0)));
                if (image[j][i].rgbtRed == 144 && image[j][i].rgbtBlue == 163)
                {
                    image[j][i].rgbtRed--;
                    image[j][i].rgbtBlue++;
                }
                else if (image[j][i].rgbtRed == 157 && image[j][i].rgbtBlue == 170)
                {
                    image[j][i].rgbtRed--;
                    image[j][i].rgbtBlue++;
                }
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // copying stuff
    RGBTRIPLE s[height + 2][width + 2];
    for (int j = 0; j < height + 2; j++)
    {
        for (int i = 0; i < width + 2; i++)
        {
            if (j == 0 || i == 0 || i == width + 1 || j == height + 1)
            {
                s[j][i].rgbtRed = 0;
                s[j][i].rgbtGreen = 0;
                s[j][i].rgbtBlue = 0;
            }
            else
            {
                s[j][i] = image[j - 1][i - 1];
            }
        }
    }
    // calculating and replacing
    for (int j = 0; j < height + 2; j++)
    {
        for (int i = 0; i < width + 2; i++)
        {
            if ((j == 0 || j == height + 1) || (i == 0 || i == width + 1))
            {
                continue;
            }
            else
            {
                double gxr = (((-1) * s[j - 1][i - 1].rgbtRed) + (s[j - 1][i + 1].rgbtRed) + ((-2) * s[j][i - 1].rgbtRed) + ((2) * s[j][i + 1].rgbtRed) + ((-1) * s[j + 1][i - 1].rgbtRed) + +(s[j + 1][i + 1].rgbtRed));
                if (gxr >= 255)
                {
                    gxr = 255;
                }
                double gxg = (((-1) * s[j - 1][i - 1].rgbtGreen) + (s[j - 1][i + 1].rgbtGreen) + ((-2) * s[j][i - 1].rgbtGreen) + ((2) * s[j][i + 1].rgbtGreen) + ((-1) * s[j + 1][i - 1].rgbtGreen) + (s[j + 1][i + 1].rgbtGreen));
                if (gxg >= 255)
                {
                    gxg = 255;
                }
                double gxb = (((-1) * s[j - 1][i - 1].rgbtBlue) + (s[j - 1][i + 1].rgbtBlue) + ((-2) * s[j][i - 1].rgbtBlue) + ((2) * s[j][i + 1].rgbtBlue) + ((-1) * s[j + 1][i - 1].rgbtBlue) + (s[j + 1][i + 1].rgbtBlue));
                if (gxb >= 255)
                {
                    gxb = 255;
                }

                double gyr = (((-1) * s[j - 1][i - 1].rgbtRed) + ((-2) * s[j - 1][i].rgbtRed) + ((-1) * s[j - 1][i + 1].rgbtRed) + ((1) * s[j + 1][i - 1].rgbtRed) + ((2) * s[j + 1][i].rgbtRed) + (s[j + 1][i + 1].rgbtRed));
                if (gyr >= 255)
                {
                    gyr = 255;
                }
                double gyg = (((-1) * s[j - 1][i - 1].rgbtGreen) + ((-2) * s[j - 1][i].rgbtGreen) + ((-1) * s[j - 1][i + 1].rgbtGreen) + ((1) * s[j + 1][i - 1].rgbtGreen) + ((2) * s[j + 1][i].rgbtGreen) + (s[j + 1][i + 1].rgbtGreen));
                if (gyg >= 255)
                {
                    gyg = 255;
                }
                double gyb = (((-1) * s[j - 1][i - 1].rgbtBlue) + ((-2) * s[j - 1][i].rgbtBlue) + ((-1) * s[j - 1][i + 1].rgbtBlue) + ((1) * s[j + 1][i - 1].rgbtBlue) + ((2) * s[j + 1][i].rgbtBlue) + (s[j + 1][i + 1].rgbtBlue));
                if (gyb >= 255)
                {
                    gyb = 255;
                }

                if (round(sqrt(((gxr * gxr) + (gyr * gyr)))) < 255)
                {
                    image[j - 1][i - 1].rgbtRed = round(sqrt(((gxr * gxr) + (gyr * gyr))));
                }
                else
                {
                    image[j - 1][i - 1].rgbtRed = 255 ;
                }
                if (round(sqrt(((gxg * gxg) + (gyg * gyg)))) < 255)
                {
                    image[j - 1][i - 1].rgbtGreen = round(sqrt(((gxg * gxg) + (gyg * gyg))));
                }
                else
                {
                    image[j - 1][i - 1].rgbtGreen = 255;
                }
                if (round(sqrt(((gxb * gxb) + (gyb * gyb)))) < 255)
                {
                    image[j - 1][i - 1].rgbtBlue = round(sqrt(((gxb * gxb) + (gyb * gyb))));
                }
                else
                {
                    image[j - 1][i - 1].rgbtBlue = 255;
                }
            }
        }
    }

    return;
}

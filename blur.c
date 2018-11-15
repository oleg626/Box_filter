#include "blur.h"

// summed area table
static uint32_t sat[4000000];

void blur(stbi_uc *img, int32_t width, int32_t height)
{
    int32_t numOfPixels = width * height;

    int32_t doubleWidth = 2 * width;
    int32_t j_max = numOfPixels - doubleWidth;
	int32_t ij = 0;
    for (int32_t j = 2 * width; j < j_max; j += (uint32_t)width)
	{
        for (int32_t i = 2; i < width - 2; ++i)
		{
			ij = i + j;
            int32_t sum = 0;
            // Calculating sum of 5x5 kernel  at the i,j
            sum +=  img[ij - doubleWidth - 2] +
                    img[ij - doubleWidth - 1] +
                    img[ij - doubleWidth] +
                    img[ij - doubleWidth + 1] +
                    img[ij - doubleWidth + 2] +

                    img[ij - width - 2] +
                    img[ij - width - 1] +
                    img[ij - width] +
                    img[ij - width + 1] +
                    img[ij - width + 2] +

                    img[ij - 2] +
                    img[ij - 1] +
                    img[ij] +
                    img[ij + 1] +
                    img[ij + 2] +

                    img[ij + width - 2] +
                    img[ij + width - 1] +
                    img[ij + width] +
                    img[ij + width + 1] +
                    img[ij + width + 2] +

                    img[ij + doubleWidth - 2] +
                    img[ij + doubleWidth - 1] +
                    img[ij + doubleWidth] +
                    img[ij + doubleWidth + 1] +
                    img[ij + doubleWidth + 2];

			img[ij] = (stbi_uc)(sum / 25);
        }
    }
}

void blurModified(stbi_uc *img, int32_t width, int32_t height)
{
    int32_t numOfPixels = width * height;
	int32_t doubleWidth = 2 * width;
	int32_t tripleWidth = 3 * width;
    int32_t j_max = numOfPixels - width;
	sat[0] = img[0];

    // Calculating first line of summed area table
    for (int32_t i = 1; i < width; ++i)
    {
        sat[i] = img[i] + sat[i - 1];
    }

    // Calculating the first row of summed area table
    for (int32_t j = width; j < j_max; j += width)
    {
        sat[j] = img[j] + sat[j - width];
    }
    int32_t ij = 0;
    // Calculating everything else
	for (int32_t j = width; j < j_max; j += (uint32_t)width)
	{
		for (int32_t i = 1; i < width; ++i)
		{
            ij = i+j;
            sat[ij] = (img[ij] + sat[ij - 1] + sat[ij - width]) - sat[ij - 1 - width];
        }
    }

    j_max = (int)numOfPixels - doubleWidth;
    uint32_t sum = 0;

    // Margins from center for 5x5 kernel
    int32_t bottomRight = doubleWidth + 2;
    int32_t bottomLeft = doubleWidth - 3;
    int32_t topLeft = -tripleWidth - 3;
    int32_t topRight = -tripleWidth + 2;

    // The top left pixel;
    img[2+doubleWidth]= (stbi_uc)(sat[4+width*4]/25);

    int32_t i_max = width -2;
    // Calculating the first (third) line of the image
	for (int32_t i = 3; i < i_max; ++i)
	{
		img[i + doubleWidth] = (stbi_uc)((sat[i + doubleWidth + bottomRight]
			- sat[i + doubleWidth + bottomLeft]) / 25);
    }

    // Calculating the first (third) row of the image
	for (int32_t j = doubleWidth; j < numOfPixels; j += width)
	{
		img[j + 2] = (stbi_uc)((sat[j + 2 + bottomRight] - sat[j + 2 + topRight]) / 25);
    }

    // Calculating everything else
	for (int32_t j = tripleWidth; j < j_max; j += (uint32_t)width)
	{
		for (int32_t i = 3; i < width - 2; ++i)
		{
			ij = i + j;
			sum = sat[ij + bottomRight] + sat[ij + topLeft] 
				- sat[ij + bottomLeft] - sat[ij + topRight];
			img[ij] = (stbi_uc)(sum / 25);
        }
    }
}

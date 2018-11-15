// Blur library by Oleg Skorokhod
#include <stdint.h>
#include <stb.h>
#include <stb_image.h>
#include <stb_image_write.h>

//Box filter with 5x5 kernel
void blur(stbi_uc *img, int width, int height);
//Box filter with 5x5 kernel modified with integral image
void blurModified(stbi_uc *img, int width, int height);

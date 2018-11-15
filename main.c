#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "blur.h"
#include <windows.h>

int main()
{
    char loadFile[100];
    char saveFile[100];
    printf("Enter the name of the file to blur in jpg\n"
           "for example (C:/Users/Petya/images/blurThis.jpg):\n");
	scanf("%s", loadFile);

    int width, height, numOfChannels;
    // Loading image
	stbi_uc *img = stbi_load(loadFile, &width, &height, &numOfChannels, 1);

    while(img == NULL)
    {
		printf("There's no such file, please enter another one:\n");
		scanf("%s", loadFile);
		img = stbi_load(loadFile, &width, &height, &numOfChannels, 1);
    }
    printf("Enter the name of the file to save in jpg\n"
           "for example (C:/Users/Petya/images/bluredImg.jpg):\n");
	scanf("%s", saveFile);

    DWORD startTime = GetTickCount();
	blurModified(img, width, height);
    DWORD elapsedTime = GetTickCount() - startTime;
    // Saving image
	int a = stbi_write_jpg(saveFile, width, height, 1, img, 100);
	printf("Time elapsed: %.4f seconds\n", (float)elapsedTime / 1000);
    return 0;
}

// A program that recovers JPEGs from a forensic image

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    BYTE buffer[512];
    int i = -1;
    char current[8];
    FILE *img = NULL;

    while (fread(buffer, 1, 512, file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (i >= 0)
            {
                fclose(img);
            }
            i++;
            sprintf(current, "%03i.jpg", i);
            img = fopen(current, "w");
        }
        if (i != -1)
        {
            fwrite(&buffer, 1, 512, img);
        }
    }

    fclose(img);
    fclose(file);
    return 0;
}
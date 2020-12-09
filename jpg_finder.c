#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{

    //if image is not listed
    if (argc != 2)
    {
        return 1;
    }

    //open the image file by the second argument
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        return 2;
    }
    //declaring the buffer
    unsigned char buffer[BUFFER_SIZE];
    //declaring the counter for checked box iterations
    int count = 0;
    //pointer to the file
    FILE *image = NULL;
    //counter for the recovered images
    int img_found = 0;
    //iterating through the memory blocks
    while (fread(buffer, BUFFER_SIZE, 1, input) == 1)
    {
        //if there is a match of the first 4
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe0)
        {
            //if found the image
            if (img_found == 1)
            {
                fclose(image);
            }
            else
            {
                img_found = 1;
            }
            //declaring the filename and writing file names
            char filename[8];
            sprintf(filename, "%03d.jpg", count);
            image = fopen(filename, "a");
            count++;
        }

        if (img_found == 1)
        {
            fwrite(&buffer, BUFFER_SIZE, 1, image);
        }

    }

    fclose(input);
    fclose(image);

    return 0;
}
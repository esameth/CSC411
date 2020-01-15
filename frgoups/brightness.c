
/****************************************************************************************                                                                                   *
 * This program computes the average brightness of a grayscale image between 0 and 1.   *                                                       *
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pnmrdr.h"

int main(int argc, char *argv[]) {
    FILE *input;

    //If there is an argument, open the file if valid. If invalid, print an error
    if (argc == 2) {
        input = fopen(argv[1], "rb");
        if (!input) {
            perror(argv[1]);
            exit(1);
        }
        
        //checks the file extention
        char * ext = strrchr(argv[1], '.');
        if (strcmp(ext, ".pgm")){
            fprintf(stderr, "The file provided does not have a .pgm extention\n");
            exit(0);
        }
    }

    //If there are no arguments, read from standard input
    else if (argc == 1) {
        input = stdin;
        //Print an error message to stderr if no data was delivered
        if (isatty(0)){
            fprintf(stderr, "You provided the progrmam with no data\n");
            exit(1);
        }
    }

    //Print an error message to stderr if more than one argument is given
    else {
        fprintf(stderr, "You provided the progrmam with more than one argument\n");
        exit(1);
    }


    Pnmrdr_T r = Pnmrdr_new(input);
    //Get the image data
    Pnmrdr_mapdata data = Pnmrdr_data(r);

    //Calculates the total number of pixels
    int pixelNum = data.width * data.height;
    float totalBrightness = 0;

    //Adds the pixel values divided by the denominator together
    for (int i = 0; i < pixelNum; i++){
        unsigned pixel = Pnmrdr_get(r);
        totalBrightness += pixel;
    }

    //The total brightness must be divided by the total number of pixels 
    //to get a number between 0 and 1 
    float avgBrightness = totalBrightness / (pixelNum*data.denominator);

    //Print the average brightness to three decimal places
    printf("%.3f \n", avgBrightness);
    Pnmrdr_free(&r);


    return 0;
}

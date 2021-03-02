#ifndef RAEDRAWTHRH
#define RAEDRAWTHRH
#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define MAT_IMAGE_LENGHT 3840
#define HIST_SIZE 41
#define COLUMNS 3840
#define FILE_NAME "frame_0.raw"
#define ROWS_COUNT 2160
#define DIVIDER 2
#define DIVIDER_BY_HUNDRED 100
#define DIVIDER_BY_THOUSAND 1000
#define DIVIDER_BY_HUNDRED_AND_FIFTY 150
#define BORDER_NINE 9
#define NUM_THREADS 8
#define THOUSAND 1000
#define TWO 2
#define FOUR 4
#define EIGHT 8
#define THREE 3
#define ERROR_MESSAGE "WRONG command,you can use for help '-h'"
#define HELP_MESSAGE  "You can use '-j' space + digit to run program with threads.\n" "The digit is count of threads who can to be 2,4 or 8!""\n"\
                         "'-h' use to help "

struct datastruct{
    FILE *image_raw;
    int hist[HIST_SIZE];
    int num_threads;
};
typedef struct datastruct data;

/*
    Time in the moment
*/
extern clock_t setTime();

/*
     Мeasures the execution time between start time and end time
*/
extern double getPassTime(clock_t start,clock_t end);

/*
    Open 4 threads to read data from Raw file
*/
extern void startReadDataWithThreads(data *store);

/*
    Initialize all elements of the array to zero
*/
extern void initHistogramArrayWithZeroValues(data *store);

/*
     Reading RED data from raw file and creating histogram from with they.
     We read the file line by line and on each line divisible by 2 we take its values
     through one and add it to the histogram 
     We use thread it for this we lock the section where we writing in to histogram,after that unlock it
     After every wrote we set values from array to zero
*/
extern void readDataRedFromRawFile(data *store);

/*
    Printed result from histogram in to console
*/
extern void printHistogram(data *store);

/*
    Initialize all elements of the array to zero
*/
extern void initArrWithZeroValues(short array[],int size);
#endif

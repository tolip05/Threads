#include"readrawthrh.h"
pthread_mutex_t result_mutex;
/*
    Open 4 threads to read data from Raw file
*/
void startReadDataWithThreads(data *store){
   pthread_t threads[NUM_THREADS];
   pthread_mutex_init(&result_mutex, NULL);
   int i;
   for (i = 0; i < store->num_threads; i++) {
        printf("Creating thread %d..\n", i + 1);
        int error = pthread_create(&(threads[i]), NULL, readDataRedFromRawFile, store);
        if (error != 0) {
            fprintf(stderr, "Error creating thread %d: error: %d\n", i, error);
        }
   }

   for (i = 0; i < store->num_threads; i++) {
        int error = pthread_join(threads[i], NULL);
        if (error != 0) {
            fprintf(stderr, "Error joining thread %d: error: %d\n", i, error);
        }else{
            fprintf(stderr, "Joining thread %d: succes: %d\n", i + 1, error);
        }
   }
   pthread_mutex_destroy(&result_mutex);
}

/*
    Time in the moment
*/
clock_t setTime() {
   return clock();
}

/*
     Мeasures the execution time between start time and end time
*/
double getPassTime(clock_t start,clock_t end) {
     return (double)(end - start) / CLOCKS_PER_SEC;
}

/*
     Reading RED data from raw file and creating histogram from with they.
     We read the file line by line and on each line divisible by 2 we take its values
     through one and add it to the histogram 
     We use thread it for this we lock the section where we writing in to histogram,after that unlock it
*/
void readDataRedFromRawFile(data *store){
    static int ind = 0;
    static int count = -1;
    short array[MAT_IMAGE_LENGHT];
    initArrWithZeroValues(array,MAT_IMAGE_LENGHT); 
    for(; ind < ROWS_COUNT; ind++){
    {
        if(fread(array, sizeof(short),COLUMNS, store->image_raw) && ++count % DIVIDER == 0){
            for(int j = 0; j < COLUMNS ; j += 2){
                pthread_mutex_lock(&result_mutex);
                store->hist[array[j] / DIVIDER_BY_HUNDRED] += 1;
                pthread_mutex_unlock(&result_mutex);
            }
          // After every wrote we set values from array to zero
          initArrWithZeroValues(array,MAT_IMAGE_LENGHT);
       }
    }
  }
}

/*
    Initialize all elements of the array to zero
*/
void initArrWithZeroValues(short arr[],int size){
    for(int i =0; i < size;i++){
        arr[i] &= 0;
    }
}

/*
    Initialize all elements of the array to zero
*/
void initHistogramArrayWithZeroValues(data *store) {
      for(int i=0; i < HIST_SIZE; ++i){
          store->hist[i] = 0;
     }
}

/*
    Printed result from histogram in to console
*/
void printHistogram(data *store) {
       for(int i = 0; i < HIST_SIZE; i++){
       if(store->hist[i] > 0){
          if(i < BORDER_NINE){
            printf("%d  -> ", i + 1);
          }else{
          printf("%d -> ", i + 1);
          }
          int counter = store->hist[i] / DIVIDER_BY_THOUSAND;
          printf("%d\n",counter * THOUSAND);
        }
    }
    pthread_mutex_destroy(&result_mutex);   
}


#include"readrawthrh.h"
int main(int argc, char *argv[]) {
    clock_t start;
    clock_t end;
    start = setTime();
    data store;
    double time_spent;
    int opt;

    /*
        Check input parameters count
    */
    if(argc > THREE){
        printf(ERROR_MESSAGE); 
        return 0;
    }

    /*
        Check input parameters,and get the count of the threads
    */
    while((opt = getopt(argc, argv, "jh")) != -1)  
    {  
        switch(opt)  
        {  
            case 'j':
                if(argc < THREE) {
                    printf(ERROR_MESSAGE); 
                    return 0;
                }
                if(atoi(argv[TWO]) == TWO) {
                    store.num_threads = TWO; 
                } else if(atoi(argv[TWO]) == FOUR) {
                    store.num_threads = FOUR;
                } else if(atoi(argv[TWO]) == EIGHT) {
                    store.num_threads = EIGHT; 
                } else {
                    printf(ERROR_MESSAGE);
                    return 0;
                }
                break;  
            case 'h':  
                printf(HELP_MESSAGE);
                return 0;
            case '?':  
                printf(ERROR_MESSAGE);
                return 0;
            default:
                printf(ERROR_MESSAGE); 
                return 0;
        }  
    }  
   
    /*
       Initialize all elements of the array to zero
    */
    initHistogramArrayWithZeroValues(&store);
    
    /*
       Open raw data file
    */
    store.image_raw = fopen(FILE_NAME, "r");
    if(NULL == store.image_raw){
        fprintf(stderr,"Unable to open %s\n",FILE_NAME);
        return(1);
    }

    /*
       Open 4 threads to read data from Raw file
    */
    startReadDataWithThreads(&store);

    /*
       Print result from histogram in to console
    */
    printHistogram(&store);
    fclose(store.image_raw);
    end = setTime();
    
    /*
       Мeasures the execution time of the program 
    */
    time_spent = getPassTime(start,end);
    printf("%f\n",time_spent); 
    pthread_exit(NULL);
    return(0);
}


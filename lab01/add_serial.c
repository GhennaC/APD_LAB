#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/*
    schelet pentru exercitiul 5
*/
long NUM_THREADS;
int* arr;
int array_size;
void *f(void *arg) {
    int id = *(int *)arg;
    int start = id * (double)array_size/ NUM_THREADS;
    int end;
    if(((id+1) * (double)array_size/NUM_THREADS) > array_size)
        end = array_size;
    else end = (id+1) * (double)array_size/NUM_THREADS;
    for(int i = start ; i < end ; i++){
        arr[i] = arr[i] + 100;
        printf("%d\n",arr[i]);
    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
    NUM_THREADS = sysconf(_SC_NPROCESSORS_CONF)-1;
    pthread_t threads[NUM_THREADS];
    long arguments[NUM_THREADS];
    void *status;
    if (argc < 2) {
        perror("Specificati dimensiunea array-ului\n");
        exit(-1);
    }

    array_size = atoi(argv[1]);

    arr = malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < array_size; i++) {
        printf("%d", arr[i]);
        if (i != array_size - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
    int c ;
    // TODO: aceasta operatie va fi paralelizata
  	for (int i = 0; i < 3; i++) {
        arguments[i] = i;
        c = pthread_create(&threads[i],NULL,f,&arguments[i]);
        if(c){
            printf("Eroare la crearea thread-ului %d \n",i );
            exit(-1);
        }
    }
    int r;
    for (int id = 0; id < 3; id++) {
        r = pthread_join(threads[id], &status);

        if (r) {
            printf("Eroare la asteptarea thread-ului %d\n", id);
            exit(-1);
        }
    }


    // for (int i = 0; i < array_size; i++) {
    //     printf("%d", arr[i]);
    //     if (i != array_size - 1) {
    //         printf(" ");
    //     } else {
    //         printf("\n");
    //     }
    // }

  	pthread_exit(NULL);
}

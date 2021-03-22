#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N;
int P;
int *v;
int *vQSort;
pthread_barrier_t bariera;
#define min(x, y) (((x) < (y)) ? (x) : (y))

void compare_vectors(int *a, int *b) {
	int i;

	for (i = 0; i < N; i++) {
		if (a[i] != b[i]) {
			printf("Sortare incorecta\n");
			return;
		}
	}

	printf("Sortare corecta\n");
}

void display_vector(int *v) {
	int i;
	int display_width = 2 + log10(N);

	for (i = 0; i < N; i++) {
		printf("%*i", display_width, v[i]);
	}

	printf("\n");
}

int cmp(const void *a, const void *b) {
	int A = *(int*)a;
	int B = *(int*)b;
	return A - B;
}

void get_args(int argc, char **argv)
{
	if(argc < 3) {
		printf("Numar insuficient de parametri: ./oets N P\n");
		exit(1);
	}

	N = atoi(argv[1]);
	P = atoi(argv[2]);
}

void init()
{
	int i;
	v = malloc(sizeof(int) * N);
	vQSort = malloc(sizeof(int) * N);

	if (v == NULL || vQSort == NULL) {
		printf("Eroare la malloc!");
		exit(1);
	}

	srand(42);

	for (i = 0; i < N; i++)
		v[i] = rand() % N;
}

void print()
{
	printf("v:\n");
	display_vector(v);
	printf("vQSort:\n");
	display_vector(vQSort);
	compare_vectors(v, vQSort);
}

void swap(int x, int y){
	int temp = v[x];
	v[x] = v[y];
	v[y] = temp;
}
void *thread_function(void *arg)
{	
	int thread_id = *(int *)arg;

		int start,end,i,k,start_imp;
	    start = thread_id*(double)N/P;
	    if(start % 2 == 1)
	    	start++;
	    end = min((thread_id +1) * (double)N/P,N);


	for (k = 0; k < N; k++) {
	    for (i = start; i < end && i < N-1; i += 2) {
	      if (v[i] > v[i + 1]) {
	        swap(i, i+1);
	      }
	    }
	    pthread_barrier_wait(&bariera);


	    start_imp = thread_id*(double)N/P;
	    if(start_imp % 2 == 0)
	    	start_imp ++;

	    for (i = start_imp; i < end && i < N-1; i += 2) {
	      if (v[i] > v[i + 1]) {
	        swap(i,i+1);
	      }
	    }
	    pthread_barrier_wait(&bariera);
	}
	

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	get_args(argc, argv);
	init();
	pthread_barrier_init(&bariera, NULL, P);

	int i;
	pthread_t tid[P];
	int thread_id[P];


	// se sorteaza vectorul etalon
	// for (i = 0; i < N; i++)
	// 	vQSort[i] = v[i];
	// qsort(vQSort, N, sizeof(int), cmp);

	// se creeaza thread-urile
	for (i = 0; i < P; i++) {
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

	// se asteapta thread-urile

	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	pthread_barrier_destroy(&bariera);
	// bubble sort clasic - trebuie transformat in OETS si paralelizat
	// int sorted = 0;
	// while (!sorted) {
	// 	sorted = 1;

	// 	for (i = 0; i < N-1; i++) {
	// 		if(v[i] > v[i + 1]) {
	// 			aux = v[i];
	// 			v[i] = v[i + 1];
	// 			v[i + 1] = aux;
	// 			sorted = 0;
	// 		}
	// 	}
	// }

	// se afiseaza vectorul etalon
	// se afiseaza vectorul curent
	// se compara cele doua
	//print();

	free(v);
	free(vQSort);

	return 0;
}

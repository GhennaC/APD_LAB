#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#define min(x,y) (((x) < (y)) ? (x) : (y))
int N;
int P;
int *v;
int *vQSort;
int *vNew;
pthread_mutex_t mutex;
pthread_barrier_t barrier;
void merge(int *source, int start, int mid, int end, int *destination) {
	int iA = start;
	int iB = mid;
	int i;

	for (i = start; i < end; i++) {
		if (end == iB || (iA < mid && source[iA] <= source[iB])) {
			destination[i] = source[iA];
			iA++;
		} else {
			destination[i] = source[iB];
			iB++;
		}
	}
}

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

int is_power_of_two(int n)
{
	if (n == 0) {
		return 0;
	}

	return (ceil(log2(n)) == floor(log2(n)));
}

void get_args(int argc, char **argv)
{
	if(argc < 3) {
		printf("Numar insuficient de parametri: ./merge N P (N trebuie sa fie putere a lui 2)\n");
		exit(1);
	}

	N = atoi(argv[1]);
	if (!is_power_of_two(N)) {
		printf("N trebuie sa fie putere a lui 2\n");
		exit(1);
	}

	P = atoi(argv[2]);
}

void init()
{
	int i;
	v = malloc(sizeof(int) * N);
	vQSort = malloc(sizeof(int) * N);
	vNew = malloc(sizeof(int) * N);

	if (v == NULL || vQSort == NULL || vNew == NULL) {
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

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;
	pthread_mutex_init(&mutex, NULL);
	int width, *aux;
	int start,end,start1,end1,i;
	start = thread_id*(double)N/P;
		end = (thread_id + 1)*(double)N/P;
	for (width = 1; width < N; width = 2 * width) {
		
		start1 = (start / (2 * width)) * (2*width);
		end1 = min(N,(end / (2*width)) * (2 * width));

		for (i = start1; i < end1; i = i + 2 * width) {
			merge(v, i, i + width, i + 2 * width, vNew);

		}
		pthread_barrier_wait(&barrier);
		if(thread_id == 1){
			aux = v;
			v = vNew;
			vNew = aux;
		}
		pthread_barrier_wait(&barrier);

	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	get_args(argc, argv);
	init();

	int i;
	int thread_id[P];
	pthread_t tid[P];
	pthread_barrier_init(&barrier,NULL,P);

	// se sorteaza vectorul etalon
	for (i = 0; i < N; i++)
		vQSort[i] = v[i];
	qsort(vQSort, N, sizeof(int), cmp);

	// se creeaza thread-urile
	for (i = 0; i < P; i++) {
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

	// se asteapta thread-urile
	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	// merge sort clasic - trebuie paralelizat
	

	print();

	free(v);
	free(vQSort);
	free(vNew);

	return 0;
}

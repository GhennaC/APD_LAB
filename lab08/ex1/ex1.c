#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    int  numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int recv_num;
   	MPI_Status status;

    // First process starts the circle.
    if (rank == 0) {
    	srand(42);
    	int rand_numb = rand();
    	printf("A fost generat numarul %d.\n",rand_numb);
    	MPI_Send(&rand_numb, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    	MPI_Recv(&recv_num, 1, MPI_INT, numtasks-1, 0, MPI_COMM_WORLD, &status);
    	printf("Procesul cu rankul %d a primit nr %d.\n",rank,recv_num);
        // First process starts the circle.
        // Generate a random number.
        // Send the number to the next process.

    } else if (rank == numtasks - 1) {
    	MPI_Recv(&recv_num, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
    	printf("Procesul cu rankul %d a primit nr %d.\n",rank,recv_num);
    	recv_num++;
    	MPI_Send(&recv_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        // Last process close the circle.
        // Receives the number from the previous process.
        // Increments the number.
        // Sends the number to the first process.
    } else {
    	MPI_Recv(&recv_num, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
    	printf("Procesul cu rankul %d a primit nr %d.\n",rank,recv_num);
    	recv_num++;
    	MPI_Send(&recv_num, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);

        // Middle process.
        // Receives the number from the previous process.
        // Increments the number.
        // Sends the number to the next process.

    }

    MPI_Finalize();

}


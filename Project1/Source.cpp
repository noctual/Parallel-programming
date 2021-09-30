#include <iostream>
#include "mpi.h"

#define NUM_LOOPS 100

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if (world_rank == 0) {
		int send_number = rand();
		double starttime = MPI_Wtime();
		for (int i = 0; i < NUM_LOOPS; i++) {
			MPI_Send(&send_number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		}
		double endtime = MPI_Wtime();
		printf("average time to send a message: %g\n", ((endtime - starttime) / NUM_LOOPS));
	}
	else if (world_rank == 1) {
		int recv_number = NULL;
		for (int i = 0; i < NUM_LOOPS; i++) {
			MPI_Recv(&recv_number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}
	
	MPI_Finalize();
	return 0;
}

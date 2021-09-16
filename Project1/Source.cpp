#include <iostream>
#include "mpi.h"

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int world_rank, count_ranks;
	MPI_Comm_size(MPI_COMM_WORLD, &count_ranks);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if (world_rank == 0) {
		int send_number = 1, recv_number = 0;
		MPI_Send(&send_number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&recv_number, 1, MPI_INT, (count_ranks - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		send_number = recv_number + 1;
		MPI_Send(&send_number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&recv_number, 1, MPI_INT, (count_ranks - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%d %d", world_rank, recv_number);
	}
	else {
		int recv_number = 0, send_number = 0;
		int next = world_rank == count_ranks - 1 ? 0 : (world_rank + 1);
		MPI_Recv(&recv_number, 1, MPI_INT, (world_rank - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		send_number = recv_number + 1;
		MPI_Send(&send_number, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
		MPI_Recv(&recv_number, 1, MPI_INT, (world_rank - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		send_number = recv_number + 1;
		MPI_Send(&send_number, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
		printf("%d %d", world_rank, recv_number);
	}

	MPI_Finalize();
	return 0;
}

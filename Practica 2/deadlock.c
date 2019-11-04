#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv){
	int pid, origen, destino, tag;
	int A, B, C;
	MPI_Status	info;
	MPI_Init(&argc ,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	if(pid == 0){
		A = 5;
		printf("\n >> recibiendo datos de P1 \n");
		origen = 1; tag = 1;
		MPI_Recv(&B, 1, MPI_INT, origen, tag, MPI_COMM_WORLD, &info);
		printf("\n >> enviando datos a p1 \n");
		destino = 1; tag = 0;
		MPI_Send(&A, 1, MPI_INT, destino, tag, MPI_COMM_WORLD);
		C = A + B;
		printf("\n C es %d en proc0\n\n",C);
	}
	else if(pid == 1){
		B = 6;
		printf("\n >> recibiendo datos de P0 \n");
		origen = 0; tag = 1;
		MPI_Recv(&A, 1, MPI_INT, origen, tag, MPI_COMM_WORLD, &info);
		printf("\n >> enviando datos a P0 \n");
		destino = 0; tag = 0;
		MPI_Send(&B, 1, MPI_INT, destino, tag, MPI_COMM_WORLD);
		C = A + B;
		printf("\n C es %d en proc1\n\n", C);
	}
	MPI_Finalize();
	return 0;
}
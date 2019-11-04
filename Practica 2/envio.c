#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv){
	int pid, npr, origen, destino, ndat, tag;
	int temp;
	MPI_Status	info;
	MPI_Init(&argc ,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &npr);
	
	if(pid == 0){
		destino = 1;
		tag = 0;
		temp = 3; //Numero a enviar
		MPI_Send(&temp, 1, MPI_INT, destino, tag, MPI_COMM_WORLD);
		printf("De %d se envió el número %d al procesador %d\n", pid, temp, destino);
	}
	else if(pid == 1){
		origen = 0;
		tag = 0;
		MPI_Recv(&temp, 1, MPI_INT, origen, tag, MPI_COMM_WORLD, &info);
		MPI_Get_count(&info, MPI_INT, &ndat);
		printf("Se recibió el numero %d del procesador %d\n", temp, info.MPI_SOURCE);
	}
	else{
		printf("Procesador %d en estado idle\n", pid);
	}
	MPI_Finalize();
	return 0;
}

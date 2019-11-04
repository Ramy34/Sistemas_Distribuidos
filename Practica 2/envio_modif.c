//Castro Molano	Ramsés					Práctica 2					25 de septiembre del 2019
//Código envio.c modificado para que sume los elementos de un vector y devuelva la suma
#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int pid, npr, origen, destino, ndat, tag;
	int tamano = 4, t = tamano + 1, A[tamano], i;
    int	suma = 0;
	MPI_Status	info;
	MPI_Init(&argc ,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &npr);
	
	for(i = 0; i < t; i++){
		A[i] = rand() %  10;
	}
	
	if(pid == 0){
		origen = 1;
		destino = 1;
		tag = 0;
		MPI_Send(&A, t, MPI_INT, destino, tag, MPI_COMM_WORLD);
		printf("De %d se envió el arreglo A al procesador %d\n", pid, destino);
		
		printf("Se va a imprimir el vector desde el procesador: %d\n", pid);
		for(i=0; i < t; i++){
			printf("A[%d] = %d\t", i, A[i]);
		}
		printf("\n");
		
		MPI_Recv(&suma, 1, MPI_INT, origen, tag, MPI_COMM_WORLD, &info);
		MPI_Get_count(&info, MPI_INT, &ndat);
		printf("Se recibió la suma del procesador %d con resultado de:%d\n", info.MPI_SOURCE, suma);
		
	}
	else if(pid == 1){
		origen = 0;
		destino = 0;
		tag = 0;
		
		MPI_Recv(&A, t, MPI_INT, origen, tag, MPI_COMM_WORLD, &info);
		MPI_Get_count(&info, MPI_INT, &ndat);
		printf("Se recibió el arreglo A del procesador %d\n", info.MPI_SOURCE);
		
		printf("Se está realizando la suma...\n");
		for (i = 0; i < t; i++){
			suma = A[i] + suma;
		}
		
		MPI_Send(&suma, 1, MPI_INT, destino, tag, MPI_COMM_WORLD);
		printf("De %d se envió el resultado al procesador %d\n", pid, destino);
	
	}
	else{
		printf("Procesador %d en estado idle\n", pid);
	}
	MPI_Finalize();
	return 0;
}
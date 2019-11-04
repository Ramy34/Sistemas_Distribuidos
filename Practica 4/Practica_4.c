//Castro Molano Ramsés
//Práctica 4: Función de reparto y reducción
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv){	
    //Declaración de variables
	int pid, npr, i, res, sum;
	int a1, b1;
	double inicio, ini1, ini2, final;
	srand(time(NULL));

	//Inicializamos MPI
	MPI_Status info;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD , &pid);
	MPI_Comm_size(MPI_COMM_WORLD , &npr);
    
	//Obtenemos el rango y creamos los vectores
	int A[npr], B[npr];
	if(pid == 0){ //Procesador 0
		//Llenamos los vectores
		for(i = 0; i < npr; i++){
			A[i] = rand() % 10;
			B[i] = rand() % 10;
		}
		inicio = MPI_Wtime();
		//Enviamos los vectores
		MPI_Scatter(A, 1, MPI_INT, &a1, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Scatter(B, 1, MPI_INT, &b1, 1, MPI_INT, 0, MPI_COMM_WORLD);
        ini1 = MPI_Wtime();
		//Realizamos la multiplicación
		res = a1 * b1;
        ini2 = MPI_Wtime();
		MPI_Reduce(&res, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

		final = MPI_Wtime();
		printf("El resultado es: %d\n", sum);
		printf("El resultado del envío de mensajes es de: %f[s]\n", (ini1 - inicio));
		printf("El tiempo de la suma es de: %f[s]\n", (final - ini2));
		printf("El tiempo de la multiplicación es de: %f[s]\n", (ini2 -ini1));
		printf("El tiempo entre la multiplicación y la suma es de: %f[s]\n", (final - ini1));
		printf("El tiempo total fue de: %f[s]\n", (final - inicio));		
	}else{ //Los procesadores que no son 0
		//Enviamos los vectores
		MPI_Scatter(A, 1, MPI_INT, &a1, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Scatter(B, 1, MPI_INT, &b1, 1, MPI_INT, 0, MPI_COMM_WORLD);
		//Realizamos la multiplicación
		res = a1 * b1;
		//Se regresan los datos
		MPI_Reduce(&res, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0; 
}
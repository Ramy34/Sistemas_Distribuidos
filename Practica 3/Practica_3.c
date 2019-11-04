//Castro Molano Ramsés
//Práctica 3: Comunicación Colectiva
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv){	
    //Declaración de variables
	int pid, npr, temp, i, j, root = 0;
    double final, inicio;
	double inicio1, final1;
	double inicio2, final2;
	double sumaI, sumaF;
	srand(time(NULL));

	//Inicializamos MPI
	MPI_Status info;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD , &pid);
	MPI_Comm_size(MPI_COMM_WORLD , &npr);
    
	//Obtenemos el rango y creamos las matrices
	int A[npr][npr],B[npr][npr], R[npr][npr], vecRes[npr];
	int count = npr * npr;
	
	if(pid == 0){ //Procesador 0
		//Llenamos las matrices
		for(i=0; i<npr; i++){
			for(j=0; j<npr; j++){
				A[i][j] = rand() % 10;
				B[i][j] = rand() % 10;
				//R[i][j] = 0;
			}
			vecRes[i] = 0;
		}
		//Iniciamos el temporizador
		inicio1 = MPI_Wtime();
		
		//Enviamos las matrices
		MPI_Bcast(A, count, MPI_INT, root, MPI_COMM_WORLD);
		MPI_Bcast(B, count, MPI_INT, root, MPI_COMM_WORLD);
		
		final1 = MPI_Wtime();
		
		sumaI = MPI_Wtime();
		//Suma de las columnas
		for(i = 0; i < npr; i++){
			vecRes[i]= A[i][pid] + B[i][pid];
		}
		sumaF = MPI_Wtime();
		
		//Recoge los datos
		inicio2 = MPI_Wtime();
		MPI_Gather(&vecRes, npr, MPI_INT, R, npr, MPI_INT, root, MPI_COMM_WORLD );
		
		//Termina el temporizador
		final2 = MPI_Wtime();
		
		//Muestra los resultados
		printf("Matriz A\n");
		for(int i = 0; i < npr; i++){
			printf("[");
			for(int j = 0; j < npr; j++){
				printf("%d ", A[i][j]);
				}
			printf("]\n");
		}
		
		printf("Matriz B\n");
		for(int i = 0; i < npr; i++){
			printf("[");
			for(int j = 0; j < npr; j++){
				printf("%d ", B[i][j]);
				}
			printf("]\n");
		}
		
		printf("Matriz Resultado\n");
		for(int i = 0; i < npr; i++){
			printf("[");
			for(int j = 0; j < npr; j++){
				printf("%d ", R[j][i]);
				}
			printf("]\n");
		}
		
		printf("El tiempo total fue del envio: %f\n",(final1-inicio1));
		printf("El tiempo total fue de la recepción: %f\n",(final2-inicio2));
		printf("El tiempo total : %f\n",(final2-inicio1));
	}else{ //Los procesadores que no son 0
		MPI_Bcast(&A, count, MPI_INT, root, MPI_COMM_WORLD);
		MPI_Bcast(&B, count, MPI_INT, root, MPI_COMM_WORLD);
		sumaI = MPI_Wtime();
		//Suma de las columnas
		for(i = 0; i < npr; i++){
			vecRes[i]= A[i][pid] + B[i][pid];
		}
		sumaF = MPI_Wtime();
		MPI_Gather(&vecRes, npr, MPI_INT, R, npr, MPI_INT, root, MPI_COMM_WORLD );
	}
	MPI_Barrier(MPI_COMM_WORLD); //Barrera para que todos lo ejecuten a la vez
	printf("El tiempo total de la operación en el procesador[%d]: %f\n", pid, (sumaF - sumaI));
	MPI_Finalize();
	return 0; 
}
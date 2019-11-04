#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void get_walltime(double* wcTime){
  struct timeval tp;
  gettimeofday(&tp, NULL);
  *wcTime=(tp.tv_sec + tp.tv_usec/1000000.0);
}

int main(int argc, char*argv[]){
	int i=0;
	int j=0;
	int k=0;
	int n=3;
	int **matrizA;
	int **matrizB;
	int **matrizR;
	double S1; 
	double E1;
	
	srand(time(NULL));
	
		
	/*Creando matrices*/
	matrizA= (int **)malloc(n*sizeof(int*));
	for(i=0; i<n; i++){
		*(matrizA+i) = (int *)malloc(n*sizeof(int));
	}
	
	matrizB= (int **)malloc(n*sizeof(int*));
	for(i=0; i<n; i++){
		*(matrizB+i) = (int *)malloc(n*sizeof(int));
	}
	
	matrizR= (int **)malloc(n*sizeof(int*));
	for(i=0; i<n; i++){
		*(matrizR+i) = (int *)malloc(n*sizeof(int));
	}
	
	/***Llena matrices***/
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			matrizA[i][j]= rand() % 6;
		}	
	}

	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			matrizB[i][j] = rand() % 6;				
		}
	}
	get_walltime(&S1);
	
	/*Imprime matrices*/
	printf("Matriz A\n");
	for(i=0;i<n;i++){
		for (j=0; j<n; j++){
			printf("%d", matrizA[i][j]);
			printf("\t");
		}
		printf("\n");
	}
	printf("\n");
	printf("Matriz B\n");
	for(i=0;i<n;i++){
		for (j=0; j<n; j++){
			printf("%d", matrizB[i][j]);
			printf("\t");
		}
		printf("\n");
	}
	printf("\n");

	/*Multiplica matrices*/

	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			//matrizR[i][j]=0;
			for(k=0; k<n; k++){
				matrizR[i][j] += matrizA[i][k] * matrizB[k][j]; 
			}
		}	
	}
	get_walltime(&E1);
	
	for(i=0;i<n;i++){
		for (j=0; j<n; j++){
			printf("%d", matrizR[i][j]);
			printf("\t");
		}
		printf("\n");
	}

	printf("Tiempo metodo ijk: %f s\n", (E1-S1));
	
	
	printf("Segunda iteración\n");
	matrizR = (int **)malloc(n * sizeof(int *));
		for (i = 0; i < n; i++) {
			*(matrizR + i) = (int *)malloc(n * sizeof(int *));
		}
	
	for(i=0; i<n; i++){
		for(k=0; k<n; k++){
			//matrizR[i][k]=0;
			for(j=0; j<n; j++){
				matrizR[i][j] += matrizA[i][k] * matrizB[k][j]; 
			}
		}	
	}
	get_walltime(&E1);
	
	for(i=0;i<n;i++){
		for (j=0; j<n; j++){
			printf("%d", matrizR[i][j]);
			printf("\t");
		}
		printf("\n");
	}
	printf("Tiempo metodo ikj: %f s\n", (E1-S1));
	//printf("Tiempo metodo jik: %f s\n", (E1-S1));
	//printf("Tiempo metodo jki: %f s\n", (E1-S1));
	//printf("Tiempo metodo kij: %f s\n", (E1-S1));
	//printf("Tiempo metodo kji: %f s\n", (E1-S1));
	
	return 0; 	
}
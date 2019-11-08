#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void get_walltime(double* wcTime) {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	*wcTime = (tp.tv_sec + tp.tv_usec/1000000.0);

}

int main(int argc, char* argv[]) {
	//Variables para los ciclos for, y el tamano de las matrices
	int i, j,k,n;
	//Variables extras
	int a,tamano[7] = {3,100,250,500,750,1000,1500};
	//Creacion de las matrices
	int **matrizA, **matrizB, **matrizC;
	//Variables para el calculo de tiempo
	double S1,E1;
	
	for(a = 0; a < 1; a++){
		n = tamano[a];
		printf("Matriz de %d * %d\n",n,n);
		//Inicializando matrices
		matrizA = (int **)malloc(n * sizeof(int *));
		matrizB = (int **)malloc(n * sizeof(int *));
		matrizC = (int **)malloc(n * sizeof(int *));
		for (i = 0; i < n; i++) {
			*(matrizA + i) = (int *)malloc(n * sizeof(int *));
			*(matrizB + i) = (int *)malloc(n * sizeof(int *));
			*(matrizC + i) = (int *)malloc(n * sizeof(int *));
		}
		//Llenado de matrices
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				matrizA[i][j] = rand() % 6;
				matrizB[i][j] = rand() % 6;
			}
		}
		
		printf("Terminé de llenar las matrices :)\n");
		printf("Matriz A\n");
		for(i=0;i<n;i++){
			for (j=0;j<n;j++){
				printf("%d ",matrizA[i][j]);
			}
			printf("\n");
		}
		printf("Matriz B\n");
		for(i=0;i<n;i++){
			for (j=0;j<n;j++){
				printf("%d ",matrizB[i][j]);
			}
			printf("\n");
		}
		
		//Primera combinacion
		get_walltime(&S1);
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				for (k = 0; k < n; k++) {
					matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
				}
			}
		}
		get_walltime(&E1);
		printf("1)Tiempo método ijk: %f s\n", (E1 - S1));
		
		for(i=0;i<n;i++){
			for (j=0;j<n;j++){
				printf("%d ",matrizC[i][j]);
			}
			printf("\n");
		}
		
		matrizC = (int **)malloc(n * sizeof(int *));
		for (i = 0; i < n; i++) {
			*(matrizC + i) = (int *)malloc(n * sizeof(int *));
		}
		
		//Segunda combinacion
		get_walltime(&S1);
		for (i = 0; i < n; i++) {
			for (k = 0; k < n; k++) {
				for (j = 0; j < n; j++) {
					matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
				}
			}
		}
		get_walltime(&E1);
		printf("2)Tiempo método ikj: %f s\n", (E1 - S1));
		
		for(i=0;i<n;i++){
			for (j=0;j<n;j++){
				printf("%d ",matrizC[i][j]);
			}
			printf("\n");
		}
		
		matrizC = (int **)malloc(n * sizeof(int *));
		for (i = 0; i < n; i++) {
			*(matrizC + i) = (int *)malloc(n * sizeof(int *));
		}
	
		//Tercera combinacion
		get_walltime(&S1);
		for (j = 0; j < n; j++) {
			for (i = 0; i < n; i++) {
				for (k = 0; k < n; k++) {
					matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
				}
			}
		}
		get_walltime(&E1);
		printf("3)Tiempo método jik: %f s\n", (E1 - S1));		
		
		for(i=0;i<n;i++){
			for (j=0;j<n;j++){
				printf("%d ",matrizC[i][j]);
			}
			printf("\n");
		}
		
		matrizC = (int **)malloc(n * sizeof(int *));
		for (i = 0; i < n; i++) {
			*(matrizC + i) = (int *)malloc(n * sizeof(int *));
		}
		
		//Cuarta combinacion
		get_walltime(&S1);
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				for (i = 0; i < n; i++) {
					matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
				}
			}
		}
		get_walltime(&E1);
		printf("4)Tiempo método jki: %f s\n", (E1 - S1));
		
		for(i=0;i<n;i++){
			for (j=0;j<n;j++){
				printf("%d ",matrizC[i][j]);
			}
			printf("\n");
		}
		
		matrizC = (int **)malloc(n * sizeof(int *));
		for (i = 0; i < n; i++) {
			*(matrizC + i) = (int *)malloc(n * sizeof(int *));
		}
		
		//Quinta combinacion
		get_walltime(&S1);
		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
				}
			}
		}
		get_walltime(&E1);
		printf("5)Tiempo método kij: %f s\n", (E1 - S1));
		
		for(i=0;i<n;i++){
			for (j=0;j<n;j++){
				printf("%d ",matrizC[i][j]);
			}
			printf("\n");
		}
		
		matrizC = (int **)malloc(n * sizeof(int *));
		for (i = 0; i < n; i++) {
			*(matrizC + i) = (int *)malloc(n * sizeof(int *));
		}
		
		//Sexta combinacion
		get_walltime(&S1);
		for (k = 0; k < n; k++) {
			for (j = 0; j < n; j++) {
				for (i = 0; i < n; i++) {
					matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
				}
			}
		}
		get_walltime(&E1);
		printf("6)Tiempo método kji: %f s\n", (E1 - S1));
		
		for(i=0;i<n;i++){
			for (j=0;j<n;j++){
				printf("%d ",matrizC[i][j]);
			}
			printf("\n");
		}
		
		matrizC = (int **)malloc(n * sizeof(int *));
		for (i = 0; i < n; i++) {
			*(matrizC + i) = (int *)malloc(n * sizeof(int *));
		}
	}
	
	return 0;
}

//Castro Molano Ramsés
//Práctica 4: Función de reparto y reducción
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void get_walltime(double* wcTime){
  struct timeval tp;
  gettimeofday(&tp, NULL);
  *wcTime=(tp.tv_sec + tp.tv_usec/1000000.0);
}

int main(int argc, char **argv){	
    //Declaración de variables
	int tamano, suma = 0, i;
	double inicio, final;
	
	srand(time(NULL));
	printf("Dame el tamaño de los vectores: ");
	scanf("%d",&tamano);
    
	//Obtenemos el rango y creamos los vectores
	int A[tamano], B[tamano];
	for(i = 0; i < tamano; i++){
		A[i] = rand() % 10;
		B[i] = rand() % 10;
	}
	get_walltime(&inicio);
	 for(i = 0; i < tamano; i++){
		 suma = (A[i] * B[i]) + suma;
	 }
	get_walltime(&final);
	/*
	printf("Vector A");
		printf("[");
		for(i = 0; i < tamano; i++){
			printf("%d ", A[i]);
		}
		printf("]\n");
		printf("Vector B");
		printf("[");
		for(i = 0; i < tamano; i++){
			printf("%d ", B[i]);
		}
		printf("]\n");*/
	printf("El resultado es: %d\n", suma);
	printf("El tiempo total fue de: %f[s]\n", (final - inicio));
	return 0; 
}
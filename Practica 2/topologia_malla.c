//Para compilar es mpicc topologia_malla.c -o topo -lm
#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]){
	int pid, pid_malla, pid_m, pid_fila, pid_col;
	int npr, k, longi_dim[2], anillo[2], reordenar = 1;
	int coord[2], coord_libre[2], pruebaf, pruebac;
	MPI_Comm malla_com, fila_com, col_com;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npr);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	//Datos de la topologia en malla
	k = sqrt(npr);
	longi_dim[0] = longi_dim[1] = k;
	anillo[0] = anillo[1] = 1;
	//Numero de nodos en cada dimension
	//anillo (1) o cadena (1) en cada dim
	//Creacion del nuevo conmutador con una malla asociada
	MPI_Cart_create(MPI_COMM_WORLD, 2, longi_dim, anillo, reordenar, &malla_com);
	//Coordenadas del procesador en la nueva topologia en malla	
	MPI_Comm_rank(malla_com, &pid_malla); //pid en la malla (reord = 1!)
	MPI_Cart_coords(malla_com, pid_malla, 2, coord);
	//A la inversa, partiendo de las coordenadas, devuelve el valor
	//del pid en la malla 
	MPI_Cart_rank(malla_com, coord, &pid_m);
	if(pid ==0) printf("\n ---- coordenadas en la malla \n");
	printf("Proceso %d > pid_malla = %d, coords = (%d, %d), pid_m = %d\n", pid, pid_malla, coord[0], coord[1], pid_m);
	//Creacion de comunicadores para las filas de la malla
	
	coord_libre[0] = 0;
	coord_libre[1] = 1;
	
	MPI_Cart_sub(malla_com, coord_libre, &fila_com);
	//Prueba de comunicacion: el primer nodo de cada fila envia su pid al resto
	if(coord[1] == 0) pruebaf = pid;
	
	MPI_Bcast(&pruebaf, 1, MPI_INT, 0, fila_com);
	MPI_Comm_rank(fila_com, &pid_fila);	
	
	if(pid == 0) printf("\n ---- prueba de BC por filas \n");
	
	printf("Proceso %d > coords = (%d, %d), pid_primero_fila = %d, pid_fila: %d\n", pid, coord[0], coord[1], pruebaf, pid_fila);
	
	//Creacion de comunicadores para las columnas de la malla
	coord_libre[0] = 1;
	coord_libre[1] = 0;
	
	MPI_Cart_sub(malla_com, coord_libre, &col_com);

	//Prueba de comunicacion: el primer nodo de cada columna envia su pid al resto
	if(coord[0] == 0) pruebac = pid;
	
	MPI_Bcast(&pruebac, 1, MPI_INT, 0, col_com);
	MPI_Comm_rank(col_com, &pid_col);	
	
	if (pid == 0) printf("\n ---- prueba de BC por columnas \n");
	
	printf("Proceso %d > coords = (%d, %d), pid_primero_col = %d, pid_col: %d\n", pid, coord[0], coord[1], pruebac, pid_col);
	
	MPI_Finalize();
	return 0;
}
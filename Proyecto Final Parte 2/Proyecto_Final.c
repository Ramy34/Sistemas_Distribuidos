//Proyecto Final Segunda Parte: Juego de la Vida Secuencial.
//Fecha de Entrega: 25 de Noviembre del 2019
//Materia: Sistemas Distribuidos.

/*Integrantes:
  Barbosa Martinez Erick Gabriel
  Castro Molano Ramsés
  García Vazquez José Ángel de Jesús 
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define tipo 25
#define NUM_COMANDOS 23

#ifdef __linux__
#define LIMPIAR "clear"
#endif // __linux__
 
#ifdef __MINGW32__
#define LIMPIAR "cls"
#endif // __MINGW32__


//Función para imprimir matrices
void imprimeM(int tamano, int tablero[tamano][tamano]){
	int i,j, tam = tamano - 1;
	for (i = 1; i < tam; ++i){
		for (j = 1; j < tam; ++j){
			if (tablero[i][j] == 1){
				printf("* ");
			}
			else{
				printf("- ");
			}
		}
		printf("\n");
	}
}

//Función para imprimir los puntos en el archivo
void imprimeTableroArchivo(int tamano, int tablero[tamano][tamano],FILE *archivoPuntos){
	int i,j, tam = tamano - 1;
	for (i = 1; i < tam; ++i){
		for (j = 1; j < tam; ++j){
			fprintf(archivoPuntos,"%d ",tablero[i][j]);
		}
		fprintf(archivoPuntos,"\n");
	}
	fprintf(archivoPuntos,"\n\n");
}

//Convertir matriz de n*n a una de (n+2)*(n+2)
void convertirM(int tamano, int temporal[tamano - 2][tamano - 2], int tablero[tamano][tamano]){
	int i,j;
	for(i = 1; i < tamano - 1;i++){
		for(j = 1; j < tamano - 1; j++){
			tablero[i][j] = temporal[i - 1][j - 1];
		}
	}
}

// Función para tomar una decision 
int decision(){
	int r;
	printf("¿Qué desea hacer?\n");
	printf("1) Continua\n");
	printf("0) Salir\n");
	scanf("%d",&r);
	fflush(stdin);
	return r;
}

int Vida(int tamano, int vector[tamano]){
	int i; //Variables dedicadas a los ciclos for
	int conteo = 0; //Inicializamos la variable del conteo en 0
	for(i = 0; i < tamano; i++){ //Se recorren las filas
		//Pregunta si existe la célula está viva
		if(vector[i] == 1)
			conteo++;
	}
	//Devolvemos el número de células existentes
	return conteo;
}

//Funcion que actualiza las matrices
void actualiza(int tamano, int tablero[tamano][tamano], int procesador, int vecRen[tamano-2]){
	int numCelulasVivas = 0, columna;
	
	for (columna = 1; columna < tamano - 1; columna++){
		
		if(columna > 0 && tablero[procesador - 1][columna - 1] == 1){//Esquina Superior Izquierda
			numCelulasVivas++;
		}
		if(tablero[procesador - 1][columna] == 1){//Arriba
			numCelulasVivas++;
		}
		if(columna < tamano && tablero[procesador - 1][columna + 1] == 1){//Esquina Superior Derecha
			numCelulasVivas++;
		}
		if(columna > 0 && tablero[procesador][columna - 1] == 1){ //Izquierda
			numCelulasVivas++;
		}
		if(columna < tamano && tablero[procesador][columna + 1] == 1){ //Derecha
			numCelulasVivas++;
		}
		if(columna > 0 && tablero[procesador + 1][columna - 1] == 1){ //Esquina Inferior Izquierda
			numCelulasVivas++;
		}
		if(tablero[procesador + 1][columna] == 1){ //Abajo
			numCelulasVivas++;
		}
		if(tablero[procesador + 1][columna + 1] == 1){ //Esquina Inferior Derecha	
			numCelulasVivas++;
		}
		if(tablero[procesador][columna] == 1){//Actuamos sobre las celulas en la copia de la matriz
			//La celulas vivas con 2 o 3 celulas vivas pegadas, se mantiene vivas.
			if(numCelulasVivas == 2 || numCelulasVivas == 3){
				vecRen[columna - 1] = 1;
			}
            else{//Si no se cumple la condicion, mueren.
				vecRen[columna - 1] = 0;
			}
		}
		else{
			if(numCelulasVivas == 3){//Las celulas muertas con 3 celulas vivas pegadas, resucitan.
				vecRen[columna - 1] = 1;
			}
		}
		numCelulasVivas = 0;//Ponemos a 0 el contador
	}
}

//Función principal
int main(int argc, char **argv){
	
	char auxX[100]="set xrange [ -0.500000 : ";
   	char auxRango[2]="";
   	char auxY[100]="set yrange [ -0.500000 : ";
	
	FILE * archivoPuntos = fopen("Calor.txt", "w");
	
	int pid, npr;
	int i, salir;
	int fil, col;
	srand(time(NULL));
	
	//Inicializamos MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD , &pid);
	MPI_Comm_size(MPI_COMM_WORLD , &npr);
	
	int tamano = npr + 2, count = tamano * tamano;
	int tablero[tamano][tamano], aux[tamano][tamano], vecRen[npr];
	int temporal[npr][npr];
	int poblacion, cuenta;
	
	if(pid == 0){ //Procesador 0	
		for(i = 0; i < tamano; i++){ //Define los limites de la fontera con 0
			aux[0][i] = tablero[0][i] = aux[i][0] = tablero[i][0] = 0;
			aux[npr - 1][i] = tablero[npr - 1][i] = aux[i][npr - 1] = tablero[i][npr - 1] = 0;
		}
		
		poblacion = ((count/100.0)*tipo);
		printf("\n");
		for(i = 0; i < poblacion; i++){
			fil = rand() % npr;
			col = rand() % npr;
			//Si la celula esta muerta, la resucita
			if(tablero [fil + 1][col + 1] == 0){
				aux[fil + 1][col + 1] = tablero[fil + 1][col + 1] = 1;
			}
			/*Si ya estaba viva se mantiene, y no lo contamos como
			una posicion añadida, asi aseguramos que se impriman el
			numero de celulas vivas seleccionado. Por ello restamos uno
			al contador*/
			else
				i--;
		}
	}
	
	MPI_Barrier(MPI_COMM_WORLD); //Barrera para que todos lo ejecuten a la vez

	if(pid == 0){
		double inicio, final, final1, final2;
		int turno = 0;
		inicio = final = final1 = final2 = 0;
		do{
			//printf("Tablero\n");
			//imprimeM(tamano, tablero); //Imprime el tablero
			system(LIMPIAR);
			printf("Turno: %d\n", turno);
			printf("Población: %d\n", poblacion);
			printf("El tamaño del tablero es de : %d * %d\n", npr, npr);
			printf("Tiempo de actualización del sistema: %f[s]\n", (final - inicio));
			printf("Tiempo de envio del tablero: %f[s]\n", (final1 - inicio));
			printf("Tiempo de actualización del renglón: %f[s]\n", (final2 - inicio));
			
			inicio = MPI_Wtime();
			MPI_Bcast(tablero, count, MPI_INT, 0, MPI_COMM_WORLD); //Envia el tablero
			final1 = MPI_Wtime();
			
			actualiza(tamano, tablero, pid + 1, vecRen); //Se actualiza el tablero con el renglón correspondiente
			cuenta = Vida(npr, vecRen);
			final2 = MPI_Wtime();
			
			MPI_Barrier(MPI_COMM_WORLD); //Barrera para que todos lo ejecuten a la vez
			
			MPI_Reduce(&cuenta, &poblacion, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
			MPI_Gather(&vecRen, npr, MPI_INT, temporal, npr, MPI_INT, 0, MPI_COMM_WORLD ); //Se reciben los renglones ya actualizados

			final = MPI_Wtime();
			convertirM(tamano, temporal, tablero);
			turno ++;
			imprimeTableroArchivo(tamano, tablero,archivoPuntos); //Imprime el tablero
			salir = decision();
			MPI_Bcast(&salir, 1, MPI_INT, 0, MPI_COMM_WORLD);
			
		} while (salir!=0);
		
		char * configGnuplot[] = {	//"set view map",
								//"splot \"Calor.txt\" matrix with image",
								"set terminal gif animate delay 100", 
								"set output 'juego.gif'",
								"unset key",
								"set style increment default",
								"set view map scale 1",
								"set style data lines",
								"set xtics border in scale 0,0 mirror norotate  autojustify",
								"set ytics border in scale 0,0 mirror norotate  autojustify",
								"set ztics border in scale 0,0 nomirror norotate  autojustify",
								"unset cbtics",
								"set rtics axis in scale 0,0 nomirror norotate  autojustify",
								"set title \"Juego de la vida\"",
								"set xrange [ -0.500000 : 7.50000 ] noreverse nowriteback",
								"set x2range [ * : * ] noreverse writeback",
								"set yrange [ -0.500000 : 7.50000 ] noreverse nowriteback",
								"set y2range [ * : * ] noreverse writeback",
								"set zrange [ * : * ] noreverse writeback",
								"set cblabel \"\"",
								"set cbrange [ 0.00000 : 1.00000 ] noreverse nowriteback",
								"set rrange [ * : * ] noreverse writeback",
								"set palette rgbformulae 7, 5, 15",
								//"splot \"Calor.txt\" matrix with image",
								"stats \"Calor.txt\" nooutput",
								"do for [i=1:int(STATS_blocks) ] { splot \"Calor.txt\" index (i-1) matrix with image }"
							};
		sprintf(auxRango,"%d",npr - 1);
		//printf("%s\n",auxRango );
		strcat(auxX,auxRango);
		strcat(auxX, ".50000 ] noreverse nowriteback");
		//printf("%s\n",auxX);
		
		strcat(auxY,auxRango);
		//printf("%s\n",auxY);
		strcat(auxY, ".50000 ] noreverse nowriteback");
		//printf("%s\n",auxY);
		//printf("\n");
		configGnuplot[12] = auxX;
		configGnuplot[14] = auxY;
		
		FILE * ventanaGnuplot = popen ("gnuplot -persist", "w");
		// Executing gnuplot commands one by one
		for (i=0;i<NUM_COMANDOS;i++){
			fprintf(ventanaGnuplot, "%s \n", configGnuplot[i]);
		}
		fclose(archivoPuntos);
	}
	else{
		do{
			MPI_Bcast(tablero, count, MPI_INT, 0, MPI_COMM_WORLD);
			
			actualiza(tamano, tablero, pid + 1, vecRen); //Se actualiza el tablero con el renglón correspondiente
			cuenta = Vida(npr, vecRen);
			
			MPI_Barrier(MPI_COMM_WORLD); //Barrera para que todos lo ejecuten a la vez
			MPI_Reduce(&cuenta, &poblacion, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
			MPI_Gather(&vecRen, npr, MPI_INT, temporal, npr, MPI_INT, 0, MPI_COMM_WORLD ); //Se reciben los renglones ya actualizados
			
			
			MPI_Bcast(&salir, 1, MPI_INT, 0, MPI_COMM_WORLD);
			
		}while(salir != 0);
		
	}
	
	MPI_Finalize();
	return 0;
}
	
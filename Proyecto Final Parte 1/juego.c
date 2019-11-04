//Castro Molano Ramsés
//Proyecto Final Primera Parte: Juego de la Vida Secuencial.
//Fecha de Entrega: 04 de Noviembre del 2019
//Materia: Sistemas Distribuidos.

//Definimos las bibliotecas a utilizar
#include <stdio.h> //Biblioteca Estándar de Entrada Salida.
#include <stdlib.h> //Biblioteca Estándar.
#include <string.h> //Biblioteca de Carácteres y Cadenas.
#include <time.h> //Biblioteca de tiempo.
#include <conio.h>//Biblioteca de Entrada Salida en Consola (Solo funciona en Windows).
#define Filas 20 //Definimos el tamaño de las filas como constante.
#define Columnas 20 //Definimos el tamaño de las columnas como constante.

//Función encargada de imprimir el tablero
void Imprimir(int Matriz[Filas][Columnas]){
	int i, j; //Variables que se utilizan en los ciclos for
	for(i = 0; i < Filas; i++){ //Ciclo para recorrer las filas
		for(j = 0; j < Columnas; j++){ //Ciclo para recorrer las columnas
			if(Matriz[i][j] == 0){
				//Si es 0 la celula esta muerta, por lo que se imprime un punto
				printf(". ");
			}
			else{//Si no, esta viva, por lo que se imprime un asterisco
				printf("* ");
			}
		}
		printf("\n");
	}
}

//Función dedicada a realizar copias del tablero
void Duplicar(int origen[Filas][Columnas], int destino[Filas][Columnas]){
	int i, j; //Variables que se utilizan en los ciclos for
	for(i = 0; i < Filas; i++) //Ciclo para recorrer las filas
		for(j = 0; j < Columnas; j++) //Ciclo para recorrer las columnas
			//Copiamos la matriz origen en destino
			destino[i][j]=origen[i][j];
}

//Función dedicada a actualizar el tablero y las celulas
void Refrescar(int Matriz[Filas][Columnas]){
	int copiaMatriz[Filas][Columnas], NUMcelulasvivas = 0;
	int i, j; //Variables que se utilizan en los ciclos for
		//Copiamos la matriz en una copia auxiliar
        Duplicar(Matriz, copiaMatriz); 
		for(i = 0; i < Filas; i++){ //Ciclo para recorrer las filas
			for(j = 0; j < Columnas; j++){ //Ciclo para recorrer las columnas
				//Control de las celulas vecinas vivas
				if(i > 0 && j > 0 && Matriz[i-1][j-1] == 1){//Esquina Superior Izquierda
					NUMcelulasvivas++;
				}
				if(i > 0 && Matriz[i-1][j] == 1){//Arriba
					NUMcelulasvivas++;
				}
				if(i > 0 && j < Columnas && Matriz[i-1][j+1] == 1){//Esquina Superior Derecha
					NUMcelulasvivas++;
				}
				if(j > 0 && Matriz[i][j-1] == 1){ //Derecha
					NUMcelulasvivas++;
				}
				if(j < Columnas && Matriz[i][j+1] == 1){ //Izquierda
					NUMcelulasvivas++;
				}
				if(i < Filas && j > 0 && Matriz[i+1][j-1] == 1){ //Esquina Inferior Izquierda
					NUMcelulasvivas++;
				}
				if(i < Filas && Matriz[i+1][j] == 1){ //Abajo
					NUMcelulasvivas++;
				}
				if(i < Filas && j < Columnas && Matriz[i+1][j+1] == 1){ //Esquina Inferior Derecha
					NUMcelulasvivas++;
				}
				if(Matriz[i][j] == 1){//Actuamos sobre las celulas en la copia de la matriz
					//La celulas vivas con 2 o 3 celulas vivas pegadas, se mantiene vivas.
					if(NUMcelulasvivas == 2 || NUMcelulasvivas == 3){
						copiaMatriz[i][j] = 1;
					}
                    else{//Si no se cumple la condicion, mueren.
						copiaMatriz[i][j]=0;
                    }
                }
                else{
                    if(NUMcelulasvivas == 3){//Las celulas muertas con 3 celulas vivas pegadas, resucitan.
						copiaMatriz[i][j] = 1;
					}
				}
                NUMcelulasvivas = 0;//Ponemos a 0 el contador
			}
		}
        Duplicar(copiaMatriz, Matriz); //Devolvemos los nuevos datos a la matriz original
}

//Función dedicada a revivir alguna célula para modificar el comportamiento del juego
void Resucitar(int Matriz[Filas][Columnas]){
	int i,j,a,b; //Variables que se utilizan como opciones 
	do{ //Ciclo de opción de celulas 
		printf("Introduce fila <1-%d>: ", Filas);
		scanf("%d",&i);
	}while(i < 1 || i > Filas);
	do{
		printf("\nIntroduce columna <1-%d>: ", Columnas);
		scanf("%d",&j);
	}while(j < 1 || j > Columnas);
	a = Matriz[i-1][j-1]; //Copiamos la el valor de la celula, para poder revertir el cambio
	Matriz[i-1][j-1] = 1; //Resucitamos la celula seleccionada
	system("cls");
	Imprimir(Matriz);
	printf("\nCompruebe la seleccion, desea mantenerla? [s/n]");
	b = getch();
	//Limpiamos el buffer
	fflush(stdin);
	//Si no se mantiene, se devuelve el valor de la celula copiada anteriormente
	if(b == 'n') Matriz[i-1][j-1]=a;
}

//Función dedicada a realizar el conteo de células vivas
int Vida(int conteo, int Matriz[Filas][Columnas]){
	int i, j; //Variables dedicadas a los ciclos for
	conteo = 0; //Inicializamos la variable del conteo en 0
	for(i = 0; i < Filas; i++){ //Se recorren las filas
		for(j = 0; j < Columnas; j++){ //Se recorren las columnas
			//Pregunta si existe la célula está viva
			if(Matriz[i][j] == 1)
				conteo++;
		}
	}
	//Devolvemos el número de células existentes
	return conteo;
}

//Función dedicada a eliminar alguna célula para modificar el comportamiento del juego
void Eliminar(int Matriz[Filas][Columnas]){
	int i,j,a,b;
	do{ //Ciclo de opción de celulas 
		printf("Introduce fila <1-%d>: ", Filas);
		scanf("%d",&i);
	}while(i < 1 || i > Filas);
	do{
		printf("\nIntroduce columna <1-%d>: ", Columnas);
		scanf("%d",&j);
	}while(j < 1 || j > Columnas);
	a = Matriz[i-1][j-1]; //Copiamos la el valor de la celula, para poder revertir el cambio.
	Matriz[i-1][j-1] = 0; //Eliminamos la celula seleccionada.
	system("cls");
	Imprimir(Matriz);
	printf("\nCompruebe la seleccion, desea mantenerla? [s/n]");
	b = getch();
	//Limpiamos el buffer
	fflush(stdin);
	//Si no se mantiene, se devuelve el valor de la celula copiada anteriormente
	if(b == 'n') Matriz[i-1][j-1] = a;
}

//Función principal dedicada a la ejecución del juego
void Juego(){
	//Definimos las diversas variables a utilizar
	int poblacion, i, j, fil, col, repetir, confirmar, turno = 0;
	int Matriz [Filas][Columnas], tipo, conteo = 0;
	clock_t t_ini, t_fin;
	double secs;
	char letra;
	do{//Menu inicial
		system("cls");
		printf("Bienvenido al juego de la Vida\n");
		printf("Algunas distribuciones que podrían ser interesantes son:\n");
		printf("\t1)Dispersa 10% \n\t2)Normal 25% \n\t3)Densa 50% \n\t4)Masiva 75% \n");
		printf("Ingresa un porcentaje de distribución (1 - 99): ");
		scanf("%d",&tipo);
		system("cls");
		//Ponemos todas las celulas muertas inicialmente
		t_ini = clock();
		for(i = 0; i < Filas; i++){
			for(j = 0; j < Columnas; j++){
				Matriz [i][j] = 0;
			}
		}
		poblacion = (((Filas*Columnas)/100)*tipo);
		//Modo aleatorio
		srand(time(0));
		for(i = 0; i < poblacion; i++){
			fil = rand() % Filas;
			col = rand() % Columnas;
			//Si la celula esta muerta, la resucita
			if(Matriz [fil][col] == 0){
				Matriz[fil][col] = 1;
			}
			/*Si ya estaba viva se mantiene, y no lo contamos como
			una posicion añadida, asi aseguramos que se impriman el
			numero de celulas vivas seleccionado. Por ello restamos uno
			al contador*/
			else
				i--;
			}
		t_fin = clock();
		do{
			do{
				system("cls");
				conteo = Vida(conteo, Matriz);
				Imprimir(Matriz);
				t_fin = clock();
				secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
				printf("\nTurno: %d\nCelulas vivas: %d\n", turno, conteo);
				printf("Tiempo de respuesta: %.16g milisegundos\n", secs * 1000.0);
				printf("Pulse una tecla:\n[s] para salir\n[c] para revivir celula\n[e] para eliminar\n");
                //Opciones en el juego
				letra = getch();
				//Limpiamos el buffer
				fflush(stdin);
				if(letra == 's'){
					system("cls");
                    Imprimir(Matriz);
                    printf("\nFin del juego");
                }
				else if(letra == 'c'){
					system("cls");
					Imprimir(Matriz);
					Resucitar(Matriz);
                }
				else if(letra == 'e'){
					system("cls");
					Imprimir(Matriz);
					Eliminar(Matriz);
				}
				else{
					t_ini = clock();
					Refrescar(Matriz);
					turno ++;
				}
			}while(letra != 's');
			//Confirmacion de salida, para prevenir equivocaciones
			system("cls");
			printf("\n\n\n\n%20cSeguro que quieres salir? [s/n]", ' ');
			confirmar = getch();
			fflush(stdin);
		}while(confirmar == 'n');
		system("cls");
		//Opcion para volver a empezar, asi no hace falta salir del programa y volver a ejecutar
		printf("\n\n\n\n%20cVolver a empezar? [s/n]", ' ');
		turno = 0;
		repetir = getch();
		//Limpiamos el buffer
		fflush(stdin);
	}while(repetir == 's');
}

//Función main
int main(){
	Juego();//Iniciamos el juego
}
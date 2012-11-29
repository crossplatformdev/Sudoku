#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int Seleccion()
{
	char cadena[MAX_BUFFER]; 
	char seleccion;

	MuestraCabecera();
	
	do{
			printf("\t\t1 - Empezar a jugar\n");
			printf("\t\t2 - Recuperar una partida.\n");
			printf("\t\t3 - Salir del programa.\n");

			printf("\n\nIntroduce seleccion... \t");
			scanf("\n%s", cadena);
			fflush(stdin);
			if (strlen(cadena)==1)
			{
				seleccion = (char)cadena[0];	
			}
			if (seleccion != JUGAR && seleccion != CARGAR && seleccion != SALIR) 
			{
				printf("ERROR! Elige una opcion valida.\n\n\n\a");
			}
		}while(seleccion != JUGAR && seleccion != CARGAR && seleccion != SALIR); //No permite elegir otra opcion que no sea una valida.

return seleccion;
}

int LeerPartidas(struct sudoku* sk)
{
	int error = -1;
	char puzzles[L_NOMBRE];
	FILE *puzzles_cortos = NULL;

	puzzles_cortos = fopen ("puzzles.txt", "r");

	if (puzzles_cortos == NULL) 
	{
		printf("ERROR AL LEER EL ARCHIVO \"puzzles.txt\".\nCompruebe que los archivos esten en el directorio del ejecutable.\n\a");
		error = 0;
	}
	else 
	{

		do{	
			printf("\n\nEstas son las partidas disponibles: \n\n");
			rewind(puzzles_cortos);
				while (!feof(puzzles_cortos))//Muestra partidas del fichero
				{
					
					fscanf(puzzles_cortos, "\n%s", puzzles);
					fflush(stdin);
					printf("\t%s", puzzles);
					printf("\n");
				}	

				printf("\nIntroduce una partida (8 caracteres):\t");
	
	
				scanf("\n%s", sk->partida);
				fflush(stdin);

				rewind(puzzles_cortos);

				while (!feof(puzzles_cortos)) //Compara la partida con las partidas del fichero
				{
					fscanf(puzzles_cortos, "\n%s", puzzles);
					fflush(stdin);
					if( !strcmp( puzzles , sk->partida))
					{
						error = 1;
					}
					
				}
		
		}while( error == -1 );
	fclose(puzzles_cortos);
	}//fin del else
	return error;
}

int EmpezarPartida(struct sudoku *sk)
{
	int error = 0;

		do {error = LeerPartidas(sk); if (error == 0) return error;} while (error != 1); //Vuelve al menu si no ha podido abrir puzzles.txt

		do { error = LeeTablero(sk); if (error == 0) return error;} while (error != 1); // Si consiguio leer el archivo anterior, intentara abrir la partida. Si no, vuelve al menu principal.

		if ( error == 0 )
		{
			DibujarTablero(sk);
		}
		else if (error == -1)
		{
			DibujarTablero(sk);
			return error;
		}

		if (sk->espacios == 0) return -1; // Si un fichero estuviera compuesto completamente por numeros, esto volveria al menu inicial.
return error;
}

int CargarPartida(struct sudoku *sk) // Similar a la funcion anterior, pero inicializa el sudoku con una partida de almacenadas.txt
{
	int error = 0;

		do { error = LeeTablero(sk); if (error == 0){ printf("No hay ninguna partida guardada\n\a"); return error;}} while (error != 1);

		if ( error == 0 )
		{
			DibujarTablero(sk);
		}
		else if (error == -1)
		{
			DibujarTablero(sk);
			return error;
		}

		if (sk->espacios == 0) return -1; // Si un fichero estuviera compuesto completamente por numeros, esto volveria al menu inicial.
	
return error;
}

void MuestraCabecera() // ASCII ART :)
{
	printf("*************************************************************************\n");
	printf("*     /////  //   //  ////     ////    //  //  //   //     (OMG!)       *\n");
	printf("*    //     //   //  // //   //  //   // //   //   //    O              *\n");
	printf("*   /////  //   //  //  //  //   //  /////   //   //    0   ~///        *\n");
	printf("*     //  //   //  //  //  //   //  //  //  //   //      o (O.o)        *\n");
	printf("* /////   /////   /////    /////   //   //  /////   ___o00o_\\./_o00o___ *\n");
	printf("*************************************************************************\n");
	printf("\n\n\n\n\n");
}

int Jugar(struct sudoku* sk)
{

	int error = 0;
	struct coor fc = {PUNTO,PUNTO};

	do
	{
		error = InsertaNumero(sk, fc);
		if ( error == -1) return error; // Si error == -1 Salir
		if ( error == -2 ) { GuardaTablero(*sk); return error;} // Si error == -2, guarda la partida.
		if ( error == -3 ) { ModificaNumero(sk, fc); return error;} // Si error == -3, modifica un numero.
		if ( error == -4 ) { LimpiaTablero(sk); return error;} // Si error == -4, vuelve el tablero a su estado original.
		
									
	
	}while(error == 1 ); // Insertar numero mientras haya errores.

return error;
}

void DibujarTablero(struct sudoku* sk) //No tiene misterio. Dibuja el tablero e imprime las estadisticas.
{
	int i, j;

	printf("\t\t\t  |1 2 3|4 5 6|7 8 9|\n");
	for ( i = MIN_FILA ; i <= MAX_FILA ; i++)
	{
		

		if( (i-CHAR)%FILAS==0 || (i-CHAR)%FILAS==3 || (i-CHAR)%FILAS==6 )
		{
			printf("\t\t\t- |- - -|- - -|- - -|\n");
		}	
		printf("\t\t\t%c ", i);
			for ( j = MIN_COLUMNA ; j <= MAX_COLUMNA ; j++)
			{

				if( (j-INT)%COLUMNAS==0 || (j-INT)%COLUMNAS==3 || (j-INT)%COLUMNAS==6 )
				{
					printf("|");
				}
					printf("%c", sk->panel[i-CHAR][j-INT]);


				if( (j-INT)%COLUMNAS!=2 && (j-INT)%COLUMNAS!=5 && (j-INT)%COLUMNAS!=8)
				{
					printf("-");
				}
			}

	printf("|\n");	
	}
	printf("\t\t\t- |- - -|- - -|- - -|\n\n");
	printf("\tPartida:   %s \tNumero de huecos:   %d \n\tPorcentaje del tablero completado:\t%.3f%%\n", sk->partida, sk->espacios, 100.0-((float)sk->espacios*100/(CASILLAS)) );


}

int LeeTablero(struct sudoku* sk) // Abre partidas de sudokus (puzzles.txt o almacenadas.txt) e inicializa el juego.
{
	int i,j,error;
	char extension[L_EXTENSION+1] = ".txt";
	FILE *partida = NULL;

	sk->espacios = 0;

	strcat(sk->partida, extension);
	printf("Partida: %s\n" , sk->partida);
	partida = fopen (sk->partida, "r");

	if (partida == NULL) 
	{
		printf("ERROR AL LEER EL ARCHIVO DE PARTIDA.\nCompruebe que los archivos esten en el directorio del ejecutable.\n\a");
		error = 0;
	}
	else 
	{
		for (i=0; i< FILAS ;i++)
		{	
			for (j=0;j < COLUMNAS ;j++)
			{
				fscanf( partida , "\n%c", &sk->panel[i][j]); // En este bucle se inicializa el sudoku
				if (sk->panel[i][j] == PUNTO) sk->espacios++; // y se actualiza el numero de espacios.
			}	
		}
	error = 1;
	fclose(partida);
	}
	return error;
}
int CompruebaCoordenadas(char *coord) 
{
	int error = 1;
	
//Comprueba si las coordenadas son correctas. Si son "Coordenadas-Comando" las identifica y hace lo que corresponda.

		if( coord[0] == 'S' && coord[1] == 'A') 
		{
			printf("Ha elegido salir de la aplicacion.\n");
			error = -1;
			return error;
		}
		if( coord[0] == 'G' && coord[1] == 'P') 
		{
			printf("Ha elegido guardar la partida.\n");
			error = -2;
			return error;
		}
		if( coord[0] == 'C' && coord[1] == 'N') 
		{
			printf("Ha elegido cambiar un numero.\n");
			error = -3;
			return error;
		}
		if( coord[0] == 'L' && coord[1] == 'T') 
		{
			printf("Ha elegido limpiar el tablero.\n");
			error = -4;
			return error;
		}
		if( strlen(coord) != 2 ) 
		{
			printf("Debes escribir en formato (LN [LineaColumna, sin espacios y en los margenes permitidos]).\n\a");
			error = 0;						
		}
		if((coord[0] < MIN_FILA) || (coord[0] > MAX_FILA)) 
		{	
			printf("Has introducido una opcion invalida!(FILA = %c)\n\a", coord[0]);	
			error=0;
		}
			
		if((coord[1] < MIN_COLUMNA) || (coord[1] > MAX_COLUMNA)) 
		{	
			printf("Has introducido una opcion invalida!(COLUMNA = %c)\n\a", 	coord[1]);	
			error=0;
		}

return error;
}
int CasillaVacia(struct sudoku sk,struct coor fc)
{
	int error;

		if( (sk.panel[fc.fila-CHAR][fc.columna-INT] == PUNTO ) &&
	   	(fc.fila >= MIN_FILA && fc.columna <= MAX_COLUMNA) &&
	   	(fc.columna >= MIN_COLUMNA && fc.columna <= MAX_COLUMNA) )
		{
			error = 1;
		}
		else
		{
			printf("La casilla ya ha sido rellenada con un numero. Elige otra.\n\a");
			error = 0;
		}
		
	return error;
}
int CompruebaNumero(char * num)
{
	int error;

		if ((*num >= MIN_NUMERO && *num <= MAX_NUMERO))
		{
			error = 1;
		}
		else
		{	
			printf("Has introducido una opcion invalida!(NUMERO = %c)\n\a", 	*num);	
			error=0;
		}
return error;
}

int CambiaNumero(char * num)
{
	int error;

	if ((*num >= MIN_NUMERO && *num <= MAX_NUMERO) || *num == PUNTO)
	{
		error = 1;
	}
	else
	{	
		printf("Has introducido una opcion invalida!(NUMERO = %c)\n\a", 	*num);	
		error=0;
	}

return error;
}

int InsertaNumero(struct sudoku* sk,struct coor fc)
{
//Inserta un numero si las coordenadas son correctas y no hay un numero ya introducido en ellas.
	int error = 0;
	char coord[MAX_BUFFER];
	char num;

	do{
		while (error == 0)
		{
			DibujarTablero(sk);//
			if ( sk->espacios <= 0){ printf("\nTABLERO COMPLETADO!!!\n\a");  return -1;} 
			printf("\nOpciones: CN=CambiarNumero LT=LimpiarTablero GP=GuardarPartida SA=SAlir\n\n"); 
			printf("Introduce una fila A-I e introduce una columna 1-9...(Formato LC).\t");					
			scanf("\n%s", coord);
			fflush(stdin);
			fc.fila = coord[0];
			fc.columna = coord[1];	

			error =	CompruebaCoordenadas(coord);

			if(error == -1 || error == -2 || error == -3 || error == -4) return error;
		
			
		}
		error = CasillaVacia(*sk , fc);
	}while (error != 1);

	do{
	printf("Ahora introduce un valor 1-9...(C=Cancelar)\t");
	scanf("\n%c", &num);
	fflush(stdin);
	if (num == 'C'){printf("\nOperacion Cancelada. \n\a"); return 0;} // 'C' Cancela la introduccion del numero, vuelve a pedir coordenadas.
	error = CompruebaNumero(&num);
	if (error == 1) error = NumeroValido( *sk, coord, &num);

	}while (error == 0);
									
	sk->panel[fc.fila-CHAR][fc.columna-INT] = num;			
	printf("\nHas elegido:\n\n"); 
	printf("Fila:%c\n", fc.fila);
	printf("Columna:%c\n", fc.columna);
	printf("Numero:%c\n", num);
	printf("\n");
	if (sk->panel[fc.fila-CHAR][fc.columna-INT] != PUNTO) sk->espacios--;else sk->espacios++;

	return error;
}

int GuardaTablero(struct sudoku sk)
{
	int i,j,error;
	FILE *saved = NULL;
	char partida[MAX_BUFFER];
	
	printf("Introduce el nombre de la partida: \n");
	scanf("\n%s", partida);
	fflush(stdin);
	
	GuardaPartida(partida); // Primero guarda el nombre en almacenadas.txt.
	
	strcat(partida, ".txt");
	saved = fopen ( partida , "w"); // Abre la partida.txt como escritura.

	if (saved == NULL) 
	{
		printf("ERROR AL ABRIR EL ARCHIVO DE PARTIDA.\n\a");
		error = 0;
	}
	else 
	{
		for (i=0; i< FILAS ;i++)
		{	
			for (j=0;j < COLUMNAS ;j++)
			{
				fprintf( saved , "%c", sk.panel[i][j]); //Luego guarda la matriz en el fichero.
			}
			fprintf( saved , "\n");
		}
	error = 1;
	fclose(saved);
	}
return error;
}


int NumeroValido(struct sudoku sk, char coord[], char * num)
{
	int error = 1;
	char f, fila = coord[0];
	char c, columna = coord[1];
	char sub_cuadrante[MAX_SUBCUADRANTE];

	for ( f = MIN_FILA ; f <= MAX_FILA; f++) // Comprueba que num no este repetido en las columnas.
	{
		
		if( sk.panel[f-CHAR][columna-INT] == *num && *num != PUNTO ) 
		{
			printf("Ese numero ya esta presente en esa columna!.\n\a");
			error = 0;						
		}

	}

	for ( c = MIN_COLUMNA ; c <= MAX_COLUMNA ; c++)// Comprueba que num no este repetido en las filas.
	{

		if( sk.panel[fila-CHAR][c-INT] == *num && *num != PUNTO) 
		{
			printf("Ese numero ya esta presente en esa fila!.\n\a");
			error = 0;						
		}

	}
	
	sub_cuadrante[0] = coord[0];
	sub_cuadrante[1] = coord[1];


	//Localizamos el subcuadrante al que pertenecen las coordenadas.
	if (( (int)(fila-CHAR) % 9  == 0) || ( (int)(fila-CHAR) % 9  == 1) || ( (int)(fila-CHAR) % 9  == 2)) sub_cuadrante[0] = 'A';
	if (( (int)(fila-CHAR) % 9  == 3) || ( (int)(fila-CHAR) % 9  == 4) || ( (int)(fila-CHAR) % 9  == 5)) sub_cuadrante[0] = 'D';
	if (( (int)(fila-CHAR) % 9  == 6) || ( (int)(fila-CHAR) % 9  == 7) || ( (int)(fila-CHAR) % 9  == 8)) sub_cuadrante[0] = 'G';

	if (( (int)(columna-INT) % 9  == 0) || ( (int)(columna-INT) % 9  == 1) || ( (int)(columna-INT) % 9  == 2)) sub_cuadrante[1] = '1';
	if (( (int)(columna-INT) % 9  == 3) || ( (int)(columna-INT) % 9  == 4) || ( (int)(columna-INT) % 9  == 5)) sub_cuadrante[1] = '4';
	if (( (int)(columna-INT) % 9  == 6) || ( (int)(columna-INT) % 9  == 7) || ( (int)(columna-INT) % 9  == 8)) sub_cuadrante[1] = '7';


	for ( f = (sub_cuadrante[0]-CHAR) ; f <= (sub_cuadrante[0]-CHAR)+2 ; f++) // Comparamos num con los numeros del subcuadrante.
	{
		for ( c = (sub_cuadrante[1]-INT) ; c <= (sub_cuadrante[1]-INT)+2 ; c++)
		{	
			if( sk.panel[(int)f][(int)c] == *num && *num != PUNTO) 
			{
				printf("Ese numero ya esta presente en ese cuadrante!.\n\a");
				error = 0;						
			}
		}
	}
	return error;
}

int LeerPartidasGuardadas(struct sudoku* sk)
{
	int error = -1;
	char partidas[L_NOMBRE];
	FILE *salvadas = NULL;

	salvadas = fopen ("almacenadas.txt", "r");

	if (salvadas == NULL) 
	{
		printf("ERROR AL LEER EL ARCHIVO \"almacenadas.txt\".\nCompruebe que los archivos esten en el directorio del ejecutable.\n\a");
		error = 0;
	}
	else 
	{

		do{	
			printf("\n\nEstas son las partidas guardadas: \n\n");
			rewind(salvadas);
				while (!feof(salvadas)) // Muestra los nombres de partidas guardadas en almacenadas.txt. SIEMPRE APARECE EL ULTIMO NOMBRE DOS VECES!!??
				{
					
					fscanf( salvadas , "\n%s", partidas);
					fflush(stdin);
					if (fscanf( salvadas , "\EOF", partidas)) break;
					printf("\t%s", partidas);
					printf("\n");
				}	

				printf("\nIntroduce una partida (8 caracteres):\t");
	
	
				scanf("\n%s", sk->partida);
				fflush(stdin);

				rewind(salvadas);

				while (!feof(salvadas)) // Compara que la partida que introducimos exista en almacenadas.txt.
				{
					fscanf(salvadas, "\n%s", partidas);
					fflush(stdin);
					if( !strcmp( partidas , sk->partida))
					{
						error = 1;
					}
					
				}
		
		}while( error == -1 );
	fclose(salvadas);
	}
	return error;
}	

int GuardaPartida(char partida[])
{
	int error;
	char partidas[MAX_BUFFER];
	FILE *indice = NULL;
	indice = fopen ("almacenadas.txt", "a"); //Abre almacenadas.txt en modo 'append' para ir añadiendo nombres de partidas al final del fichero.

	if (indice == NULL) 
	{
		printf("ERROR AL ABRIR EL ARCHIVO DE PARTIDAS GUARDADAS.\n\a");
		error = 0;
	}
	else 
	{
		fprintf( indice, "%s\n", partida);
		fclose(indice);
		error = 1;
	}
return error;
}

int ModificaNumero(struct sudoku* sk,struct coor fc)
{

	int error = 0;
	char coord[MAX_BUFFER];
	char num;

	//Identica a InsertaNumero() solo que en lugar de dejar escribir en los puntos, escribe en los numeros ya escritos.

	do{
		while (error == 0)
		{
			DibujarTablero(sk);//
			if ( sk->espacios <= 0){ printf("\nTABLERO COMPLETADO!!!\n");  return -1;} 
			printf("\nOpciones: CN=CambiarNumero LT=LimpiarTablero GP=GuardarPartida SA=SAlir\n\n"); 
			printf("Introduce una fila A-I e introduce una columna 1-9.\n(Formato LC) del numero que quieras modificar: \t");

			scanf("\n%s", coord);
			fflush(stdin);
			fc.fila = coord[0];
			fc.columna = coord[1];	
 		
			error =	CompruebaCoordenadas(coord);
			if(error == -1 || error == -2 || error == -3 || error == -4) return error;
		
		}
		error = CasillaLlena(*sk , fc);
	}while (error != 1);

	do{
	printf("Ahora introduce un valor 1-9 o punto para borrar...(C=Cancelar)\t");
	scanf("\n%c", &num);
	fflush(stdin);
	if (num == 'C'){printf("\nOperacion Cancelada. \n\a"); return 0;}// 'C' Cancela la introduccion del numero, vuelve a pedir coordenadas.
	error = CambiaNumero(&num);
	if (error == 1) error = NumeroValido( *sk, coord, &num);

	}while (error == 0);
									
	sk->panel[fc.fila-CHAR][fc.columna-INT] = num;			
	printf("\nHas elegido:\n\n"); 
	printf("Fila:%c\n", fc.fila);
	printf("Columna:%c\n", fc.columna);
	printf("Numero:%c\n", num);
	printf("\n");
	if (sk->panel[fc.fila-CHAR][fc.columna-INT] != PUNTO) sk->espacios--;else sk->espacios++;

	return error;
}

int CasillaLlena(struct sudoku sk,struct coor fc)
{
	int error;
						if( (sk.panel[fc.fila-CHAR][fc.columna-INT] != PUNTO ) &&
						   	(fc.fila >= MIN_FILA && fc.columna <= MAX_COLUMNA) &&
						   	(fc.columna >= MIN_COLUMNA && fc.columna <= MAX_COLUMNA) )
						{
							error = 1;
						}

						else
						{
							printf("La casilla ya esta vacia. Elige otra.\n\a");
			
							error = 0;
						
						}
		
	return error;
}	
int LimpiaTablero(struct sudoku* sk)
{
	int i,j,error;
	FILE *partida = NULL;

	sk->espacios = 0;
	
	partida = fopen (sk->partida, "r"); //Abre la partida en curso de nuevo.

	if (partida == NULL) 
	{
		printf("ERROR AL LEER EL ARCHIVO DE PARTIDA.\nCompruebe que los archivos esten en el directorio del ejecutable.\n\a");
		error = 0;
	}
	else 
	{
		for (i=0; i< FILAS ;i++)
		{	
			for (j=0;j < COLUMNAS ;j++)
			{
				fscanf( partida , "\n%c", &sk->panel[i][j]); // Reinicializa el juego.
				if (sk->panel[i][j] == PUNTO) sk->espacios++;
			}	
		}
	error = 1;
	fclose(partida);
	}

	return error;
}

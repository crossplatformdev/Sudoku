/*
* Sudoku is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Sudoku is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along
* with this program.  If not, see <http://www.gnu.org/licenses/>.
 


*					
* AUTORES: Elias Angulo Klein
*					

* FECHA: 22/11/2010			
*					
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funciones.h"

int main()
{
	int error = 1;
	int seleccion;
	struct sudoku sk =  {
	{
		{PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO},
	 	{PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO},
		{PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO},

		{PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO},
	 	{PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO},
		{PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO},

		{PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO},
	 	{PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO},
		{PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO,PUNTO}},
		{""}, 
		0,
		
	};

	do{

		seleccion = Seleccion(); //Ejecuta la seleccion del menu y la guarda para el sqitch

		switch(seleccion)
		{
	
		case JUGAR:

				error = EmpezarPartida(&sk); //Solo si error == 1 se llamara a Jugar(). 0 == error en esa funcion,
				if (error == 0 || error == -1) return 0; // -1 == Salir del juego (Vuelve al menu principal).
				do{

					error = Jugar(&sk);
					if (error == -1 || error == -2){printf("Asi ha quedado el tablero:\n");DibujarTablero(&sk);	fflush(stdin); getchar(); break;} //Continuara jugando mientras no se pida SAlir o GuardarPartida

				} while (error == 1 || sk.espacios > 0); //Continuara mientras haya errores o queden espacios.

				break;

		case CARGAR:

				error = LeerPartidasGuardadas(&sk); // Muestra las partidas de almacenadas.txt
				error = CargarPartida(&sk); // Carga la partida seleccionada en la funcion anterior.
				if (error == 0 || error == -1) return 0; // Volver al menu principal si ha habido errores.
				do{
	
					error = Jugar(&sk);
					if (error == -1 || error == -2){printf("Asi ha quedado el tablero:\n");DibujarTablero(&sk); getchar(); break;}//Continuara jugando mientras no se pida SAlir o GuardarPartida


				} while (error == 1 || sk.espacios > 0);//Continuara mientras haya errores o queden espacios.
				break;
	
		case SALIR:

			printf("\nHASTA PRONTO!!!!!\n\n");
			getchar();
			break;
				
		default:
				
			break;
		}

	}while (seleccion != SALIR);
	
	
	return 0;
}


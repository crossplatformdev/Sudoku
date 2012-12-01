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
 * AUTHOR: Elias Angulo Klein
 *

 * DATE: 2010/22/11
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int main() {
	int error = 1;
	int selection;
	struct sudoku sk = {

	{ { DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT }, { DOT, DOT, DOT, DOT,
			DOT, DOT, DOT, DOT, DOT }, { DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT,
			DOT },

	{ DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT }, { DOT, DOT, DOT, DOT, DOT,
			DOT, DOT, DOT, DOT },
			{ DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT },

			{ DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT, DOT }, { DOT, DOT, DOT,
					DOT, DOT, DOT, DOT, DOT, DOT }, { DOT, DOT, DOT, DOT, DOT,
					DOT, DOT, DOT, DOT } }, { "" }, 0,

	};

	do {

		selection = Selection();

		switch (selection) {

		case PLAY:

			error = StartGame(&sk); //Solo si error == 1 se llamara a Play(). 0 == error en esa funcion,
			if (error == 0 || error == -1)
				return 0; // -1 == Salir del juego (Vuelve al menu principal).
			do {

				error = Play(&sk);
				if (error == -1 || error == -2) {
					printf("The grid is like this:\n");
					DrawTable(&sk);
					fflush(stdin);
					getchar();
					break;
				} //Continuara jugando mientras no se pida SAlir o GuardarPartida

			} while (error == 1 || sk.spaces > 0); //Continuara mientras haya errores o queden espacios.

			break;

		case LOAD:

			error = LoadSavedGames(&sk); // Muestra las partidas de almacenadas.txt
			error = LoadGame(&sk); // Carga la partida seleccionada en la funcion anterior.
			if (error == 0 || error == -1)
				return 0; // Volver al menu principal si ha habido errores.
			do {

				error = Play(&sk);
				if (error == -1 || error == -2) {
					printf("The grid is like this:\n");
					DrawTable(&sk);
					getchar();
					break;
				} //Continuara jugando mientras no se pida SAlir o GuardarPartida

			} while (error == 1 || sk.spaces > 0); //Continuara mientras haya errores o queden espacios.
			break;

		case EXIT:

			printf("\nSEE YOU SOON!!!!!\n\n");
			getchar();
			break;

		default:

			break;
		}

	} while (selection != EXIT);

	return 0;
}


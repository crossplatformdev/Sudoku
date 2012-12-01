#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int Selection() {
	char string[MAX_BUFFER];
	char selection;

	ShowHeader();

	do {
		printf("\t\t1 - Start\n");
		printf("\t\t2 - Load.\n");
		printf("\t\t3 - Exit.\n");

		printf("\n\nInput Selection... \t");
		scanf("\n%s", string);
		fflush(stdin);
		if (strlen(string) == 1) {
			selection = (char) string[0];
		}
		if (selection != PLAY && selection != LOAD && selection != EXIT) {
			printf("ERROR! Choose a valid option.\n\n\n\a");
		}
	} while (selection != PLAY && selection != LOAD && selection != EXIT); //No permite elegir otra opcion que no sea una valida.

	return selection;
}

int LoadPuzzleIndex(struct sudoku* sk) {
	int error = -1;
	char puzzles[L_NAME];
	FILE *puzzle_short = NULL;

	puzzle_short = fopen("puzzles.txt", "r");

	if (puzzle_short == NULL) {
		printf("ERROR READING FILE \"puzzles.txt\".\n"
				"Check if saved games are in the executable directory.\n\a");
		error = 0;
	} else {

		do {
			printf("\n\nThese are the available games: \n\n");
			rewind(puzzle_short);
			while (!feof(puzzle_short)) //Muestra games del fichero
			{

				fscanf(puzzle_short, "\n%s", puzzles);
				fflush(stdin);
				printf("\t%s", puzzles);
				printf("\n");
			}

			printf("\nEnter game name (8 characters max string):\t");

			scanf("\n%s", sk->game);
			fflush(stdin);

			rewind(puzzle_short);

			while (!feof(puzzle_short)) //Compara la game con las games del fichero
			{
				fscanf(puzzle_short, "\n%s", puzzles);
				fflush(stdin);
				if (!strcmp(puzzles, sk->game)) {
					error = 1;
				}

			}

		} while (error == -1);
		fclose(puzzle_short);
	} //fin del else
	return error;
}

int StartGame(struct sudoku *sk) {
	int error = 0;

	do {
		error = LoadPuzzleIndex(sk);
		if (error == 0)
			return error;
	} while (error != 1); //Vuelve al menu si no ha podido abrir puzzles.txt

	do {
		error = ReadTable(sk);
		if (error == 0)
			return error;
	} while (error != 1); // Si consiguio leer el archivo anterior, intentara abrir la game. Si no, vuelve al menu principal.

	if (error == 0) {
		DrawTable(sk);
	} else if (error == -1) {
		DrawTable(sk);
		return error;
	}

	if (sk->spaces == 0)
		return -1; // Si un fichero estuviera compuesto completamente por NUMBERs, esto volveria al menu inicial.
	return error;
}

int LoadGame(struct sudoku *sk) // Similar a la funcion anterior, pero inicializa el sudoku con una game de almacenadas.txt
{
	int error = 0;

	do {
		error = ReadTable(sk);
		if (error == 0) {
			printf("There is no saved games.\n\a");
			return error;
		}
	} while (error != 1);

	if (error == 0) {
		DrawTable(sk);
	} else if (error == -1) {
		DrawTable(sk);
		return error;
	}

	if (sk->spaces == 0)
		return -1; // Si un fichero estuviera compuesto completamente por NUMBERs, esto volveria al menu inicial.

	return error;
}

void ShowHeader() // ASCII ART :)
{
	printf(
			"*************************************************************************\n");
	printf(
			"*     /////  //   //  ////     ////    //  //  //   //     (OMG!)       *\n");
	printf(
			"*    //     //   //  // //   //  //   // //   //   //    O              *\n");
	printf(
			"*   /////  //   //  //  //  //   //  /////   //   //    0   ~///        *\n");
	printf(
			"*     //  //   //  //  //  //   //  //  //  //   //      o (O.o)        *\n");
	printf(
			"* /////   /////   /////    /////   //   //  /////   ___o00o_\\./_o00o___ *\n");
	printf(
			"*************************************************************************\n");
	printf("\n\n\n\n\n");
}

int Play(struct sudoku* sk) {

	int error = 0;
	struct coor fc = { DOT, DOT };

	do {
		error = InsertNumber(sk, fc);
		if (error == -1)
			return error; // Si error == -1 EXIT
		if (error == -2) {
			SaveTable(*sk);
			return error;
		} // Si error == -2, guarda la game.
		if (error == -3) {
			ChangeInsertedNumber(sk, fc);
			return error;
		} // Si error == -3, modifica un NUMBER.
		if (error == -4) {
			CleanTable(sk);
			return error;
		} // Si error == -4, vuelve el tablero a su estado original.

	} while (error == 1); // Insertar NUMBER mientras haya errores.

	return error;
}

void DrawTable(struct sudoku* sk) //No tiene misterio. Dibuja el tablero e imprime las estadisticas.
{
	int i, j;

	printf("\t\t\t  |1 2 3|4 5 6|7 8 9|\n");
	for (i = ROW_MIN; i <= ROW_MAX; i++) {

		if ((i - CHAR) % ROWS == 0 || (i - CHAR) % ROWS == 3
				|| (i - CHAR) % ROWS == 6) {
			printf("\t\t\t- |- - -|- - -|- - -|\n");
		}
		printf("\t\t\t%c ", i);
		for (j = COLUMN_MIN; j <= COLUMN_MAX; j++) {

			if ((j - INT) % COLUMNS == 0 || (j - INT) % COLUMNS == 3
					|| (j - INT) % COLUMNS == 6) {
				printf("|");
			}
			printf("%c", sk->panel[i - CHAR][j - INT]);

			if ((j - INT) % COLUMNS != 2 && (j - INT) % COLUMNS != 5
					&& (j - INT) % COLUMNS != 8) {
				printf("-");
			}
		}

		printf("|\n");
	}
	printf("\t\t\t- |- - -|- - -|- - -|\n\n");
	printf(
			"\tNumbers:   %s \tTotal empty dots:   %d \n\tPercentage of grid completed:\t%.3f%%\n",
			sk->game, sk->spaces, 100.0 - ((float) sk->spaces * 100 / (CELLS)));

}

int ReadTable(struct sudoku* sk) // Abre games de sudokus (puzzles.txt o almacenadas.txt) e inicializa el juego.
{
	int i, j, error;
	char extension[L_EXTENSION + 1] = ".txt";
	FILE *game = NULL;

	sk->spaces = 0;

	strcat(sk->game, extension);
	printf("game: %s\n", sk->game);
	game = fopen(sk->game, "r");

	if (game == NULL) {
		printf("ERROR READING game.txt FILE.\n"
				"Check if saved games are in the executable directory.\n\a");
		error = 0;
	} else {
		for (i = 0; i < ROWS; i++) {
			for (j = 0; j < COLUMNS; j++) {
				fscanf(game, "\n%c", &sk->panel[i][j]); // En este bucle se inicializa el sudoku
				if (sk->panel[i][j] == DOT)
					sk->spaces++; // y se actualiza el NUMBER de espacios.
			}
		}
		error = 1;
		fclose(game);
	}
	return error;
}
int CheckCoords(char *coord) {
	int error = 1;

//Comprueba si las coordenadas son correctas. Si son "Coordenadas-Comando" las identifica y hace lo que corresponda.

	if (coord[0] == 'S' && coord[1] == 'A') {
		printf("You have choosed to EXIT the game.\n");
		error = -1;
		return error;
	}
	if (coord[0] == 'G' && coord[1] == 'P') {
		printf("You have choosed to SAVE the game.\n");
		error = -2;
		return error;
	}
	if (coord[0] == 'C' && coord[1] == 'N') {
		printf("You have choosed to Change Number.\n");
		error = -3;
		return error;
	}
	if (coord[0] == 'L' && coord[1] == 'T') {
		printf("You have choosed to Clean Table.\n");
		error = -4;
		return error;
	}
	if (strlen(coord) != 2) {
		printf(
				"MUST WRITE IN PROPER FORMAT (LN [ROWCOLUMN, without spaces and in the permitted range]).\n\a");
		error = 0;
	}
	if ((coord[0] < ROW_MIN) || (coord[0] > ROW_MAX)) {
		printf("You have entered a invalid option!(ROW = %c)\n\a", coord[0]);
		error = 0;
	}

	if ((coord[1] < COLUMN_MIN) || (coord[1] > COLUMN_MAX)) {
		printf("You have entered a invalid opcion!(COLUMN = %c)\n\a", coord[1]);
		error = 0;
	}

	return error;
}
int IsDotEmpty(struct sudoku sk, struct coor fc) {
	int error;

	if ((sk.panel[fc.row - CHAR][fc.column - INT] == DOT)
			&& (fc.row >= ROW_MIN && fc.column <= COLUMN_MAX)
			&& (fc.column >= COLUMN_MIN && fc.column <= COLUMN_MAX)) {
		error = 1;
	} else {
		printf("That cell is filled already with a number. Choose other.\n\a");
		error = 0;
	}

	return error;
}
int CheckNumber(char * num) {
	int error;

	if ((*num >= MIN_NUMBER && *num <= MAX_NUMBER)) {
		error = 1;
	} else {
		printf("You have entered a invalid option!(NUMBER = %c)\n\a", *num);
		error = 0;
	}
	return error;
}

int ChangeNumber(char * num) {
	int error;

	if ((*num >= MIN_NUMBER && *num <= MAX_NUMBER) || *num == DOT) {
		error = 1;
	} else {
		printf("You have entered a invalid option !(NUMBER = %c)\n\a", *num);
		error = 0;
	}

	return error;
}

int InsertNumber(struct sudoku* sk, struct coor fc) {
//Inserta un NUMBER si las coordenadas son correctas y no hay un NUMBER ya introducido en ellas.
	int error = 0;
	char coord[MAX_BUFFER];
	char num;

	do {
		while (error == 0) {
			DrawTable(sk); //
			if (sk->spaces <= 0) {
				printf("\nGRID COMPLETED!!!\n\a");
				return -1;
			}
			printf(
					"\nOptions: CN=ChangeNumber LT=LooseTable GP=SaveGame SA=EXIT\n\n");
			printf("Enter ROW A-I and COLUMN 1-9 (RC FORMAT).\t");
			scanf("\n%s", coord);
			fflush(stdin);
			fc.row = coord[0];
			fc.column = coord[1];

			error = CheckCoords(coord);

			if (error == -1 || error == -2 || error == -3 || error == -4)
				return error;

		}
		error = IsDotEmpty(*sk, fc);
	} while (error != 1);

	do {
		printf("Now input 1-9 value... (C=Cancel)\t");
		scanf("\n%c", &num);
		fflush(stdin);
		if (num == 'C') {
			printf("\nCanceled. \n\a");
			return 0;
		} // 'C' Cancela la introduccion del NUMBER, vuelve a pedir coordenadas.
		error = CheckNumber(&num);
		if (error == 1)
			error = IsNumberValid(*sk, coord, &num);

	} while (error == 0);

	sk->panel[fc.row - CHAR][fc.column - INT] = num;
	printf("\nYou have chosen:\n\n");
	printf("ROW:%c\n", fc.row);
	printf("COLUMN:%c\n", fc.column);
	printf("NUMBER:%c\n", num);
	printf("\n");
	if (sk->panel[fc.row - CHAR][fc.column - INT] != DOT)
		sk->spaces--;
	else
		sk->spaces++;

	return error;
}

int SaveTable(struct sudoku sk) {
	int i, j, error;
	FILE *saved = NULL;
	char game[MAX_BUFFER];

	printf("Enter the name of the game: \n");
	scanf("\n%s", game);
	fflush(stdin);

	SaveGame(game); // Primero guarda el nombre en almacenadas.txt.

	strcat(game, ".txt");
	saved = fopen(game, "w"); // Abre la game.txt como escritura.

	if (saved == NULL) {
		printf("ERROR OPENING game.txt FILE.\n\a");
		error = 0;
	} else {
		for (i = 0; i < ROWS; i++) {
			for (j = 0; j < COLUMNS; j++) {
				fprintf(saved, "%c", sk.panel[i][j]); //Luego guarda la matriz en el fichero.
			}
			fprintf(saved, "\n");
		}
		error = 1;
		fclose(saved);
	}
	return error;
}

int IsNumberValid(struct sudoku sk, char coord[], char * num) {
	int error = 1;
	char f, ROW = coord[0];
	char c, COLUMN = coord[1];
	char sub_table[MAX_SUB_TABLE];

	for (f = ROW_MIN; f <= ROW_MAX; f++) // Comprueba que num no este repetido en las COLUMNS.
			{

		if (sk.panel[f - CHAR][COLUMN - INT] == *num && *num != DOT) {
			printf("That NUMBER is already present on that COLUMN!.\n\a");
			error = 0;
		}

	}

	for (c = COLUMN_MIN; c <= COLUMN_MAX; c++) // Comprueba que num no este repetido en las ROWS.
			{

		if (sk.panel[ROW - CHAR][c - INT] == *num && *num != DOT) {
			printf("That NUMBER is already present on that ROW!.\n\a");
			error = 0;
		}

	}

	sub_table[0] = coord[0];
	sub_table[1] = coord[1];

	//Localizamos el subcuadrante al que pertenecen las coordenadas.
	if (((int) (ROW - CHAR) % 9 == 0) || ((int) (ROW - CHAR) % 9 == 1)
			|| ((int) (ROW - CHAR) % 9 == 2))
		sub_table[0] = 'A';
	if (((int) (ROW - CHAR) % 9 == 3) || ((int) (ROW - CHAR) % 9 == 4)
			|| ((int) (ROW - CHAR) % 9 == 5))
		sub_table[0] = 'D';
	if (((int) (ROW - CHAR) % 9 == 6) || ((int) (ROW - CHAR) % 9 == 7)
			|| ((int) (ROW - CHAR) % 9 == 8))
		sub_table[0] = 'G';

	if (((int) (COLUMN - INT) % 9 == 0) || ((int) (COLUMN - INT) % 9 == 1)
			|| ((int) (COLUMN - INT) % 9 == 2))
		sub_table[1] = '1';
	if (((int) (COLUMN - INT) % 9 == 3) || ((int) (COLUMN - INT) % 9 == 4)
			|| ((int) (COLUMN - INT) % 9 == 5))
		sub_table[1] = '4';
	if (((int) (COLUMN - INT) % 9 == 6) || ((int) (COLUMN - INT) % 9 == 7)
			|| ((int) (COLUMN - INT) % 9 == 8))
		sub_table[1] = '7';

	for (f = (sub_table[0] - CHAR); f <= (sub_table[0] - CHAR) + 2; f++) // Comparamos num con los NUMBERs del subcuadrante.
			{
		for (c = (sub_table[1] - INT); c <= (sub_table[1] - INT) + 2; c++) {
			if (sk.panel[(int) f][(int) c] == *num && *num != DOT) {
				printf(
						"That NUMBER is already present on that SUB TABLE!.\n\a");
				error = 0;
			}
		}
	}
	return error;
}

int LoadSavedGames(struct sudoku* sk) {
	int error = -1;
	char game[L_NAME];
	FILE *saved = NULL;

	saved = fopen("savedgames.txt", "r");

	if (saved == NULL) {
		printf("ERROR OPENING \"savedgames.txt\".\n"
				"Check if saved games are in the executable directory.\n\a");
		error = 0;
	} else {

		do {
			printf("\n\nThese are the saved games: \n\n");
			rewind(saved);
			while (!feof(saved)) // Muestra los nombres de game guardadas en almacenadas.txt. SIEMPRE APARECE EL ULTIMO NOMBRE DOS VECES!!??
			{

				fscanf(saved, "\n%s", game);
				fflush(stdin);
				if (fscanf(saved, "\EOF", game))
					break;
				printf("\t%s", game);
				printf("\n");
			}

			printf("\nEnter saved game (8 character string):\t");

			scanf("\n%s", sk->game);
			fflush(stdin);

			rewind(saved);

			while (!feof(saved)) // Compara que la game que introducimos exista en almacenadas.txt.
			{
				fscanf(saved, "\n%s", game);
				fflush(stdin);
				if (!strcmp(game, sk->game)) {
					error = 1;
				}

			}

		} while (error == -1);
		fclose(saved);
	}
	return error;
}

int SaveGame(char game[]) {
	int error;
	FILE *indice = NULL;
	indice = fopen("savedgames.txt", "a"); //Abre almacenadas.txt en modo 'append' para ir añadiendo nombres de games al final del fichero.

	if (indice == NULL) {
		printf("ERROR OPENING SAVED GAMES FILE .\n\a");
		error = 0;
	} else {
		fprintf(indice, "%s\n", game);
		fclose(indice);
		error = 1;
	}
	return error;
}

int ChangeInsertedNumber(struct sudoku* sk, struct coor fc) {

	int error = 0;
	char coord[MAX_BUFFER];
	char num;

	//Identica a InsertNumber() solo que en lugar de dejar escribir en los DOTs, escribe en los NUMBERs ya escritos.

	do {
		while (error == 0) {
			DrawTable(sk); //
			if (sk->spaces <= 0) {
				printf("\nGRID COMPLETED!!!\n");
				return -1;
			}
			printf(
					"\nOptions: CN=ChangeNumber LT=LooseTable GP=SaveGame SA=EXIT\n\n");
			printf("Enter ROW A-I and COLUMN 1-9 (RC FORMAT).\t");
			scanf("\n%s", coord);
			fflush(stdin);
			fc.row = coord[0];
			fc.column = coord[1];

			error = CheckCoords(coord);
			if (error == -1 || error == -2 || error == -3 || error == -4)
				return error;

		}
		error = IsDotEmpty(*sk, fc);
	} while (error != 1);

	do {
		printf("Now input 1-9 value... (C=Cancel)\t");
		scanf("\n%c", &num);
		fflush(stdin);
		if (num == 'C') {
			printf("\nCanceled. \n\a");
			return 0;
		} // 'C' Cancela la introduccion del NUMBER, vuelve a pedir coordenadas.
		error = ChangeNumber(&num);
		if (error == 1)
			error = IsNumberValid(*sk, coord, &num);

	} while (error == 0);

	sk->panel[fc.row - CHAR][fc.column - INT] = num;
	printf("\nYou have chosen:\n\n");
	printf("ROW:%c\n", fc.row);
	printf("COLUMN:%c\n", fc.column);
	printf("NUMBER:%c\n", num);
	printf("\n");
	if (sk->panel[fc.row - CHAR][fc.column - INT] != DOT)
		sk->spaces--;
	else
		sk->spaces++;

	return error;
}

int IsBoxFull(struct sudoku sk, struct coor fc) {
	int error;
	if ((sk.panel[fc.row - CHAR][fc.column - INT] != DOT)
			&& (fc.row >= ROW_MIN && fc.column <= COLUMN_MAX)
			&& (fc.column >= COLUMN_MIN && fc.column <= COLUMN_MAX)) {
		error = 1;
	}

	else {
		printf("That cell is already empty. Choose another.\n\a");

		error = 0;

	}

	return error;
}
int CleanTable(struct sudoku* sk) {
	int i, j, error;
	FILE *game = NULL;

	sk->spaces = 0;

	game = fopen(sk->game, "r"); //Abre la game en curso de nuevo.

	if (game == NULL) {
		printf("ERROR READING game.txt FILE.\n .\n\a");
		error = 0;
	} else {
		for (i = 0; i < ROWS; i++) {
			for (j = 0; j < COLUMNS; j++) {
				fscanf(game, "\n%c", &sk->panel[i][j]); // Reinicializa el juego.
				if (sk->panel[i][j] == DOT)
					sk->spaces++;
			}
		}
		error = 1;
		fclose(game);
	}

	return error;
}

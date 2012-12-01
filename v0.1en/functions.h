#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#define ROWS 9
#define COLUMNS 9
#define CELLS ROWS*COLUMNS
#define L_TOTAL L_NAME + L_EXTENSION
#define L_NAME 9
#define L_EXTENSION 4
#define MIN_NUMBER '1'
#define MAX_NUMBER '9'
#define DOT '.'
#define MAX_BUFFER 256
#define ROW_MIN 'A'
#define ROW_MAX 'I'
#define COLUMN_MIN '1'
#define COLUMN_MAX '9'
#define CHAR 65 //diferencia de 'A' a 0
#define INT 49 //diferencia de '1' a 0
#define PLAY '1'
#define LOAD '2'
#define EXIT '3'
#define MAX_SUB_TABLE 3

struct sudoku {
	char panel[ROWS + 1][COLUMNS + 1];
	char game[L_TOTAL + 1];
	int spaces;

} sk;

struct coor {
	char row;
	char column;
} fc;

int Selection(); // Muestra el menu de seleccion. Devuelve la seleccion.
int LoadPuzzleIndex(struct sudoku* sk); // Lee las partidas de puzzles.txt.
int LoadSavedGames(struct sudoku* sk); // Lee las partidas de almacenadas.txt.
int StartGame(struct sudoku* sk); // Empieza una partida nueva (a partir de un puzzle de puzzles.txt).
void ShowHeader(); // Muestra la cabecera.
int Play(struct sudoku* sk); // Llama a insertar numero, cuyo retorno puede llamar a otras funciones.
void DrawTable(struct sudoku* sk); // Dibuja el tablero e imprime informacion (huecos, porcentajes, etc...).
int ReadTable(struct sudoku* sk); // Lee el archivo elegido de puzzles.txt.
int CleanTable(struct sudoku* sk); // Vuelve a inicializar la matrix con el archivo para volverla a su estado original.
int CheckCoords(char *coord); // Comprueba si las coordenadas son correctas
int IsDotEmpty(struct sudoku sk, struct coor fc); // Comprueba si la casilla esta vacia
int CheckNumber(char * num); // Comprueba si el numero introducido es valido.
int ChangeNumber(char * num); // Cambia un numero una vez validado que es un numero y no un punto.
int InsertNumber(struct sudoku* sk, struct coor fc); //Inserta un numero en el tablero (haciendo las comprobaciones).
int SaveTable(struct sudoku sk); // Guarda el estado del sudoku en un archivo .txt
int SaveGame(char partida[]); // Guarda el nombre del archivo anterior en almacenadas.txt.
int LoadGame(struct sudoku *sk); // Inicializa el sudoku a partir de la partida seleccionada de almacenadas.txt.
int IsNumberValid(struct sudoku sk, char coord[], char * num); //Comprueba si un numero es valido.
int IsDotFilled(struct sudoku sk, struct coor fc); //Comprueba si una casilla esta llena.
int ChangeInsertedNumber(struct sudoku* sk, struct coor fc); // Similar a insertar numero, solo que permite modificar los que ya se han introducido.

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#define FILAS 9
#define COLUMNAS 9
#define CASILLAS FILAS*COLUMNAS
#define L_TOTAL L_NOMBRE+L_EXTENSION
#define L_NOMBRE 9
#define L_EXTENSION 4
#define MIN_NUMERO '1'
#define MAX_NUMERO '9'
#define PUNTO '.'
#define MAX_BUFFER 256
#define MIN_FILA 'A'
#define MAX_FILA 'I'
#define MIN_COLUMNA '1'
#define MAX_COLUMNA '9'
#define CHAR 65 //diferencia de 'A' a 0
#define INT 49 //diferencia de '1' a 0
#define JUGAR '1'
#define CARGAR '2'
#define SALIR '3'
#define MAX_SUBCUADRANTE 3

struct sudoku {
	char panel[FILAS + 1][COLUMNAS + 1];
	char partida[L_TOTAL + 1];
	int espacios;

} sk;

struct coor {
	char fila;
	char columna;
} fc;

int Seleccion(); // Muestra el menu de seleccion. Devuelve la seleccion.
int LeerPartidas(struct sudoku* sk); // Lee las partidas de puzzles.txt.
int LeerPartidasGuardadas(struct sudoku* sk); // Lee las partidas de almacenadas.txt.
int EmpezarPartida(struct sudoku* sk); // Empieza una partida nueva (a partir de un puzzle de puzzles.txt).
void MuestraCabecera(); // Muestra la cabecera.
int Jugar(struct sudoku* sk); // Llama a insertar numero, cuyo retorno puede llamar a otras funciones.
void DibujarTablero(struct sudoku* sk); // Dibuja el tablero e imprime informacion (huecos, porcentajes, etc...).
int LeeTablero(struct sudoku* sk); // Lee el archivo elegido de puzzles.txt.
int LimpiaTablero(struct sudoku* sk); // Vuelve a inicializar la matrix con el archivo para volverla a su estado original.
int CompruebaCoordenadas(char *coord); // Comprueba si las coordenadas son correctas
int CasillaVacia(struct sudoku sk, struct coor fc); // Comprueba si la casilla esta vacia
int CompruebaNumero(char * num); // Comprueba si el numero introducido es valido.
int CambiaNumero(char * num); // Cambia un numero una vez validado que es un numero y no un punto.
int InsertaNumero(struct sudoku* sk, struct coor fc); //Inserta un numero en el tablero (haciendo las comprobaciones).
int GuardaTablero(struct sudoku sk); // Guarda el estado del sudoku en un archivo .txt
int GuardaPartida(char partida[]); // Guarda el nombre del archivo anterior en almacenadas.txt.
int CargarPartida(struct sudoku *sk); // Inicializa el sudoku a partir de la partida seleccionada de almacenadas.txt.
int NumeroValido(struct sudoku sk, char coord[], char * num); //Comprueba si un numero es valido.
int CasillaLlena(struct sudoku sk, struct coor fc); //Comprueba si una casilla esta llena.
int ModificaNumero(struct sudoku* sk, struct coor fc); // Similar a insertar numero, solo que permite modificar los que ya se han introducido.

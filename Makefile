all : sudoku.exe
sudoku.exe : main.o funciones.o
	gcc main.o funciones.o -o sudoku.exe   	
main.o : main.c funciones.c funciones.h
	gcc -c main.c
funciones.o : funciones.c funciones.h
	gcc -c funciones.c
clean :
	rm *.o



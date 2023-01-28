C = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = game.o gstruct.o grids.o inout.o random.o newSleep.o color.o
EXEC = ant

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

game.o : game.c game.h gstruct.h grids.h inout.h random.h newSleep.h macros.h
	gcc -c game.c $(CFLAGS)

gstruct.o :	gstruct.c gstruct.h macros.h
	gcc -c gstruct.c $(CFLAGS)

grids.o : grids.c grids.h macros.h
	gcc -c grids.c $(CFLAGS)

inout.o : inout.c inout.h macros.h
	gcc -c inout.c $(CFLAGS)

newSleep.o : newSleep.c newSleep.h
	gcc -c newSleep.c $(CFLAGS)

random.o : random.c random.h
	gcc -c random.c $(CFLAGS)

color.o : color.c color.h macros.h
	gcc -c color.c $(CFLAGS)

clean : 
	rm -f $(EXEC) $(OBJ)


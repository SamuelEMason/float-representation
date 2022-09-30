CFLAG = -Wall -g -3O -pedantic
CC = gcc


float: main.o
	$(CC) main.o -o float

main.o: float.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o *.so *.dll *.exe

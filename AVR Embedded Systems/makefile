CC=gcc
CFLAGS=-I.
lab2.o: lab2.c
    $(CC) -c -o lab2.o lab2.c
lab2: lab2.o
    $(CC) -o lab2 lab2.o -lrt
.PHONY: clean
clean:
    rm -f lab2.o lab2
.PHONY : all

all : main

main : main.c strings.o support.o
	gcc main.c strings.o support.o -o bin/main -Wall

strings.o : strings.c support.o strings.h
	gcc -c strings.c

support.o : support.c support.h
	gcc -c support.c


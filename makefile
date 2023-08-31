.PHONY : all

all : main

main : main.c strings.o support.o stack.o charIs.o dynArr.o  
	gcc main.c strings.o support.o dynArr.o stack.o charIs.o -o bin/main -Wall

strings.o : strings.c support.o charIs.o strings.h
	gcc -c strings.c -Wall

support.o : support.c support.h
	gcc -c support.c -Wall

dynArr.o : dynArr.c dynArr.h
	gcc -c dynArr.c  -Wall

charIs.o : charIs.c charIs.h
	gcc -c charIs.c -Wall

stack.o : stack.c support.o
	gcc -c stack.c

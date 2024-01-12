.PHONY : all clean

objects = strings.o support.o stack.o dynArr.o

IN = $(wildcard test/*-input.txt)
PASS = $(IN:-input.txt=.passed)

all : main

main : main.c strings.o support.o stack.o dynArr.o  
	if ! [ -d bin ]; then mkdir bin; fi
	gcc main.c strings.o support.o dynArr.o stack.o -o bin/main  -Wall 

strings.o : strings.c support.o stack.o strings.h
	gcc -c strings.c -Wall 

support.o : support.c support.h
	gcc -c support.c -Wall

dynArr.o : dynArr.c dynArr.h
	gcc -c dynArr.c  -Wall

stack.o : stack.c support.o
	gcc -c stack.c

clean : 
	rm -f $(objects)

test : main $(PASS) 

$(PASS) : %.passed: %-input.txt %-expected.txt bin/main
	echo "Running test $*..."
	rm -f $@
	bin/main $*-input.txt $*-actual.txt
	diff $*-expected.txt $*-actual.txt
	touch $@

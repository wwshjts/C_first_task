.PHONY : all clean allocator

objects = strings.o support.o stack.o dynArr.o

IN = $(wildcard test/*-input.txt)
PASS = $(IN:-input.txt=.passed)


all : main 

main : main.c strings.o support.o stack.o dynArr.o  
	if ! [ -d bin ]; then mkdir bin; fi
	gcc main.c strings.o support.o dynArr.o stack.o -o bin/main -Wall 
	make clean

checked : main.c strings.o support.o stack.o dynArr.o  
	if ! [ -d bin ]; then mkdir bin; fi
	gcc main.c strings.o support.o dynArr.o stack.o -o bin/main -Wall -fsanitize=address 
	make clean

strings.o : strings.c support.o stack.o strings.h
	gcc -c strings.c -Wall 

support.o : support.c support.h
	gcc -c support.c -Wall

dynArr.o : dynArr.c dynArr.h
	gcc -c dynArr.c  -Wall

stack.o : stack.c support.o
	gcc -c stack.c

allocator.o : allocator.c allocator.h linked_list.o types.h
	gcc -c allocator.c linked_list.o

linked_list.o : linked_list.c linked_list.h types.h 
	gcc -c linked_list.c 

clean : 
	rm -f $(objects)

test : checked $(PASS) 

$(PASS) : %.passed: %-input.txt %-expected.txt bin/main
	echo "Running test $*..."
	rm -f $@
	bin/main $*-input.txt $*-actual.txt
	diff $*-expected.txt $*-actual.txt
	touch $@

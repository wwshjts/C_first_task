.PHONY : all clean 

objects = strings.o support.o stack.o dynArr.o allocator.o linked_list.o

IN = $(wildcard test/*-input.txt)
PASS = $(IN:-input.txt=.passed)

options = -fsanitize=address -fsanitize=undefined -fsanitize=leak


all : main 

main : main.c $(objects) 
	if ! [ -d bin ]; then mkdir bin; fi
	gcc main.c $(objects) -o bin/main -Wall $(options)
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
	gcc -c allocator.c 

linked_list.o : linked_list.c linked_list.h types.h 
	gcc -c linked_list.c 

clean : 
	rm -f $(objects)

test : main $(PASS) 

$(PASS) : %.passed: %-input.txt %-expected.txt bin/main
	echo "Running test $*..."
	rm -f $@
	bin/main $*-input.txt $*-actual.txt
	diff $*-expected.txt $*-actual.txt
	touch $@

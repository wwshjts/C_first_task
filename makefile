.PHONY : all clean

objects = strings.o support.o stack.o dynArr.o list_allocator.o
alloc_src = allocator/

IN = $(wildcard test/*-input.txt)
PASS = $(IN:-input.txt=.passed)

all : main

main : main.c strings.o support.o stack.o dynArr.o  list_allocator.o
	gcc main.c list_allocator.o strings.o support.o dynArr.o stack.o -o bin/main allocator/ptrList.o -Wall

strings.o : strings.c support.o stack.o strings.h
	gcc -c strings.c -Wall

support.o : support.c support.h
	gcc -c support.c -Wall

dynArr.o : dynArr.c list_allocator.o dynArr.h
	gcc -c dynArr.c  -Wall

stack.o : stack.c support.o
	gcc -c stack.c

list_allocator.o : $(addprefix $(alloc_src), ptrList.o list_allocator.c list_allocator.h)
	gcc -c allocator/list_allocator.c 

allocator/ptrList.o : $(addprefix $(alloc_src), ptrList.c linked_list_generate_code.h linked_list_generate_header.h ptrList.h)
	gcc -c allocator/ptrList.c -o allocator/ptrList.o

clean : 
	rm -f $(objects)

test : main $(PASS) 

$(PASS) : %.passed: %-input.txt %-expected.txt bin/main
	echo "Running test $*..."
	rm -f $@
	bin/main $*-input.txt $*-actual.txt
	diff $*-expected.txt $*-actual.txt
	touch $@

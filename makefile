# VARIABLES
CC = gcc
FLAGS = -Wall -pedantic -g
TEST = -lcunit
VALTEST = valgrind --leak-check=full

# ALL FILES
all: freq_count hash_table hash_test hash_valgrind list_linked iterator list_test list_valgrind

# C. FILES
freq-count: freq-count.c hash_table.o list_linked.o iterator.o
	$(CC) $(FLAGS) -pg -o freq-count freq-count.c hash_table.o list_linked.o iterator.o

hash_table: hash_table.c list_linked.c
	$(CC) $(FLAGS) -std=c11 -o hash_table hash_table.c

list_linked: list_linked.c
	$(CC) $(FLAGS) -std=c11 -o list_linked list_linked.c

iterator: iterator.c
	$(CC) $(FLAGS) -std=c11 -o iterator iterator.c

# TESTFILES
hash_test: hash_test.c hash_table.o list_linked.o iterator.o
	$(CC) $(FLAGS) -std=c11 -o $@ $< hash_table.o list_linked.o iterator.o $(TEST)
	./$@

list_test: list_test.c list_linked.o iterator.o
	$(CC) $(FLAGS) -std=c11 -o $@ $< list_linked.o iterator.o $(TEST)               
	./$@

# VALGRIND
hash_valgrind: hash_test
	$(VALTEST) ./hash_test

list_valgrind: list_test
	$(VALTEST) ./list_test

# OBJECTFILES
hash_table.o: hash_table.c hash_table.h common.h
	$(CC) $(FLAGS) -std=c11 -c $<

list_linked.o: list_linked.c list_linked.h 
	$(CC) $(FLAGS) -std=c11 -c $<

iterator.o: iterator.c iterator.h 
	$(CC) $(FLAGS) -std=c11 -c $<

# CLEAN 
clean:
	rm -f freq_count hash_table hash_test hash_valgrind list_linked iterator list_test list_valgrind
	rm -f *~

.PHONY: hash_test list_test clean

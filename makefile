clean:
	rm -f ./*~
	rm -f ./*#

prog: hash_table.c
	gcc -pedantic -Wall -g hash_table.c -c -o hash_table

runtest: prog
	gcc -ggdb -Wall -std=c11 ioopm_hash_test.c hash_table.c -lcunit -o tester

valtest: runtest
	valgrind --leak-check=full ./tester

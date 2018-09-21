prog: hash_table.c
	gcc -pedantic -Wall -g hash_table.c -c -o hash_table

valinlupp: hash_table.c
	valgrind --tool=memcheck ./hash_table

runtest: ioopm_hash_test.c
	gcc -ggdb -Wall -std=c11 ioopm_hash_test.c hash_table.c -lcunit -o tester

valtest: inlupp1.c
	valgrind --tool=memcheck ./tester

clean:
	rm -f ./*~
	rm -f ./*#

prog: hash_table.c
	gcc -pedantic -Wall -g hash_table.c -c -o hash_table

runtest: prog
	gcc -ggdb -Wall -std=c11 ioopm_hash_test.c hash_table.c list_linked.c -lcunit -o tester

valtest: runtest
	valgrind --leak-check=full ./tester

prog2: list_linked.c
	gcc -pedantic -Wall -g list_linked.c -c -o linked_list

runtest2: prog2
	gcc -ggdb -Wall -std=c11 ioopm_list_linked_test.c list_linked.c -lcunit -o tester2

valtest2: runtest2
	valgrind --leak-check=full ./tester2

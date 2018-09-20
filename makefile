prog: inlupp1.c
	gcc -pedantic -Wall -g inlupp1.c -lcunit -o inlupp1

memtest: inlupp1.c
	valgrind --tool=memcheck ./inlupp1

tester: ioopm_hash_test.c
	gcc -ggdb -Wall -std=c11 ioopm_hash_test.c inlupp1.c -lcunit -o tester

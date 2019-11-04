#makefile

testme: testme.c
	gcc testme.c -g -o testme -ftest-coverage -fprofile-arcs -std=c99

gcov: testme.c
	gcov testme.c
	
clean:
	rm -f *.o testme
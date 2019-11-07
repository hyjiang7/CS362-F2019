CFLAGS= -Wall -ftest-coverage -fprofile-arcs -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

updateCoinsTest: updateCoinsTest.c dominion.o rngs.o
	gcc -o updateCoinsTest -g  updateCoinsTest.c dominion.o rngs.o -ftest-coverage -fprofile-arcs

unittest1: unittest1.c dominion.o rngs.o 
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o -ftest-coverage -fprofile-arcs

unittest2: unittest2.c dominion.o rngs.o 
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o -ftest-coverage -fprofile-arcs

unittest3: unittest3.c dominion.o rngs.o 
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o -ftest-coverage -fprofile-arcs

unittest4: unittest4.c dominion.o rngs.o 
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o -ftest-coverage -fprofile-arcs

unittest5: unittest5.c dominion.o rngs.o 
	gcc -o unittest5 -g unittest5.c dominion.o rngs.o -ftest-coverage -fprofile-arcs

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5
	./unittest1 1> unittestresults.out
	./unittest2 1>> unittestresults.out
	./unittest3 1>> unittestresults.out
	./unittest4 1>> unittestresults.out
	./unittest5 1>> unittestresults.out
	gcov dominion.c -b -f 1>> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

cardFunctions.o: cardFunctions.h cardFunctions.c
	gcc -c cardFunctions.c -g $(CFLAGS)

playdom: dominion.o playdom.c cardFunctions.o
	gcc -o playdom playdom.c -g dominion.o rngs.o cardFunctions.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o cardFunctions.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o cardFunctions.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittest5: unittest5.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest5 -g  unittest5.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o cardFunctions.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o cardFunctions.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

randomtestcard3: randomtestcard3.c dominion.o rngs.o cardFunctions.o
	gcc -o randomtestcard3 -g  randomtestcard3.c dominion.o rngs.o cardFunctions.o $(CFLAGS)


testresults: unittest1 unittest2 unittest3 unittest4 unittest5 randomtestcard1 randomtestcard2 randomtestcard3
	./unittest1 1> testresults.out
	./unittest2 >> testresults.out
	./unittest3 >> testresults.out
	./unittest4 >> testresults.out
	./unittest5 >> testresults.out
	gcov cardFunctions.c -b -f >> testresults.out
	./randomtestcard1 >> testresults.out
	./randomtestcard2 >> testresults.out
	./randomtestcard3 >> testresults.out
	gcov cardFunctions.c -b -f >> testresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

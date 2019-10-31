CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion_helpers.o: dominion_helpers.h dominion_helpers.c
	gcc -c dominion_helpers.c -g  $(CFLAGS)

dominion.o: rngs.o dominion_helpers.o dominion.h dominion.c 
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o dominion_helpers.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o dominion_helpers.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o dominion_helpers.o $(CFLAGS)

all: playdom player 


unittest1: unittest1.c unittest2.c dominion.o rngs.o
	gcc -o unittest1 unittest 2 -g  unittest1.c unittest2.c dominion.o rngs.o dominion_helpers.o $(CFLAGS)

rununittests: unittest2 
	./unittest1 &> unittestresult.out
	./unittest2 &> unittestresult.out
	gcov dominion_helpers.c >> unittestresult.out
	cat dominion_helpers.c.gcov >> unittestresult.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

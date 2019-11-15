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

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o dominion_helpers.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o dominion_helpers.o $(CFLAGS)

# unittest3: unittest3.c dominion.o rngs.o
# 	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o dominion_helpers.o $(CFLAGS)

# unittest4: unittest4.c dominion.o rngs.o
# 	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o dominion_helpers.o $(CFLAGS)

# unittest5: unittest5.c dominion.o rngs.o
# 	gcc -o unittest5 -g  unittest5.c dominion.o rngs.o dominion_helpers.o $(CFLAGS)

runrandomtests: randomtestcard1 randomtestcard2
	./randomtestcard1
	./randomtestcard2
	gcov -b -f dominion_helpers.c > randomtestresult.out
	cat dominion_helpers.c.gcov >> randomtestresult.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestcard1 randomtestcard2
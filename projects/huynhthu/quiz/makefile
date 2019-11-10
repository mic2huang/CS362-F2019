CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)

runtest: testme
	-./testme
	gcov testme.c -b -f > testresult.out
	cat testme.c.gcov >> testresult.out

clean:
	rm -f *.o testme *.gcov *.gcda *.gcno *.so *.out
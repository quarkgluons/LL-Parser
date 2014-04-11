exec: ll.o readFile.o firstSet.o follow.o
	gcc -Wall -g  readFile.o ll.o firstSet.o follow.o -o executable 


compile: ll.c readFile.c first.c follow.c
	gcc -c -g  ll.c readFile.c firstSet.c follow.c


clean:
	rm *.o executable

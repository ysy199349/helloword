a: a.o
	gcc a.o -o a
a.o: a.c
	gcc -c a.c -o a.o
clean:
	rm -rf a a.o

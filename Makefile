
final:
	gcc -c -fpic -std=c99 hw2.c
	gcc -shared -o libmem.so hw2.o
	gcc main.c -lmem -L. -o main
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
	./main
CC = gcc

main.o: FORCE
	

clean:
	rm *.o

FORCE:
	$(CC) main.c -g shogilib.c -g  utilities.c -g  stacklib.c -g -o main 

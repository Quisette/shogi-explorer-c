CC = gcc

main.o: FORCE
	

clean:
	rm *.o

FORCE:
	$(CC) main.c shogilib.c utilities.c -o main.o && ./main.o

CC = gcc

# clean:
	# rm *.o
main.o:
	$(CC) main.c shogilib.c -o main.o && ./main.o
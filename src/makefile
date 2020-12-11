CC=gcc
EXE=png_vault
BIN_DIR=/usr/bin/local


all: png_vault

png_vault: main.o exit_message.o png_io.o file_io.o bin_conv.o
	$(CC) main.o exit_message.o png_io.o file_io.o bin_conv.o -lpng -o $(EXE)
main.o: main.c
	$(CC) -c main.c
exit_message.o: exit_message.c
	$(CC) -c exit_message.c
png_io.o: png_io.c
	$(CC) -c png_io.c
file_io.o: file_io.c
	gcc -c file_io.c
bin_conv.o: bin_conv.c
	gcc -c bin_conv.c
install: all
	mv $(EXE) $(BIN_DIR)
clean:
	rm *.o $(EXE)

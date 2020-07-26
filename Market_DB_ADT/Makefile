# Compiler
CC = gcc
# Compiler Flags
CFLAGS = -O0 -g3 -Wall -c -fmessage-length=0 -std=c99
# Object File
OBJ = main.o market.o read.o
# Program File (./PROG argvs)
PROG = market

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(OBJ) -o $@

main.o: main.c market.h read.h
	$(CC) $(CFLAGS) -c main.c

market.o: market.c market.h read.h
	$(CC) $(CFLAGS) -c market.c

read.o: read.c read.h
	$(CC) $(CFLAGS) -c read.c

clean:
	rm -rf $(OBJ) $(PROG)
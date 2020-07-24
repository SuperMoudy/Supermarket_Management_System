# Compiler
CC = gcc
# Compiler Flags
CFLAGS = -O0 -g3 -Wall -c -fmessage-length=0 -std=c99
# Object File
OBJ = main.o accounts.o
# Program File (./PROG argvs)
PROG = market

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(OBJ) -o $@

main.o: main.c accounts.h
	$(CC) $(CFLAGS) -c main.c

accounts.o: accounts.c accounts.h
	$(CC) $(CFLAGS) -c accounts.c

clean:
	rm -rf $(OBJ) $(PROG)
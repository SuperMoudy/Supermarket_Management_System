# Compiler
CC = gcc
# Compiler Flags
CFLAGS = -O0 -g3 -Wall -c -fmessage-length=0 -std=c99
# Object File
OBJ = market.o item_list.o
# Program File (./PROG argvs)
PROG = market

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(OBJ) -o $@

market.o: market.c item_list.h
	$(CC) $(CFLAGS) -c market.c

item_list.o: item_list.c item_list.h
	$(CC) $(CFLAGS) -c item_list.c

clean:
	rm -rf $(OBJ) $(PROG)
 ##############################################################################
 # Student Name    : Victor Ageev
 # RMIT Student ID : s3732094
 # COURSE CODE     : CPT220
 #
 # Startup code provided by Paul Miller for use in "Programming in C",
 # study period 4, 2018.
 ##############################################################################

CC=gcc
CFLAGS=-ansi -Wall -pedantic -g
LFLAGS=
TARGETS=picedit

all: $(TARGETS)

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

test: test.o
	$(CC) $(CFLAGS) test.o -o test

command.o: command.c command.h line.h fileio.h
	$(CC) $(CFLAGS) -c command.c

fileio.o: fileio.c fileio.h line.h shared.h
	$(CC) $(CFLAGS) -c fileio.c

helpers.o: helpers.c shared.h
	$(CC) $(CFLAGS) -c helpers.c

line.o: line.c line.h shared.h
	$(CC) $(CFLAGS) -c line.c

main.o: main.h main.c command.h repl.h
	$(CC) $(CFLAGS) -c main.c

repl.o: repl.c repl.h command.h
	$(CC) $(CFLAGS) -c repl.c

picedit: command.o fileio.o helpers.o line.o main.o repl.o
	$(CC) $(CFLAGS) command.o fileio.o helpers.o line.o main.o repl.o -o picedit

.PHONY:clean

clean:
	rm -f *.o picedit

sanitize:CFLAGS+=-fsanitize=address
sanitize:clean all

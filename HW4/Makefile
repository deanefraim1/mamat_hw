CC=gcc
CFLAGS=-g -Wall -std=c99
CCLINK=$(CC)
OBJS=grades.o
RM=rm -rf *.o libgrades.so

libgrades.so: $(OBJS)
	$(CCLINK) -shared grades.o -o libgrades.so -llinked-list -L.

grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -c -fpic grades.c
	
clean:
	$(RM)

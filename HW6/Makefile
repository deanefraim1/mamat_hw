CC=g++
CFLAGS=-g -Wall -std=c++11
CCLINK=$(CC)
OBJS=main.o string.o field.o ip.o port.o
EXEC=firewall.exe
RM=rm -rf *.o *.exe libfirewall.so

$(EXEC): $(OBJS) libfirewall.so
	$(CCLINK) $(OBJS) -o $(EXEC) -L. -lfirewall -L. -linput

main.o: main.cpp string.h ip.h port.h input.h
	$(CC) $(CFLAGS) -c -fpic main.cpp

string.o: string.cpp string.h
	$(CC) $(CFLAGS) -c -fpic string.cpp
	
field.o: field.cpp string.h field.h
	$(CC) $(CFLAGS) -c -fpic field.cpp

ip.o: ip.cpp ip.h string.h field.h
	$(CC) $(CFLAGS) -c -fpic ip.cpp

port.o: port.cpp port.h string.h field.h
	$(CC) $(CFLAGS) -c -fpic port.cpp
	
libfirewall.so: string.o field.o ip.o port.o
	$(CCLINK) -shared string.o field.o ip.o port.o -o libfirewall.so

clean:
	$(RM)

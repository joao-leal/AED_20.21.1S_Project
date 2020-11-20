#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS =-Wall -std=c99 -g

#  Sources
SOURCES = aeroportos.c

#  Objects
OBJECTS = aeroportos.o

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

backbone: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

aeroportos.o:  aeroportos.c

clean::
	rm -f *.o core a.out backbone *~

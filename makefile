#   Compiler, Compiler Flags
CC = gcc
CFLAGS1 =-g -Wall
CFLAGS2=-Wall -std=c99 -O3


#   Sources
SOURCES = backbone.c interfaces.c file.c

#   Objects  ('Make' automatically compiles .c to .o)
OBJECTS_A = backbone.o interfaces.o file.o


.c.o:
	$(CC) $(CFLAGS1) -c -o $@ $<

backbone: $(OBJECTS_A)
	$(CC) $(CFLAGS1) -o $@ $(OBJECTS_A)
	
backbone.o: backbone.c defs.h interfaces.h file.h

final :$(OBJECTS_A)
	$(CC) $(CFLAGS2) -o $@ $(OBJECTS_A)

clean:
	rm -f *.o *.~ *.gch

all:
	for F in testes/15_A1/*.routes; do ./backbone $${F} ; done;

diff:
	for F in testes/15_A1/*.bbones; do diff $$F $${F}0; done;

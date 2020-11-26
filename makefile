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

FILES = $(shell ls testes/Enunciado/*.routes0)
OUTPUT = $(shell ls ./primeiro/*.wordz)
TEST = $(shell ls ./primeiro/*.wordz)

all:
	for F in testes/Enunciado/*B0*.routes0; do ./backbone $${F} ; done;

diff:
	for F in testes/Enunciado/*B0*.queries; do diff $$F $${F}0; done;
# prim:
# 	for F in Testes/primeiro*.graph0; do ./wordz Testes/curto.dict $${F} ; done;

# seg:
# 	for F in Testes/segundo*.graph0; do ./wordz Testes/portugues.dict $${F} ; done;

# cach:
# 	for F in Testes/cachimbo*.graph0; do ./wordz Testes/portugues.dict $${F} ; done;

# esp:
# 	for F in Testes/espin*.graph0; do ./wordz Testes/portugues.dict $${F} ; done;

# ama:
# 	for F in Testes/ama*.graph0; do ./wordz Testes/portugues.dict $${F} ; done;
# des:
# 	for F in Testes/desata*.graph0; do ./wordz Testes/portugues.dict $${F} ; done;

# proc:
# 	for F in Testes/processo*.graph0; do ./wordz Testes/portugues.dict $${F} ; done;


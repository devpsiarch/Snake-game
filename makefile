cc = gcc
cflages = -lraylib -lGL -lm -lpthread -ldl -I$(IDIR)

IDIR = ./inc/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c


all: snake

snake:$(SOURCES) inc/headers.h 
	$(cc) $(SOURCES) $(cflages) -o $@ 
run:
	./snake

clean:
	rm snake

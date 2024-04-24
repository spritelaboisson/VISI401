CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lSDL2 -lm

all: maze

maze: visi.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

visi.o: visi.c visi.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o maze


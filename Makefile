CFLAGS=-g -O
LDFLAGS=-pthread

default: all

all: slime_seed 

%.o: %.c
	gcc -c ${CFLAGS} -o $@ $<

slime_chunks.c: slime_chunks.rl
	ragel -G2 -o $@ $<

slime_seed: slime_chunks.o slimes.o slime_algo.o
	gcc ${CFLAGS} ${LDFLAGS} -o $@ $^

clean:
	rm -f slime_seed *.o slime_chunks.c

run:
	time ./slime_seed | head -n 100000 > output.seeds


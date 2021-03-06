CFLAGS=-g -O
LDFLAGS=-pthread

default: all run

all: slime_seed expand48to64random map_slime_chunks 

%.o: %.c
	gcc -c ${CFLAGS} -o $@ $<

slime_chunks.c: slime_chunks.rl
	ragel -G2 -o $@ $<

slime_seed: slime_chunks.o slimes.o slime_algo.o
	gcc ${CFLAGS} ${LDFLAGS} -o $@ $^

expand48to64random: expand48to64random.o slime_algo.o
	 gcc ${CFLAGS} ${LDFLAGS} -o $@ $^

map_slime_chunks: map_slime_chunks.o slime_algo.o
	 gcc ${CFLAGS} ${LDFLAGS} -o $@ $^ -lm

clean:
	rm -f slime_seed map_slime_chunks expand48to64random *.o slime_chunks.c slime_seed.zip *.seeds *.pgm *.png *~

dist: clean slime_chunks.c
	zip slime_seed.zip *

run:
	@echo
	@echo '***' Generating 48-bit suffixes...
	@echo
	./slime_seed | head -n 10000 > output.suffixes
	@echo
	@echo '...' `wc -l output.suffixes | cut -d ' ' -f 1` results
	@echo
	@echo '***' Generating map of slime pattern...
	@echo
	./map_slime_chunks < output.suffixes > map.pgm
	@convert map.pgm map.png || echo "Couldn't convert PGM image to PNG - try loading in an image tool"
	@echo
	@echo '***' Finding likely 64 bit seeds for 48-bit suffixes...
	@echo
	./expand48to64random < output.suffixes | sort -n > likely.seeds


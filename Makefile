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

expand48to64random: expand48to64random.o slime_algo.o
	 gcc ${CFLAGS} ${LDFLAGS} -o $@ $^

clean:
	rm -f slime_seed expand48to64random *.o slime_chunks.c *.seeds

dist: clean slime_chunks.c

run: slime_seed expand48to64random
	@echo
	@echo '***' Generating 48-bit suffixes...
	@echo
	./slime_seed | head -n 100000 > output.seeds
	@echo
	@echo '...' `wc -l output.seeds | cut -d ' ' -f 1` results
	@echo
	@echo '***' Finding likely 64 bit seeds for 48-bit suffixes...
	@echo
	./expand48to64random < output.seeds > likely.seeds


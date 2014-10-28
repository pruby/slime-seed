#define MAX_SEED (1L << 48)
#define NUM_THREADS 32
#define BLOCK_SIZE 8388608L

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "slime_chunks.h"
#include "slime_algo.h"

const static unsigned long mask_48bit = (1L << 48) - 1L;
const static unsigned long mask_31bit = (1L << 31) - 1L;
const static unsigned long mask_17bit = (1L << 17) - 1L;

#ifdef LOWER_BIT_PREFILTER
unsigned int *lower_bits_series;
unsigned int lower_bits_count;
#endif

typedef struct {
  unsigned int block_counter;
  unsigned long start_seed;
  unsigned long end_seed;
  chunk_list_t chunks;
} run_state;

void *processing_thread(void* data) {
  run_state *state = (run_state*) data;
  
  while (1) {
    unsigned int block = __sync_fetch_and_add(&(state->block_counter), 1);
    unsigned long my_start = state->start_seed + ((long) block * BLOCK_SIZE);
    unsigned long my_end = my_start + BLOCK_SIZE;
    
    if (my_start >= state->end_seed || my_end < my_start) {
      pthread_exit(0);
    }
    
    unsigned long root;
#ifdef LOWER_BIT_PREFILTER
    for (root = (my_start >> 18); root < (my_end >> 18); ++root) {
      unsigned int lv;
      for (lv = 0; lv < lower_bits_count; ++lv) {
      unsigned long seed = (root << 18) | lower_bits_series[lv];
#else
    for (root = my_start; root < my_end; ++root) {
#ifdef SEED_TRANSFORM
      unsigned long seed = seed_transform(root, state->chunk_values[0]);
#else
      unsigned long seed = root;
#endif
#endif
      int hits = 0;
      unsigned int chunk;
      for (chunk = 0; chunk < state->chunks.num_chunks; ++chunk) {
        unsigned long random = ((seed + state->chunks.chunk_values[chunk]) ^ 0x5e434e432) & mask_48bit;
        random = (((random * 0x5DEECE66DL) + 0xBUL) & mask_48bit) >> 17;
        int are_slimes = random % 10 == 0;
        if (are_slimes) {
          hits += 1;
        }
        if (chunk + 1 - hits > state->chunks.num_chunks - state->chunks.required_hits) {
          break;
        }
      }
      if (hits >= state->chunks.required_hits) {
        printf("%ld\n", seed);
        fflush(stdout);
      }
#ifdef LOWER_BIT_PREFILTER
      }
#endif
    }
  }
}

int main(int argc, char** argv) {
  chunk_list_t chunks = read_chunk_list_file("chunks.txt");
  //debug_slime_chunks(&chunks);
  
#ifdef LOWER_BIT_PREFILTER
  calculate_lower_bits_series(chunks.chunk_values, chunks.num_chunks, chunks.required_hits, &lower_bits_series, &lower_bits_count);
  
  fprintf(stderr, "Filtering to %d options for lower 18 bits (%0.9f%%)\n", lower_bits_count, (double) lower_bits_count / (double) 262144);
#endif
  
  run_state state;
  state.block_counter = 0;
  state.chunks = chunks;
  
  state.start_seed = 0;
  state.end_seed = (1L << 48);
  
  pthread_t threads[NUM_THREADS];
  unsigned int i;
  for (i = 0; i < NUM_THREADS; ++i) {
    pthread_create(&threads[i], NULL, processing_thread, (void*) &state);
  }
  
  for (i = 0; i < NUM_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }
  
  return 0;
}

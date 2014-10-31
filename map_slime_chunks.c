/*
 * Generates a PGM file, indicating the probabilities of each chunk
 * spawning slimes. The middle pixel is always cx 0, cz 0. Each
 * pixel is a chunk.
 */

#define RADIUS 500

#define TOP -RADIUS
#define LEFT -RADIUS
#define BOTTOM RADIUS
#define RIGHT RADIUS

#define NUM_THREADS 8

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "slime_algo.h"

typedef struct {
  const unsigned long* seeds;
  int seedCount;
  int start_z;
  int end_z;
  int* counts;
} run_state;

void *processing_thread(void* data) {
  run_state *state = (run_state*) data;
  
  unsigned long seed;
  
  int i, x, z;
  unsigned width = RIGHT - LEFT + 1;
  
  for (z = state->start_z; (z < state->end_z) && (z <= BOTTOM); ++z) {
    for (x = LEFT; x <= RIGHT; ++x) {
      int count = 0;
      unsigned long chunk_val = calc_chunk_val(x, z);
      for (i = 0; i < state->seedCount; i++) {
        unsigned long seed = state->seeds[i];
        
        count += matches(chunk_val, seed);
      }
      state->counts[((z - TOP) * width) + (x - LEFT)] = count;
    }
  }
  
  pthread_exit(0);
}

int main(int argc, char** argv) {
  int width = RIGHT - LEFT + 1;
  int height = BOTTOM - TOP + 1;
  int* counts = (int*) malloc(sizeof(int) * width * height);
  int x, z;
  
  // Zero counts
  memset(counts, 0, sizeof(int) * width * height);
  
  // Load seed list
  int max_seeds = 64;
  unsigned long seed;
  unsigned long* seeds = (unsigned long*) malloc(max_seeds * sizeof(unsigned long));
  int seedCount = 0;
  while (scanf("%lu\n", &seed) > 0) {
    seeds[seedCount++] = seed;
    
    if (seedCount > max_seeds) {
      max_seeds *= 2;
      seeds = (unsigned long*) realloc((void*) seeds, max_seeds * sizeof(unsigned long));
    }
  }
  
  // Run threads to populate counts
  pthread_t threads[NUM_THREADS];
  run_state threadStates[NUM_THREADS];
  int start_z = TOP;
  int total_z = (BOTTOM - TOP + 1); 
  int i;
  for (i = 0; i < NUM_THREADS; i++) {
    threadStates[i].seeds = seeds;
    threadStates[i].seedCount = seedCount;
    
    threadStates[i].start_z = start_z + i * (total_z / NUM_THREADS);
    if (i == NUM_THREADS - 1) {
      threadStates[i].end_z = BOTTOM + 1;
    } else {
      threadStates[i].end_z = start_z + (i + 1) * (total_z / NUM_THREADS);
    }
    
    threadStates[i].counts = counts;
    
    pthread_create(&threads[i], NULL, processing_thread, (void*) &threadStates[i]);
  }
  
  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  
  // Image header
  printf("P2\n");
  printf("%d %d\n", RIGHT - LEFT + 1, BOTTOM - TOP + 1);
  printf("255\n");
  fflush(stdout);
  
  // Output scaled concentrations
  for (z = TOP; z <= BOTTOM; ++z) {
    for (x = LEFT; x <= RIGHT; ++x) {
      if (x != LEFT) {
        printf(" ");
      }
      int count = counts[(z - TOP) * width + x - LEFT];
      
      int shown;
      if (count == 0) {
        shown = 0;
      } else if (count == seedCount) {
        shown = 255;
      } else {
        float prop = ((float) count) / (float) (seedCount);
        shown = (int) round(prop * 253) + 1;
      }
      
      printf("%d", shown);
    }
    printf("\n");
  }
  
  return 0;
}

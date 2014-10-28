#ifndef SLIME_CHUNKS_H
#define SLIME_CHUNKS_H

/* 
 * Seed transform will speed up search almost 10 times.
 * This makes the first chunk provided compulsory - seeds without it won't
 * be listed. It does this by iterating multiples of 10, and finding the
 * unique seed that will produce that number at the first chunk's location.
 * With this enabled, the first chunk should be 100% certain to spawn slimes.
 */
//#define SEED_TRANSFORM
/*
 * Lower bit prefilter is the most efficient way to search, each chunk added
 * is used to speed the search up. Supports REQUIRED_HITS fully.
 */
#define LOWER_BIT_PREFILTER

typedef struct {
  int num_chunks;
  int required_hits;
  int *chunk_xs;
  int *chunk_zs;
  unsigned long *chunk_values;
} chunk_list_t;

chunk_list_t read_chunk_list_file(const char *filename);

void debug_slime_chunks(const chunk_list_t *chunks);

#endif

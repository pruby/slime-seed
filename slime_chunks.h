#ifndef SLIME_CHUNKS_H
#define SLIME_CHUNKS_H

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

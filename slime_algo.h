#ifndef SLIME_ALGO_H

#include <stdint.h>

long calc_chunk_val(long xPosition, long zPosition);
int matches(long chunkval, long seed);
long random_next(long seed);
long random_reverse(long seed);
unsigned long seed_transform(unsigned long root, unsigned long chunkval);
void calculate_lower_bits_series(const unsigned long *chunk_vals, unsigned int chunk_count, unsigned int required_hits, unsigned int **results, unsigned int *count);

#endif

#include <stdio.h>
#include <malloc.h>

const static unsigned long mask_48bit = (1L << 48) - 1L;
const static unsigned long mask_31bit = (1L << 31) - 1L;
const static unsigned long mask_17bit = (1L << 17) - 1L;

long calc_chunk_val(int xPosition, int zPosition) {
  long xsqv = (long) (xPosition * xPosition * 0x4c1906);
  long xv = (long) (xPosition * 0x5ac0db);
  long zsqv = ((long) (zPosition * zPosition)) * 0x4307a7L;
  long zv = (long) (zPosition * 0x5f24f);
  long chunk_val = (xsqv + xv + zsqv + zv);
  return chunk_val;
}

unsigned long random_next(unsigned long seed) {
  return (seed * 0x5DEECE66DUL + 0xBUL) & mask_48bit;
}

unsigned long random_reverse(unsigned long seed) {
  return ((seed - 0xBUL) * 246154705703781UL) & mask_48bit;
}

int matches(long chunkval, long seed) {
  unsigned long random = ((seed + chunkval) ^ 0x5e434e432L) & mask_48bit;
  
  int val;
  long bits;
  do {
      random = random_next(random);
      bits = random >> 17;
      val = bits % 10;
  } while(bits - val + 9 < 0); // Only repeats if bits are from 4294967290 to 4294967295 - 1 in a billion chunks.
  
  return (val == 0);
}

unsigned long seed_transform(unsigned long root, unsigned long chunkval) {
  unsigned long l17 = root & mask_17bit;
  unsigned long a17 = root >> 17;
  long source = ((a17 * 10L) << 17) | l17;
  long pstate = random_reverse(source);
  return (unsigned long) (((pstate^ 0x5e434e432L) - chunkval) & mask_48bit);
}

inline static int filter_even(long chunkval, long seed) {
  unsigned long random = ((seed + chunkval) ^ 0x5e434e432L) & mask_48bit;
  
  int val;
  long bits;
  
  do {
      random = random_next(random);
      bits = random >> 17;
      val = bits % 10;
  } while(bits - val + 9 < 0); // Only repeats if bits are from 4294967290 to 4294967295 - 1 in a billion chunks.
  
  return ((val % 2) == 0);
}

void calculate_lower_bits_series(const long *chunk_vals, unsigned int chunk_count, unsigned int required_hits, unsigned int **results, unsigned int *count_out) {
  unsigned int i, j;
  int count = 0;
  unsigned int capacity = 1024;
  *results = (unsigned int*) malloc(capacity * sizeof(unsigned int));
  
  for (i = 0; i < 262144; ++i) {
    int even_count = 0;
    for (j = 0; j < chunk_count; ++j) {
      if (filter_even(chunk_vals[j], i)) {
        even_count += 1;
      }
    }
    
    if (even_count >= required_hits) {
      // Record possible value of lower bits
      if (count >= capacity) {
        capacity *= 2;
        *results = (unsigned int*) realloc((void*) *results, capacity * sizeof(int));
      }
      (*results)[count] = i;
      count++;
    }
  }
  *count_out = count;
}

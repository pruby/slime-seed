/*
Copyright (c) 2014 Timothy Goddard

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef SLIME_ALGO_H

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

#include <stdint.h>

long calc_chunk_val(long xPosition, long zPosition);
int matches(long chunkval, long seed);
long random_next(long seed);
long random_reverse(long seed);
unsigned long seed_transform(unsigned long root, unsigned long chunkval);
void calculate_lower_bits_series(const unsigned long *chunk_vals, unsigned int chunk_count, unsigned int required_hits, unsigned int **results, unsigned int *count);

#endif

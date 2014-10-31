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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/*
 * If no seed is provided to Minecraft when creating a world, it generates the seed with:
 * 
 *     (new Random()).nextLong()
 * 
 * This breaks down to two successive outputs of the Random() LCG, which only has
 * 48 bits of entropy. As a result, any given lower 48 bits of seed is consistent
 * on average with one 64 bit total seed - most 64 bit seeds are simply not possible.
 * 
 * This program takes 48 bit partial seeds, 1 per line, and outputs the possible 64 bit
 * seeds that could have these lower 48 bits if generated with this approach.
 */

#include "slime_algo.h"

const static long mask_32bit = (1L << 32) - 1L;
const static long mask_16bit = (1L << 16) - 1L;

int main(int argc, char** argv) {
  // Load seed list
  long seed;
  while (scanf("%ld\n", &seed) > 0) {
    long lowerInt = seed & mask_32bit;
    long upperPartial = (seed >> 32) & mask_16bit;
    int i;
    for (i = 0; i < (1 << 16); ++i) {
      long state = (lowerInt << 16) | i;
      long prevState = random_reverse(state);
      long lastOutput = prevState >> 16;
      if ((lastOutput & mask_16bit) == upperPartial) {
        printf("%ld\n", ((lastOutput << 32) | lowerInt));
      }
    }
  }
  
  return 0;
}

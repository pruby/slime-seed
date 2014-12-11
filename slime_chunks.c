
#line 1 "slime_chunks.rl"
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

#include "slime_chunks.h"
#include "slime_algo.h"

#define BUFFER_SIZE 256


#line 74 "slime_chunks.rl"



#line 39 "slime_chunks.c"
static const int slimechunks_start = 1;
static const int slimechunks_error = 0;

static const int slimechunks_en_main = 1;


#line 77 "slime_chunks.rl"

chunk_list_t read_chunk_list_file(const char *filename)
{
  chunk_list_t result;
  char buffer[BUFFER_SIZE];
  FILE *file = fopen(filename, "r");
  
  result.required_hits = -1;
  result.num_chunks = 0;
  
  int chunk_capacity = 8;
  result.chunk_xs = malloc(chunk_capacity * sizeof(int));
  result.chunk_zs = malloc(chunk_capacity * sizeof(int));
  result.chunk_values = malloc(chunk_capacity * sizeof(unsigned long));
  
  int current_sign = 1;
  int current_number = 0;
  int cs;
  
  
#line 67 "slime_chunks.c"
	{
	cs = slimechunks_start;
	}

#line 97 "slime_chunks.rl"

  char *eof = 0;
  while ( !eof )
  {
    char *p = buffer, *pe;

    int len = fread( p, 1, BUFFER_SIZE, file );
    pe = p + len;

    /* Check if this is the end of file. */
    if ( len < BUFFER_SIZE )
    {
      eof = pe;
    }
    
    
#line 89 "slime_chunks.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 83: goto st2;
		case 115: goto st2;
	}
	goto st0;
st0:
cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	switch( (*p) ) {
		case 76: goto st3;
		case 108: goto st3;
	}
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	switch( (*p) ) {
		case 73: goto st4;
		case 105: goto st4;
	}
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	switch( (*p) ) {
		case 77: goto st5;
		case 109: goto st5;
	}
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	switch( (*p) ) {
		case 69: goto st6;
		case 101: goto st6;
	}
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 32 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 67: goto st8;
		case 99: goto st8;
	}
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	switch( (*p) ) {
		case 72: goto st9;
		case 104: goto st9;
	}
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	switch( (*p) ) {
		case 85: goto st10;
		case 117: goto st10;
	}
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 78: goto st11;
		case 110: goto st11;
	}
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	switch( (*p) ) {
		case 75: goto st12;
		case 107: goto st12;
	}
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 83: goto st13;
		case 115: goto st13;
	}
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	switch( (*p) ) {
		case 10: goto st38;
		case 32: goto st13;
		case 35: goto st15;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st13;
	goto st0;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 10: goto st38;
		case 32: goto st14;
		case 35: goto st15;
		case 67: goto st16;
		case 82: goto st28;
		case 99: goto st16;
		case 114: goto st28;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st14;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	switch( (*p) ) {
		case 10: goto st38;
		case 32: goto st14;
		case 35: goto st15;
		case 67: goto st16;
		case 99: goto st16;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st14;
	goto st0;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) == 10 )
		goto st38;
	goto st15;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 88: goto tr17;
		case 120: goto tr17;
	}
	goto st0;
tr17:
#line 45 "slime_chunks.rl"
	{
    result.num_chunks += 1;
    
    if (result.num_chunks > chunk_capacity)
    {
      chunk_capacity *= 2;
      result.chunk_xs = realloc(result.chunk_xs, chunk_capacity * sizeof(int));
      result.chunk_zs = realloc(result.chunk_zs, chunk_capacity * sizeof(int));
      result.chunk_values = realloc(result.chunk_values, chunk_capacity * sizeof(unsigned long));
    }
  }
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 277 "slime_chunks.c"
	switch( (*p) ) {
		case 32: goto st17;
		case 43: goto tr19;
		case 44: goto tr20;
		case 45: goto tr21;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr22;
	} else if ( (*p) >= 9 )
		goto st17;
	goto st0;
tr19:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
	goto st18;
tr21:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
#line 39 "slime_chunks.rl"
	{current_sign = -1;}
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 304 "slime_chunks.c"
	if ( (*p) == 44 )
		goto st19;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr24;
	goto st0;
tr20:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
	goto st19;
tr22:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
#line 40 "slime_chunks.rl"
	{current_number = current_number * 10 + (*p - '0');}
	goto st19;
tr24:
#line 40 "slime_chunks.rl"
	{current_number = current_number * 10 + (*p - '0');}
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 328 "slime_chunks.c"
	switch( (*p) ) {
		case 32: goto tr25;
		case 44: goto st19;
		case 67: goto tr26;
		case 99: goto tr26;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr24;
	} else if ( (*p) >= 9 )
		goto tr25;
	goto st0;
tr25:
#line 42 "slime_chunks.rl"
	{result.chunk_xs[result.num_chunks - 1] = current_number * current_sign;}
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 349 "slime_chunks.c"
	switch( (*p) ) {
		case 32: goto st20;
		case 67: goto st21;
		case 99: goto st21;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st20;
	goto st0;
tr26:
#line 42 "slime_chunks.rl"
	{result.chunk_xs[result.num_chunks - 1] = current_number * current_sign;}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 366 "slime_chunks.c"
	switch( (*p) ) {
		case 90: goto st22;
		case 122: goto st22;
	}
	goto st0;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	switch( (*p) ) {
		case 32: goto st22;
		case 43: goto tr30;
		case 44: goto tr31;
		case 45: goto tr32;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr33;
	} else if ( (*p) >= 9 )
		goto st22;
	goto st0;
tr30:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
	goto st23;
tr32:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
#line 39 "slime_chunks.rl"
	{current_sign = -1;}
	goto st23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
#line 402 "slime_chunks.c"
	if ( (*p) == 44 )
		goto st24;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr35;
	goto st0;
tr31:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
	goto st24;
tr33:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
#line 40 "slime_chunks.rl"
	{current_number = current_number * 10 + (*p - '0');}
	goto st24;
tr35:
#line 40 "slime_chunks.rl"
	{current_number = current_number * 10 + (*p - '0');}
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 426 "slime_chunks.c"
	switch( (*p) ) {
		case 10: goto tr37;
		case 32: goto tr36;
		case 35: goto tr38;
		case 44: goto st24;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr35;
	} else if ( (*p) >= 9 )
		goto tr36;
	goto st0;
tr36:
#line 43 "slime_chunks.rl"
	{result.chunk_zs[result.num_chunks - 1] = current_number * current_sign;}
#line 57 "slime_chunks.rl"
	{
    result.chunk_values[result.num_chunks - 1] = calc_chunk_val(result.chunk_xs[result.num_chunks - 1], result.chunk_zs[result.num_chunks - 1]);
  }
	goto st25;
tr56:
#line 41 "slime_chunks.rl"
	{result.required_hits = current_number * current_sign;}
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 455 "slime_chunks.c"
	switch( (*p) ) {
		case 10: goto st39;
		case 32: goto st25;
		case 35: goto st27;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st25;
	goto st0;
tr37:
#line 43 "slime_chunks.rl"
	{result.chunk_zs[result.num_chunks - 1] = current_number * current_sign;}
#line 57 "slime_chunks.rl"
	{
    result.chunk_values[result.num_chunks - 1] = calc_chunk_val(result.chunk_xs[result.num_chunks - 1], result.chunk_zs[result.num_chunks - 1]);
  }
	goto st39;
tr57:
#line 41 "slime_chunks.rl"
	{result.required_hits = current_number * current_sign;}
	goto st39;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
#line 480 "slime_chunks.c"
	switch( (*p) ) {
		case 10: goto st39;
		case 32: goto st26;
		case 35: goto st27;
		case 67: goto st16;
		case 99: goto st16;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st26;
	goto st0;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 10: goto st39;
		case 32: goto st26;
		case 35: goto st27;
		case 67: goto st16;
		case 99: goto st16;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st26;
	goto st0;
tr38:
#line 43 "slime_chunks.rl"
	{result.chunk_zs[result.num_chunks - 1] = current_number * current_sign;}
#line 57 "slime_chunks.rl"
	{
    result.chunk_values[result.num_chunks - 1] = calc_chunk_val(result.chunk_xs[result.num_chunks - 1], result.chunk_zs[result.num_chunks - 1]);
  }
	goto st27;
tr58:
#line 41 "slime_chunks.rl"
	{result.required_hits = current_number * current_sign;}
	goto st27;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
#line 521 "slime_chunks.c"
	if ( (*p) == 10 )
		goto st39;
	goto st27;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 69: goto st29;
		case 101: goto st29;
	}
	goto st0;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 81: goto st30;
		case 113: goto st30;
	}
	goto st0;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 85: goto st31;
		case 117: goto st31;
	}
	goto st0;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 73: goto st32;
		case 105: goto st32;
	}
	goto st0;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 82: goto st33;
		case 114: goto st33;
	}
	goto st0;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 69: goto st34;
		case 101: goto st34;
	}
	goto st0;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	if ( (*p) == 32 )
		goto st35;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st35;
	goto st0;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 32: goto st35;
		case 43: goto tr50;
		case 44: goto tr51;
		case 45: goto tr52;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr53;
	} else if ( (*p) >= 9 )
		goto st35;
	goto st0;
tr50:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
	goto st36;
tr52:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
#line 39 "slime_chunks.rl"
	{current_sign = -1;}
	goto st36;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
#line 618 "slime_chunks.c"
	if ( (*p) == 44 )
		goto st37;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr55;
	goto st0;
tr51:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
	goto st37;
tr53:
#line 38 "slime_chunks.rl"
	{current_number = 0; current_sign = 1;}
#line 40 "slime_chunks.rl"
	{current_number = current_number * 10 + (*p - '0');}
	goto st37;
tr55:
#line 40 "slime_chunks.rl"
	{current_number = current_number * 10 + (*p - '0');}
	goto st37;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
#line 642 "slime_chunks.c"
	switch( (*p) ) {
		case 10: goto tr57;
		case 32: goto tr56;
		case 35: goto tr58;
		case 44: goto st37;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr55;
	} else if ( (*p) >= 9 )
		goto tr56;
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 113 "slime_chunks.rl"
    
    if (cs == slimechunks_error)
    {
      fprintf(stderr, "Error parsing chunks file.\n");
      exit(1);
    }
  }
  
  if (result.required_hits < 0)
  {
    result.required_hits = result.num_chunks;
  }
  
  fclose(file);
  
  return result;
}

void debug_slime_chunks(const chunk_list_t *chunks)
{
  int i;
  fprintf(stderr, "Debug chunks: require %d of %d\n", chunks->required_hits, chunks->num_chunks);
  for (i = 0; i < chunks->num_chunks; ++i)
  {
    fprintf(stderr, "X%+d Z%+d V=%lu\n", chunks->chunk_xs[i], chunks->chunk_zs[i], chunks->chunk_values[i]);
  }
}

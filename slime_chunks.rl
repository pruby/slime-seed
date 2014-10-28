#include <stdlib.h>
#include <stdio.h>

#include "slime_chunks.h"
#include "slime_algo.h"

#define BUFFER_SIZE 256

%%{
  machine slimechunks;
  
  comment = "#" any* :>> '\n';
  
  tolineend = space* (comment | '\n');
  
  action start_number {current_number = 0; current_sign = 1;}
  action negate_sign {current_sign = -1;}
  action number_digit {current_number = current_number * 10 + (*p - '0');}
  action set_required {result.required_hits = current_number * current_sign;}
  action set_chunk_x {result.chunk_xs[result.num_chunks - 1] = current_number * current_sign;}
  action set_chunk_z {result.chunk_zs[result.num_chunks - 1] = current_number * current_sign;}
  
  action start_chunk {
    result.num_chunks += 1;
    
    if (result.num_chunks > chunk_capacity)
    {
      chunk_capacity *= 2;
      result.chunk_xs = realloc(result.chunk_xs, chunk_capacity * sizeof(int));
      result.chunk_zs = realloc(result.chunk_zs, chunk_capacity * sizeof(int));
      result.chunk_values = realloc(result.chunk_values, chunk_capacity * sizeof(unsigned long));
    }
  }
  
  action finish_chunk {
    result.chunk_values[result.num_chunks - 1] = calc_chunk_val(result.chunk_xs[result.num_chunks - 1], result.chunk_zs[result.num_chunks - 1]);
  }
  
  sign = "+" | ("-" @negate_sign);
  number = (sign? (digit @number_digit | ',')+) >start_number;
  
  header = "slime chunks"i tolineend+;
  
  required = "require"i space+ number %set_required tolineend+;
  
  chunk_x = "CX"i @start_chunk space* number %set_chunk_x;
  chunk_z = "CZ"i space* number %set_chunk_z;
  
  chunk = space* chunk_x space* chunk_z %finish_chunk tolineend+;
  
  main := header required? chunk*;
}%%

%% write data nofinal;

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
  
  %% write init;

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
    
    %% write exec;
    
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

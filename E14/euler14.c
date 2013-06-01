#include <stdio.h>
#include <stdlib.h>

extern inline long even(long number) { return number/2; }

extern inline long odd(long number) { return number * 3 + 1; }

long compute_chain(long term) {
   long sequence_length = 1;
   /* extern inline long odd(long number);
   extern inline long even(long number); */

   while (term > 1) {
      if ( term % 2 == 0 ) { 
         term = even(term);
         sequence_length++;
      }
      else {
         term = even(odd(term));
         sequence_length += 2;
      }
   }
   return sequence_length;
}

int main(int argc, char *argv[])
{

   printf("13's sequence is, %ld long\n", compute_chain(13));

   int initial_term = 2;
   int last_term = 1000000;
   long longest_chain = 0;
   int longest_chain_start = 0;

   for (long i = initial_term; i <= last_term; i++) {
      long sequence_length = compute_chain(i);
      if (sequence_length > longest_chain) {
         longest_chain = sequence_length;
         longest_chain_start = i;
         printf("\nNew Max Term at %ld: %ld", i, longest_chain);
      }
   }
   printf("\n   The starting term %d produces a chain of %ld\n", 
          longest_chain_start, longest_chain);
}

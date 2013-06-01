#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define ABSUM_MAX 28124

static short isAbSum[ABSUM_MAX];

void abundantSums(void)
{
   int i,j;
   int root = 3;
   long sum,nxtSquare;

   nxtSquare = (root+1)*(root+1);

   for (i = 0; i <= 11; i++) { isAbSum[i] = 0; }

   for (i = 12; i < ABSUM_MAX; i++) {
      if (i >= nxtSquare) {
         root++;
         nxtSquare = (root+1)*(root+1);
      }
      sum = 1;
      for (j = 2; j <= root; j++) {
         if (i%j == 0) {
            sum += ((j == i/j) ? j : j + i/j);
         }
      }
      isAbSum[i] = (sum > i) ? -1 : 0;
      /* printf ("AbSum(%d): %d\n",i,sum); */
   }
}

int main(int argc, char *argv[])
{
   int i,j,sumval;
   long finalSum = 1;

   abundantSums(); 
   
   for (i = 1; i < ABSUM_MAX; i++) {
      /* printf("%d %2d",i,isAbSum[i]); */
      j = i/2;
      do {
         sumval = (isAbSum[j] && isAbSum[i-j]);
         /* if (sumval) { printf (" = %d + %d",i-j,j); */
      } while (!sumval && --j >= 1);
      if (!sumval) {
         printf ("%d added\n",i);
         finalSum += i;
      }
      /* printf("\n"); */
   }
   printf("Final Sum: %d\n", finalSum);
}

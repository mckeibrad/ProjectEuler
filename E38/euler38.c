#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <math.h>

/*-----------------------------------------------------------------------------
* Take the number 192 and multiply it by each of 1, 2, and 3:
*
*     192 × 1 = 192
*     192 × 2 = 384
*     192 × 3 = 576
*
* By concatenating each product we get the 1 to 9 pandigital, 192384576. We
* will call 192384576 the concatenated product of 192 and (1,2,3)
*
* The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4,
* and 5, giving the pandigital, 918273645, which is the concatenated product of
* 9 and (1,2,3,4,5).
*
* What is the largest 1 to 9 pandigital 9-digit number that can be formed as the
* concatenated product of an integer with (1,2, ... , n) where n > 1?
* ----------------------------------------------------------------------------*/

static unsigned int count,pdsum;
static short dv[10];
static unsigned int powers[] = {1,10,100,1000,10000,100000,1000000};

void zeroDv(void)
{
   for (int i = 1; i < 10; i++) dv[i] = 0;
   dv[0] = 99;
   count = pdsum = 0;
}

unsigned int stillpan(int prod)
{
   int n = 0;
   int ps = prod;
   
   while (prod > 0) {
      if (dv[prod%10]++ > 0) return(10);
      prod /= 10;
      n++;
   }
   pdsum = pdsum*powers[n]+ps;
   return(n);
}

int main(int argc,char *argv[])
{
   int i,n;
   unsigned long maxPdSum = 0;

   for (n = 2; n<9877; n++) {
      zeroDv();
      i = 0;
      while (count < 9) {
         count += stillpan(++i*n);
      }
      if (count == 9) {
         if (pdsum > maxPdSum) maxPdSum = pdsum;
         printf("%4d*(1-%d) is %ld   Max: %ld\n",n,i,pdsum, maxPdSum);
      }
   }
}

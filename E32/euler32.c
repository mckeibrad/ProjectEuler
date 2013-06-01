#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define MX 20

/*-----------------------------------------------------------------------------
* We shall say that an n-digit number is pandigital if it makes use of all the
* digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1
* through 5 pandigital.
*
* The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing
* multiplicand, multiplier, and product is 1 through 9 pandigital.
*
* Find the sum of all products whose multiplicand/multiplier/product identity
* can be written as a 1 through 9 pandigital.
* 
* HINT: Some products can be obtained in more than one way so be sure to only
* include it once in your sum.
* ----------------------------------------------------------------------------*/

static unsigned int count,pdsum;
static short dv[10];
static short pv[10000];
unsigned long powers[] = {
   100000000,10000000,1000000,100000,10000,1000,100,10,1};

void fmult(int m1,int ms2,int dc)
{
   int i,j,m2;
   long px,pt;
   long p1,p2;

   dc++;
   /* p1 = 1;*/
   /* for (i=1; i<=8-dc; i++) p1 = (p1 == 0) ? 10 : p1*10; */
   p1 = powers[dc];
   p2 = p1*10;

   for (i=1; i<=9; i++) {
      if (dv[i] != 0) continue;
      dv[i] = 2;
      m2 = ms2*10+i;
      px = pt = m1*m2;
      /* printf("%d: %d*%d=%d   %d-%d\n",dc,m1,m2,px,p1,p2); */
      if (p1 < px && px < p2) {
         while (pt > 0) {
            j=pt%10;
            if (dv[j] != 0) break;
            dv[j] = 3;
            pt /= 10;
         }
         if (pt <= 0 && pv[px] <= 0) {
            pv[px]++;
            count++;
            pdsum += px;
            printf("found(%d): %d*%d=%d   %d %d\n",dc,m1,m2,px,p1,p2);
         }
         for (j=1; j<=9; j++) {
            if (dv[j] == 3) dv[j] = 0;
         }
      }
      if (px <= p2) fmult(m1,m2,dc);
      dv[i] = 0;
   }
   return;
}

int main(int argc,char *argv[])
{
   int i,j,m1;

   dv[0] = 99;
   pdsum = 0;
   for(i=1; i<=9; i++) {
      dv[i] = 1;
      fmult(i,0,1);
      for (j=1; j<=9; j++) {
         if (dv[j] == 0) {
            dv[j] = 1;
            fmult(i*10+j,0,2);
            dv[j] = 0;
         }
      }
      dv[i] = 0;
   }             
        
   printf("Count of [1-9] pan digit multipliers: %d  Sum: %d\n",count,pdsum);
}

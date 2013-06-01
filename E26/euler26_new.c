#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define MAX_VAL 1005

static unsigned quoVals[MAX_VAL],remVals[MAX_VAL],quotientVals[MAX_VAL];
static unsigned quoFlags[MAX_VAL],remFlags[MAX_VAL];

/*-----------------------------------------------------------------------------
 * Find the longest repeating string of digits 1/n for 1 < n <=1000. As the
 * decimal digits are created they will begin to repeat once a remainder occurs
 * a second time.  Therefore the longest possible repeating sequece for any
 * given n is n-1 digits.
 * ---------------------------------------------------------------------------*/

int isFirst(unsigned myQuotient, unsigned myRem)
{
    int i = 0, myFirst; 

    while (quoVals[++i] != 0 && remVals[i] != 0 && !myFirst) {
        myFirst = (quoVals[i] != myQuotient || remVals[i] != myRem) ? 0 : i;
    }
    if (!myFirst) {
        quoVals[i] = myQuotient;
        remVals[i] = myRem;
    }
    return (myFirst);
}

void clearFirst(void) {

    int i;

    for (i = 0; i < MAX_VAL; i++) {
        quoVals[i] = remVals[i] = quotientVals[i] = 0;
        quoFlags[i] = remFlags[i] = 0;
    }

}

int main(int argc,char *argv[])
{
   unsigned n,div,rem,quotient,i,k,thisRepeatCount,maxRepeatCount;
   int remFirst;

   maxRepeatCount = 0;
   /*n = 1000;
   while (n > 1 && maxRepeatCount < n-1) { */
   n = 984;
   while (n > 983 && maxRepeatCount < n-1) {
       clearFirst();
       i = 0;
       div = 1;
       do {
           div *= 10;
           if (div >= n) {
              quotient = div/n;
              rem = div%n;
           }
           else {
              rem = div;
              quotient = 0;
           }
           printf ("%d/%d = %d %d  -- %d %d\n",
                  div,n,
                  quotient,quoFlags[quotient],
                  rem,remFlags[rem]
                  );
           remFirst = isFirst(quotient,rem);
           div = rem;
       } while (remFirst && rem != 0);

       thisRepeatCount = (rem != 0) ? i - remFlags[rem] + 1 : 0;
       if (thisRepeatCount > maxRepeatCount) maxRepeatCount = thisRepeatCount;
          
       printf("%d: %d %d ",n,remFlags[rem],thisRepeatCount);
       for (k = 1; k <= i; k++) {
           if (rem != 0 && k == remFlags[rem]) {printf("(");}
           printf("%d",quotientVals[k]);
       }
       printf((rem == 0) ? "\n" : ")\n");
       n--;
   }
   printf("Max Repeat Count: %d\n", maxRepeatCount);
}

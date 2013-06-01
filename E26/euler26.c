#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define MAX_NUM 1000
#define MAX_VAL ((MAX_NUM + 5) * 10 + 50)
#define MAX_FGS (MAX_VAL*10 + 50)

/*-----------------------------------------------------------------------------
 * Find the longest repeating string of digits 1/n for 1 < n <=1000. As the
 * decimal digits are created they will begin to repeat once a remainder occurs
 * a second time.  Therefore the longest possible repeating sequece for any
 * given n is n-1 digits.
 * ---------------------------------------------------------------------------*/

int main(int argc,char *argv[])
{
   unsigned n,div,rem,quotient,k,thisRepeatCount,maxRepeatNum;
   unsigned remFlags[MAX_VAL],quotientVals[MAX_VAL];
   int remFirst;
   int idxRemFg,iStartRepeat,iEndQuoVals;
   unsigned maxRepeatCount = 0;
   
   /*
   n = 984;
   while (n > 983 && maxRepeatCount < n-1) {
   */

   n = MAX_NUM;
   while (n > 1 && maxRepeatCount < n-1) {
       for (k = 0; k < MAX_VAL; k++) {
           remFlags[k] = quotientVals[k] = 0;
       }
       iEndQuoVals = idxRemFg = iStartRepeat = 0;
       div = 1;
       do {
           div *= 10;
           quotient = div/n;
           rem = div%n;
           idxRemFg = rem*10+quotient;

           /*
           printf ("%d/%d = %d R %d  -- %d\n",
                    div,n,
                    quotient,rem,
                    remFlags[idxRemFg]
                  );
           */

           if (remFirst = (remFlags[idxRemFg] == 0)) {
               remFlags[idxRemFg] = ++iEndQuoVals;
               quotientVals[iEndQuoVals] = quotient;        
           }
           else {
               iStartRepeat = remFlags[idxRemFg];
           }

           div = rem;
       } while (remFirst && rem != 0);

       thisRepeatCount = (rem != 0) ? iEndQuoVals - iStartRepeat + 1 : 0;
       if (thisRepeatCount > maxRepeatCount) {
           maxRepeatCount = thisRepeatCount;
           maxRepeatNum = n;
       }
          
       printf("1/%d: %d %d = .",n,iStartRepeat,thisRepeatCount);
       for (k = 1; k <= iEndQuoVals; k++) {
           if (rem != 0 && k == iStartRepeat) {printf("(");}
           printf("%d",quotientVals[k]);
       }
       printf((rem == 0) ? "\n" : ")\n");
       n--;
   }
   printf("Max Repeat Count of, %d, occurs at number: %d\n",
          maxRepeatCount,maxRepeatNum);
}

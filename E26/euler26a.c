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
   unsigned n,rem,remFirst,k,thisRepeatCount,maxRepeatNum;
   unsigned maxRepeatCount = 0;
   
   n = MAX_NUM;
   if (argc > 1) {
      printf("%s\n",argv[1]);
      sscanf(argv[1],"%d",&n);
   }
   n--;
   while (n > 1 && maxRepeatCount < n-1) {
       rem = 1;
       for (k = 0; k < n && rem != 0; k++) rem = (rem*10)%n;
       remFirst = rem;
       thisRepeatCount = 0;
       do {
           rem = (rem*10)%n;
           thisRepeatCount++;
       } while (rem != remFirst && rem != 0);

       if (rem == 0) thisRepeatCount = 0;
       if (thisRepeatCount > maxRepeatCount) {
           maxRepeatCount = thisRepeatCount;
           maxRepeatNum = n;
       }
       printf("1/%d: %d\n",n,thisRepeatCount);
       n -= 2;
   }
   printf("Max Repeat Count of, %d, occurs at number: %d\n",
          maxRepeatCount,maxRepeatNum);
}

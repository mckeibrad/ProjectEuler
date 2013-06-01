#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *ones[] = {
   "zero",
   "one","two","three","four","five","six","seven","eight","nine","ten",
   "eleven","twelve","thirteen","fourteen","fifteen",
   "sixteen","seventeen","eighteen","nineteen"};
static char *tens[] = {
   "ones","teens",
   "twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};


int main(int argc, char *argv[])
{
   int i,h,t,o;
   int intCharCount = 0;
   char number[1000];

  for (i = 1; i <= 999; i++) {
      for (int j = 1; j < 1000; j++ ) {number[j] = '\0';}
      strcpy(number,"");
      t = i % 100;
      if (i >= 100) {
         h = i/100;
         strcpy(number,ones[h]);
         strcat(number,"hundred");
         if (t > 0) {strcat(number,"and"); }
      }
      if (t > 0 && t < 20) {strcat(number,ones[t]); }
      if (t >= 20) {
         o = t % 10;
         t /= 10;
         strcat(number,tens[t]);
         if (o > 0) {
            /* strcat(number," ");*/
            strcat(number,ones[o]);
         }
      }
      printf("%d: %s\n",i,number);
      intCharCount += strlen(number);
   }
   strcpy(number,"onethousand");
   intCharCount += strlen(number);
   printf("%d: %s\n",1000,number);
   printf("Character Count: %d\n", intCharCount);
}

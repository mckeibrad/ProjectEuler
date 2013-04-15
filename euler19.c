#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

struct sdate {
   long y, m, d;
};

static char *wkday[] = {
   "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

long gday(int Yr, int Mth, int Dy) {       /* convert date to day number */
  long  y, m;

  m = (Mth + 9)%12;                /* mar=0, feb=11 */
  y = Yr - m/10;                     /* if Jan/Feb, year-- */
  return y*365 + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (Dy - 1);
  }

struct sdate dtf(long d) { /* convert day number to y,m,d format */
  struct sdate pd;
  long y, ddd, mm, dd, mi;

  /* y=int(d/365.2425) with 1.4780 error correction */
  y = (10000*d + 14780)/3652425;

  /* Compute day of year with mar as 0 and Feb as 11 of previous year */
  ddd = d - (y*365 + y/4 - y/100 + y/400);
  if (ddd < 0) {
    y--;
    ddd = d - (y*365 + y/4 - y/100 + y/400);
    }

  mi = (52 + 100*ddd)/3060; /* Compute month relative to March = 0 */

  /* Adjust back to standard format i.e. Jan = 1 */
  pd.y = y + (mi + 2)/12;
  pd.m = (mi + 2)%12 + 1;
  pd.d = ddd - (mi*306 + 5)/10 + 1;
  return pd;
  }

int calcDOW(int Year,int Month, int Day)
{
    /* return 0 for Sunday, ..., 6 for Saturday */
     return ((int) ((gday(Year, Month, Day)+3)%7));
}

int main(int argc, char *argv[])
{
   int Year, Month, Day, i, w, sumDays;
   int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
   int dowCount[7];
   long o,lasto;

   /*
   Year = atoi(argv[1]);
   Month = atoi(argv[2]);
   Day = atoi(argv[3]);
      mdays[2] = (Year%4 == 0) ? 29 : 28;
      for (Day = 1; Day <= mdays[Month]; Day++) {
      */

   lasto = gday(2001,1,1);
   sumDays = 0;
   for (i = 0; i < 7; i++) { dowCount[i] = 0; }
   Day = 1;
   for (Year = 2000; Year >= 1800; Year--) {
      mdays[2] = (Year%400 == 0 || (Year%4 == 0 && Year%100 != 0)) ? 29 : 28;
      for (Month = 12; Month >= 1; Month--) {
         for (Day = 1; Day >= 1; Day--) {
            o = gday(Year,Month,Day);
            w = calcDOW(Year,Month,Day);
            printf("%2.2d/%2.2d/%d: %ld %d %d %s\n",
                   Month,Day,Year,o,lasto-o,w,wkday[w]);
            dowCount[w]++;
            lasto = o;
         }
      }
   }
   
   for (i = 0; i < 7; i++) {
       sumDays += dowCount[i];
       printf("%s count: %d\n", wkday[i], dowCount[i]);
   }
   printf("Sum of count: %d\n", sumDays);
}

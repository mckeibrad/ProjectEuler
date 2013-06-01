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

  y = (10000*d + 14780)/3652425;
  ddd = d - (y*365 + y/4 - y/100 + y/400);
  if (ddd < 0) {
    y--;
    ddd = d - (y*365 + y/4 - y/100 + y/400);
    }
  mi = (52 + 100*ddd)/3060;
  pd.y = y + (mi + 2)/12;
  pd.m = (mi + 2)%12 + 1;
  pd.d = ddd - (mi*306 + 5)/10 + 1;
  return pd;
  }

int calcDOW(int Year,int Month, int Day)
{
    return ((int) ((gday(Year, Month, Day)+3)%7));
}

int main(int argc, char *argv[])
{
   int Year, Month, Day, i, w, sumDays;
   int sunCount;
   int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
   int dowCount[7];
   long o,lasto;
   struct tm mytm;
   char xday[50];
   time_t tx;

   /*
   Year = atoi(argv[1]);
   Month = atoi(argv[2]);
   Day = atoi(argv[3]);
      mdays[2] = (Year%4 == 0) ? 29 : 28;
      for (Day = 1; Day <= mdays[Month]; Day++) {
      */

   lasto=0;
   sunCount = 0;
   sumDays = 0;
   for (i = 0; i < 7; i++) { dowCount[i] = 0; }
   Day = 1;
   for (Year = 1901; Year <= 2000; Year++) {
      mdays[2] = (Year%4 == 0) ? 29 : 28;
      for (Month = 1; Month <= 12; Month++) {
         for (Day = 1; Day <= 1; Day++) {
            mytm.tm_sec = 1;
            mytm.tm_min = 1;
            mytm.tm_hour = 12;
            mytm.tm_year = Year-1900;
            mytm.tm_mon = Month-1;
            mytm.tm_mday = Day;
            mytm.tm_isdst = -1;
            (void) mktime(&mytm);
            /*printf("%d, strftime: %d  ",tx,strftime(xday,50,"%w",&mytm));*/
            (void) strftime(xday,50,"%w",&mytm);
            i = atoi(xday);
            o = gday(Year,Month,Day);
            w = calcDOW(Year,Month,Day);
            printf("%s - %2.2d/%2.2d/%d: %ld %d %d %s\n",
                   (i == w) ? "=" : "!",Month,Day,Year,o,o-lasto,w,wkday[w]);
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

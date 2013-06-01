#include <stdio.h>
#include <stdlib.h>

#define MXSIZE 53

static unsigned long intMxSize = 20;
static unsigned long ulnRouteCount = 0;
static unsigned long ulnModCount = 0;

unsigned long latticecount(unsigned int Sz) {
   static unsigned long lattice[MXSIZE][MXSIZE];
   int i,j;
   unsigned int lSz;

   for (i = 0; i < MXSIZE; i++) {
     for (j = 0; j < MXSIZE; j++) { lattice[i][j] = 0; }
   }

   lSz = Sz+1;

   for (i = 1; i <= lSz; i++) {
      for(j = 1; j <= lSz+1; j++) {
         lattice[i][j] = (i == 1 && j== 1) ? 1 : lattice[i-1][j]+lattice[i][j-1];
      }
   }
   return (lattice[lSz][lSz]);
}

int main(int argc, char *argv[])
{
   int i;

   for (i = 2; i <= intMxSize; i++) {
      printf("lattice size %d   lattice count: %ld\n",i,latticecount(i));
   }
}

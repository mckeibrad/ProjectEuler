#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define MX 20

/*-----------------------------------------------------------------------------
* In England the currency is made up of pound, £, and pence, p, and there are
* eight coins in general circulation:
*
*     1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
*
*     It is possible to make £2 in the following way:
*
*         1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
*
*         How many different ways can £2 be made using any number of coins?
* ----------------------------------------------------------------------------*/

int cv[8] = {1,2,5,10,20,50,100,200};

unsigned nways(long amt, int idxCv)
{
    unsigned count = 0;

    if (idxCv == 0) return(1);
    while (amt > 0) {
        count += nways(amt,idxCv-1);
        amt -= cv[idxCv];
    }
    return((amt == 0) ? count+1 : count);
}

int main(int argc,char *argv[])
{
    long amt = (argc >= 2) ? atol(argv[1]) : 200;

    printf("Ways to make %d pence: %d\n",amt,nways(amt,7));
}

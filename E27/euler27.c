#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define MX 20

/*-----------------------------------------------------------------------------
* Euler published the remarkable quadratic formula:
* 
* n² + n + 41
*
* It turns out that the formula will produce 40 primes for the consecutive
* values n = 0 to 39. However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is
* divisible by 41, and certainly when n = 41, 41² + 41 + 41 is clearly divisible
* by 41.
* 
* Using computers, the incredible formula  n² − 79n + 1601 was discovered, which
* produces 80 primes for the consecutive values n = 0 to 79. The product of the
* coefficients, −79 and 1601, is −126479.
*
* Considering quadratics of the form:
*
*     n² + an + b, where |a| < 1000 and |b| < 1000
*
*     where |n| is the modulus/absolute value of n
*     e.g. |11| = 11 and |−4| = 4
*
* Find the product of the coefficients, a and b, for the quadratic expression
* that produces the maximum number of primes for consecutive values of n,
* starting with n = 0.
* ----------------------------------------------------------------------------*/

long fcn(int n,int a,int b)
{
    return(n*(n+b)+a);
}
int isprime(int n)
{
    int i = 2;
    int rtn = 0;

    if ( n < 1) return(rtn);
    rtn = -1;
    if (n == 2) return(rtn);

    while (i*i <= abs(n)) {
        if (n%i == 0) {
            rtn = 0;
            break;
        }
        i++;
    }
    return(rtn);
}

int main(int argc,char *argv[])
{
    int i,mxC,mxA,mxB;
    long v;
    int a,b;

    for(a = 2; a < 1000; a++) {
        if (!isprime(a)) continue;
        for (b = 1000; b >= -1000; b--) {
            i = 0;
            do {
                v=fcn(++i,a,b);
            } while(isprime(v));
            if (i > mxC) {
                mxC = i;
                mxA = a;
                mxB = b;
                printf("Count: %d   A: %d   B: %d  Px: %d\n",i,a,b,a*b);
            }
        }
    }
}

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <gmp.h>

int main(int argc,char *argv[])
{
    mpf_t mpfVal,mpf1;
    unsigned long i;

    mpf_set_default_prec(9000);
    mpf_init_set_ui(mpf1,1);
    printf ("%ld\n",mpf_get_default_prec());

    for (i=997; i>=997; i--) {
        mpf_init(mpfVal);
        mpf_div_ui(mpfVal,mpf1,i);
        printf("%ld: ",i);
        (void) mpf_out_str(stdout,10,2000,mpfVal);

        mpf_clear(mpfVal);
    }
}

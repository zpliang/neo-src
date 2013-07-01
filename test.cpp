#include "include/testinclude.h"





int main (void) {
    int iy, im, id, j;
    double d1, d2;
    iy=2013;
    im=7;
    id=1;
    printf("%4d/%2.2d/%2.2d\n",iy,im,id);
    j=iauCal2jd(iy, im, id, &d1, &d2);
    printf ( "%9.1f +%13.6f =%15.6f\n", d1, d2, d1 + d2 );











}

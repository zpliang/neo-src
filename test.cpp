#include "include/testinclude.h"





int main (void) {

/////////////////////////// test 1 /////////////////////
    int iy, im, id, j;
    double d1, d2, fd;
    iy=2013;
    im=7;
    id=1;
    // printf("%4d/%2.2d/%2.2d\n",iy,im,id);
    j=iauCal2jd(iy, im, id, &d1, &d2); //d2 is mjd
    // printf ( "%9.1f +%13.6f =%15.6f\n", d1, d2, d1 + d2 );
    j=mjd2yd(d2,iy,id);
    // printf ( "year is %4d, doy is %3d \n",iy,id);
    j=iauJd2cal(d1,d2,&iy,&im,&id,&fd);
    // printf ( "mjd=%8f => %4d/%02d/%02d    %4.4f\n", d2, iy,im,id,fd);
    d2=yd2mjd(2013,182);
    // printf ( "mjd=%8f \n",d2);
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////




/////////////////////////////////////////////////





}

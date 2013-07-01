// mjdyd.cpp
#include "../include/testinclude.h"

double yd2mjd(int yr, int doy){
	double djm0,mjd1;
	if(yr<100)yr+=2000;//10.23
    iauCal2jd(yr,1,1,&djm0, &mjd1);
    // jday(yr, 1, 1, 0, 0, 0.0, jd);  
	double mjd = mjd1 + doy -1;
    // printf("yd2mjd yr=%d,mjd=%lf\n",yr,mjd);
	return(mjd);
}
int mjd2yd(const double mjd, int &yr, int &doy){
int err=0;
	double mjd2000_0=51544;
	yr = 2000 + (int)floor((mjd-mjd2000_0)/365);//get year number.
	doy =(int)(mjd-yd2mjd(yr,0));//subtract by beginning of year
return(err);
}


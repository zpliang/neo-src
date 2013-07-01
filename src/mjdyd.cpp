// mjdyd.cpp

double yd2mjd(int yr, int doy){
	double jd;
	if(yr<100)yr+=2000;//10.23
	jday(yr, 1, 1, 0, 0, 0.0, jd);//printf("yd2mjd yr=%d,jd=%lf\n",yr,jd);
	double mjd = jd -Jd2Mjd + doy -1;
	return(mjd);
}
int mjd2yd(const double mjd, int &yr, int &doy){
int err=0;
	double mjd2000_0=51544;
	yr = 2000 + (int)floor((mjd-mjd2000_0)/365);//get year number.
	doy =(int)(mjd-yd2mjd(yr,0));//subtract by beginning of year
return(err);
}


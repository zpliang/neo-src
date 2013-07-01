#ifndef h_time_fun_h
#define h_time_fun_h

#include <stdio.h>
#include <math.h>
#include "./common-constant.h"

// dependency
void    jday(int year, int mon, int day, int hr, int minute, double sec, double& jd);
//void invjday(double jd, int& year, int& mon, int& day, int& hr, int& minute, double& sec);


//~ time system
int jd2ept(double &mjdn,double &sod,const double  jd);//jdn as unsigned long
double ept2jd(double &jd,const double  mjdn,const double  sod);//jdn as unsigned long
double yd2mjd(int yr, int doy);
int mjd2yd(const double mjd, int &yr, int &doy);
double mjday(int year, int mon, int day, int hr, int minute, double sec);
double hms2sod(int hr, int minute, double sec);
double jd2radgast(const double  jd, const double  Eps, const double  dPsi);
double jd2radgast_2(const double jd, const double Eps, const double dPsi, const double dut1);//o=f(i,i,i)
double jd2radgmst_2(const double jd, const double Eps, const double dPsi, const double dut1);//o=f(i,i,i)



#endif



//version 0.11.30

#ifndef h_primit_fun_h
#define h_primit_fun_h

#include <math.h>
#include <stdio.h>
#include "./common-constant.h"

double troprf_c( int  laser, int  iobs, double  fld,  double   p,  double 	t,  double   w,  double   sel,  double   hsta,  double   slat );
void    jday(int year, int mon, int day, int hr, int minute, double sec, double& jd);
void invjday(double jd, int& year, int& mon, int& day, int& hr, int& minute, double& sec);

//~ time system
//~ int jd2ept(double &mjdn,double &sod,const double  jd);//jdn as unsigned long
//~ double ept2jd(double &jd,const double  mjdn,const double  sod);//jdn as unsigned long
//~ double yd2mjd(int yr, int doy);
//~ int mjd2yd(const double mjd, int &yr, int &doy);
//~ double mjday(int year, int mon, int day, int hr, int minute, double sec);
//~ double hms2sod(int hr, int minute, double sec);
//~ double jd2radgast(const double  jd, const double  Eps, const double  dPsi);
//~ double jd2radgast_2(const double jd, const double Eps, const double dPsi, const double dut1);//o=f(i,i,i)
//~ double jd2radgmst_2(const double jd, const double Eps, const double dPsi, const double dut1);//o=f(i,i,i)
	
	
	
//~ coordinate system
//~ int tiny_pole_shift3(double vec[3], const double  shift[]);
//~ int common_rot3_z(double vec[], const double  angrad);
//~ int common_rot3_y(double vec[], const double  angrad);
//~ int common_rot3_x(double vec[], const double  angrad);

//~ int common_cartes3_to_polar(const double  car[], double pol[]);// f(i, o)
//~ int cartes3_to_ah(const double car[], double rae[]);
//~ int teme2pef(double vec[], const double  gmstrad);// f(i/o, i)
//~ int pef2tef(double vec[], const double  polexy[]);// f(i/o, i)
//~ int uod2tef(double vec[], const double  gstrad, const double  polexy[]); // f(i/o,i,i)
//~ int tef2slf(double vec3[], const double  sta_vec3[], const double  sta_geo2[]);
//~ int tef2uod(double vec[], const double  gstrad, const double  polexy[]); // f(i/o,i,i)
//~ int teme2meme(double vec[], const double raddEps, const double raddPsi);// (i/o, i,i)
//~ int meme2teme(double vec[], const double raddEps, const double raddPsi);
//~ int teme2meme_m(double vec[], const double raddEps, const double raddPsi);// (i/o, i,i)
//~ int meme2j2000(double vec[], const double eu1, const double eu2, const double eu3);
//~ int j2k2meme(double vec[], const double eu1, const double eu2, const double eu3);
//~ int j2k2tef(double vec[], const double mjd, const double eop[]);
//~ 

//~ double vector manipulation
//~ int double_vec_add(double vec1[], const double vec2[], const int n);
//~ int double_vec_add(double vec1[], const double vec2[], const double vec3[], const int n);
//~ int double_vec_assign(double vec2[], const double vec1[], const int n);
//~ int double_vec_perturb(double vec[], const double delta, const int k);
//~ int double_vec_subtract(double vec1[], const double  vec2[], const int n);
//~ int double_vec_subtract(double vec1[], const double vec2[], const double vec3[], const int n);
//~ int double_vec_scaling(double vec[], const double  scale, const int n);

//~ format driver
//~ int extract_Mrec(const char longstr[], int &nYoc, int &nDoy, double &fsod, 
				//~ double &fAz, double &fEl, double &fR, double &p, double &T, double &rh);
//~ int extract_tbrec_1(const char longstr[], int &nYoc, int &nDoy, double &fsod, 
				//~ double &fAz, double &fEl, double &fR, double &p, double &T, double &rh);
//~ int extract_tbrec_2(const char longstr[], 										double &fsod, 
				//~ double &fAz, double &fEl, double &fR, double &p, double &T, double &rh);
//~ int extract_tbhead_1(const char longstr[], double &mjdn);

//~ misc
int refr_cor(double &range, double &el, const double  p, const double  kT, const double  rh, 
						const double  hsta, const double  stalatd);//f(o,i/o,iiiii)

#endif


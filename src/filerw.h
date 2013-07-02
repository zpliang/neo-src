#ifndef file_rw_h
#define file_rw_h

#include <math.h>


#include "./Rec3.h"
#include "./Arr2.h"
#include "./common-constant.h"
#include "./primit-fun.h"

//#define T_ARRAY C Array2
typedef CArray2 T_ARRAY;
typedef CFile3	T_FILE;

// dependency
int tef2slf(double vec3[], const double  sta_vec3[], const double  sta_geo2[]);
int cartes3_to_ah(const double car[], double rae[]);
int mjd2yd(const double mjd, int &yr, int &doy);
double yd2mjd(int yr, int doy);
int jd2ept(double &mjdn,double &sod,const double  jd);//jdn as unsigned long


// read
int read_sta_dat_1(const CFile3 &datfile, double prmt[], char m2s[]);

int read_eop_dat	(const CFile3 &eopfile, const double jd, double eop[]);
int read_eop_dat_2	(const CFile3 &eopfile, const double jd, double eop[]);
int read_eop_dat_3	(const CFile3 &eopfile, const double jd, double eop[]);

// transfer
int CPF2Amxyz(const CFile3 &cpffile,  T_ARRAY &Amxyz);
int FR2Amrae(const CFile3 &m2file, T_ARRAY &Amrae);
int hermite (const int ityp, const double x[], const double y[], const double z[], 
		const int nmax, const int nval, const double xp, double &yp, double &zp);
int lagrange10_1(const double x[], const double y[], const double xp, double &yp);
int interp_mabc_1(const double mjd, const T_ARRAY &Amabc, const unsigned n, double mdes[] );
int interp_mabc_2(const double mjd, const double m[],
			const double a[], const double b[], const double c[], double mdes[] );
int interp_mabc_3(const double mjdA[], const unsigned int len,
			const T_ARRAY Amabc, const unsigned n, T_ARRAY &dAmxyz );
int interp_mabc_4(const double mjdA[], const unsigned int len,
			const T_ARRAY &Amabc, const unsigned n, T_ARRAY &dAmxyz );
int mxyz2mobs(const double mxyz[], const double pm[], double mrae[]);

// write
int write_merit_II(const double jd, const double rae[], 
					const double satid,
					const char s1[], const char s2[], char out[]);//SI,range=mUs
					
int write_merit_II_2(const double jd, const double sod, const double rae[], 
					const double satid,
					const char s1[], const char s2[], char out[]);
// extract					
int extract_Mrec_1(const char longstr[], 
				int &nYoc, int &nDoy, double &fsod, 
				double &fAz, double &fEl, double &fR, 
				double &p, double &T, double &rh);//version 0.09.10b turn to SI's
double* extract_Mrec_2(const char longstr[], double mrae[]);//keep t,r,a,e only.
				
int extract_tbrec_1b(const char longstr[], 
				int &nYoc, int &nDoy, double &fsod, 
				double &fAz, double &fEl, double &fR, 
				double &p, double &T, double &rh);
int extract_tbrec_2b(const char longstr[], 
				double &fsod, 
				double &fAz, double &fEl, double &fR, 
				double &p, double &T, double &rh);int extract_tbhead_1b(const char longstr[], double &mjdn);
int extract_tbhead_1b(const char longstr[], double &mjdn);				

int extract_CPF_rec_1(const char longstr[], double txyz[]);//t in mjd


#endif
				




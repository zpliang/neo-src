//version 1.04.12
// easily shared common functions
// para's are in elementary data types.

#include "primit-fun.h"



int refr_cor(
double &range, double &el, 
const double p, const double kT, const double rh, 
const double hsta, const double stalatd){//f(o,i/o,iiiii)
int err=0;
	double ct = kT - 273.15;
	//the "6.1121...." is saturated vapor pressure of water.
	// w is partial pressure of water vapor.
	double w = rh * 6.1121 * exp(( 18.678-(ct/234.5) )*( ct/(257.14+ct) )); 
	double fld = 1.0257;// see f(lambda) in li jisheng p.44
	double sel = sin(el);
	double slat = sin(stalatd);
	
	range 	+= 6.6e-3 *	troprf_c(1, 1, fld, p, kT, w, sel, hsta, slat);	 //transfer to mUs
	el 		+=		troprf_c(1, 4, fld, p, kT, w, sel, hsta, slat);
return(err);
}


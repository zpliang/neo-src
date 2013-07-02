#ifndef h_coord_fun_h
#define h_coord_fun_h

#include <stdio.h>
#include <math.h>
#include "./common-constant.h"

// dependency
int double_vec_subtract(double vec1[], const double  vec2[], const int n);
double jd2radgmst_2(const double jd, const double Eps, const double dPsi, const double dut1);//o=f(i,i,i)
	

//~ coordinate system
int tiny_pole_shift3(double vec[3], const double  shift[]);
int common_rot3_z(double vec[], const double  angrad);
int common_rot3_y(double vec[], const double  angrad);
int common_rot3_x(double vec[], const double  angrad);

int common_cartes3_to_polar(const double  car[], double pol[]);// f(i, o)
int cartes3_to_ah(const double car[], double rae[]);
int teme2pef(double vec[], const double  gmstrad);// f(i/o, i)
int pef2tef(double vec[], const double  polexy[]);// f(i/o, i)
int uod2tef(double vec[], const double  gstrad, const double  polexy[]); // f(i/o,i,i)
int tef2slf(double vec3[], const double  sta_vec3[], const double  sta_geo2[]);
int tef2uod(double vec[], const double  gstrad, const double  polexy[]); // f(i/o,i,i)
int teme2meme(double vec[], const double raddEps, const double raddPsi);// (i/o, i,i)
int meme2teme(double vec[], const double raddEps, const double raddPsi);
int teme2meme_m(double vec[], const double raddEps, const double raddPsi);// (i/o, i,i)
int meme2j2000(double vec[], const double eu1, const double eu2, const double eu3);
int j2k2meme(double vec[], const double eu1, const double eu2, const double eu3);
int j2k2tef(double vec[], const double mjd, const double eop[]);

#endif//h_coord_fun_h


#ifndef h_test_include_h
#define h_test_include_h

#include <stdio.h>
#include <math.h>
#include "sofa.h"
#include "sofam.h"

//#include "time-fun.h"
double yd2mjd(int yr, int doy);
int mjd2yd(const double mjd, int &yr, int &doy);

//#include "coord-fun.h"
int common_rot3_x(double vec[], const double  angrad);
int common_rot3_z(double vec[], const double  angrad);
int common_cartes3_to_polar(const double  car[], double pol[]);// f(i, o)
int cartes3_to_ah(const double car[], double rae[]);

//#include "double-vec.h"
int double_vec_subtract(double vec1[], const double  vec2[], const int n);
int double_vec_subtract(double vec1[], const double vec2[], const double vec3[], const int n);

//#include "common-constant.h"
#define Mpi		3.141592653589793
#define M_invSpeedOfLight	3.33564095e-3	// 1 / 299.792458 mUs*m-1
#define M_rad2deg		57.2957795		// 180 deg /pi rad
#define M_deg2rad		0.017453292519943 // pi/180.0;


#include "../src/Rec3.h"

#include "../src/Arr2.h"

//#include "filerw.h"
typedef CArray2 T_ARRAY;
int CPF2Amxyz(const CFile3 &cpffile,  T_ARRAY &Amxyz);
int read_sta_dat_1(const CFile3 &datfile, double prmt[], char m2s[]);
int mxyz2mobs(const double mxyz[], const double pm[], double mrae[]);


// sod_to_hms.cpp
int sod_to_hms(double sod, int &h, int &m, int &s);

#endif


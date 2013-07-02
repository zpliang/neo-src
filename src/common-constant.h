//version 0.11.30

#ifndef h_common_constant_h
#define h_common_constant_h

//#include "common-type.h"

//mathematical, physical and geological constants
#define	EARTHRADIUS 6378.00
#define OBLIQUITY_deg	23.4392810

//chrono
#define	M_sec2min	0.0166666667	//==1.0/60
#define M_sec2day	1.157407407407407e-5	// 1.0/86400
#define M_day2min	1440.0		// 60*24
#define M_day2sec	86400.0
#define M_k			1000.0
#define Jd2Mjd		2400000.5
//angle
#define	M_pi		3.14159265358979
#define	M_EarthRotate	7.292115e-5	//  rad/s
#define M_deg2rad		0.017453292519943 // pi/180.0;
#define M_rad2deg		57.2957795		//180/pi
#define M_asc2rad		4.848136812e-6	// arcsec to rad
#define M_invSpeedOfLight	3.33564095e-3	// 1 / 299 792 458 mUs*m-1

//////legacy
#define Marcmin2rad 	0.0002908882086657216
#define Marcsec2rad 	4.84813681109536e-6

//time
#define Mhr2deg		15.0
#define Mhr2rad		0.2617993877991494
#define Mmin2rad	4.363323129985823e-3
#define Msec2rad	7.272205216643038e-5

#define Mrad2deg		57.29577951308232
#define Mrad2arcsec		206264.806247096352 //Mrad2deg * Mdeg2arcsec
#define Mrad2hr		3.819718634205488
#define Mpi		3.141592653589793

#define Mdeg2rad 	0.017453292519943295
#define Mdeg2arcsec 3600.0
#define M_arcsec2deg  2.77777778e-4 //   1/3600

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

//--

//system parameters
#define 	EPS 		0.0001		//tolerance ratio
#define 	DELTA		0.001		//variation ratio 
#define 	inv2DELTA	500		//inverse 2*DELTA
#define 	N_X_Dim		7		//dimension of X state or obt-elm
#define 	N_Y_Obs		3		//dimension of Y obs data
#define		N_m2_rows	40000
#define		N_m2_cols	135

//mode parameter
#define	M_Control_Mode	4	
	// specifying controller mode for upd_X()
	// 1 for ignoring previous data
	// 2 for equal weighing prev. data.
	// 3 for differently weighing prev. data.
	// 4 for test mode. change is little.
//static EOP eop;

//static 
//const Tefvec CHO = {
//	{-2674377.0, 3757198.0, 4391503.0},
//	125.4433	* M_deg2rad,
//	43.7905		* M_deg2rad,
//	268.3 };

//CHO.pos[0]	=	-2674377.0;
//CHO.pos[1]	=	3757198.0;
//CHO.pos[2]	=	4391503.0;
//CHO.longtd	= 125.4433	*M_deg2rad;
//CHO.latitd	= 43.7905	*M_deg2rad;
//CHO.hsta	= 268.3;
//     City or Town             : CHANGCHUN
//     State or Province        : JILIN
//     Country                  : CHINA
//     Tectonic Plate           : EURASIAN
//     Approximate Position (ITRF)
//       X coordinate (m)       : -2674377.0
//       Y coordinate (m)       : 3757198.0
//       Z coordinate (m)       : 4391503.0
//       Latitude (N is +)      : +434725.80	43.7905deg
//       Longitude (E is +)     : +1252635.88	125.4433deg
//       Elevation (m,ellips.)  : 268.3


#endif


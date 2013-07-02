//for CPF to tb only.
#include "./coord-fun.h"


int tiny_pole_shift3(double vec[3], const double shift[]){// f(i/o,i) shift in arcsec.
int err=0;
	double old_x = vec[0];		double shift_xro_rad = shift[0]*Marcsec2rad;
	double old_y = vec[1];		double shift_yro_rad = shift[1]*Marcsec2rad;
	double old_z = vec[2];

	double new_x =		old_x	+		shift_xro_rad * old_z ;				//B =[	1		0		xro_rad;
	double new_y =		old_y	-		shift_yro_rad * old_z ;				//		0		1		-yro_rad;
	double new_z = - old_x * shift_xro_rad + old_y * shift_yro_rad + old_z ;	//		-xro_rad	yro_rad		1	]

	vec[0]=new_x;
	vec[1]=new_y;
	vec[2]=new_z;

return(err);
}

int common_rot3_z(double vec[], const double angrad){// f(i/o,i)
int err=0;
	double x2 = vec[0];
	double y2 = vec[1];
	double z2 = vec[2];

	double costh = cos(angrad);
	double sinth = sin(angrad);
	double x	=	costh*x2	+	sinth*y2		;
	double y	=	-sinth*x2	+	costh*y2		;
	double z	=								z2	;

	vec[0] = x;
	vec[1] = y;
	vec[2] = z;

return(err);
}
int common_rot3_y(double vec[], const double angrad){// f(i/o,i)
int err=0;
	double x2 = vec[0];
	double y2 = vec[1];
	double z2 = vec[2];

	double costh = cos(angrad);
	double sinth = sin(angrad);
	double x	=	costh*x2		-	sinth*z2	;
	double y	=				y2					;
	double z	=	sinth*x2		+	costh*z2	;

	vec[0] = x;
	vec[1] = y;
	vec[2] = z;

return(err);
}

int common_rot3_x(double vec[], const double angrad){// f(i/o,i)
int err=0;
	double x2 = vec[0];
	double y2 = vec[1];
	double z2 = vec[2];

	double costh = cos(angrad);
	double sinth = sin(angrad);
	//the matrix is R1	=	[	1		0		0		]
						//	[	0		cos		sin		]
						//	[	0		-sin	cos		]

	vec[0] = x2									;
	vec[1] =			costh*y2	+	sinth*z2	;
	vec[2] =			-sinth*y2	+	costh*z2	;
return(err);
}

int common_cartes3_to_polar(const double car[], double pol[]){// f(i, o)
int err=0;

	double x2 = car[0];
	double y2 = car[1];
	double z2 = car[2];

	double r2		=	sqrt(x2*x2+y2*y2+z2*z2);
	double phi2		=	asin(z2/r2);
	double theta2	=	atan(y2/x2);

	if (x2<0)	theta2 += Mpi;	//2,3 quadrant.
	else if (y2<0)	theta2 += 2*Mpi;	//4 quadrant.

	pol[0] = r2;
	pol[1] = phi2;
	pol[2] = theta2; // [0,2*pi]

return(err);
}
int cartes3_to_ah(const double car[], double rae[]){// to range,azimuth,elevation
int err=0;	//range is meter(depend on car), az,el in rad
	double pol[3];
	common_cartes3_to_polar(car,pol);
		double range = pol[0];//rea=(rho, phi, theta)
		double az	= Mpi/2 - pol[2];//theta
		  if (az<0.0) az+= 2*Mpi;//3of4 to +=. but pi is not precise.
		//this az is 0deg=north, 90deg=east.
		double el	= pol[1];//phi
	rae[0] = range;
	rae[1] = az;
	rae[2] = el;
return(err);
}
int teme2pef(double vec[], const double gmstrad){// f(i/o, i)
int err=0;
	common_rot3_z(vec,gmstrad);//position vector rotation.
	
return(err);
}

int pef2tef(double vec[], const double polexy[]){// f(i/o, i)
int err=0;
	tiny_pole_shift3(vec,polexy);
return(err);
}

int uod2tef(double vec[], const double gstrad, const double polexy[]){ // f(i/o,i,i)
int err=0;
	teme2pef(vec,gstrad);
	pef2tef(vec, polexy);
return(err);
}
int tef2uod(double vec[], const double  gstrad, const double  polexy[]){// f(i/o,i,i)
int err=0;
	double invgst;
	double invpol[2]; 
	//inverse var's.
	invgst=-1.0*gstrad;
	invpol[0]= - polexy[0];
	invpol[1]= - polexy[1];
	
	pef2tef(vec, invpol); //and exchange.
	teme2pef(vec,invgst);
return(err);
}
int tef2slf(double vec3[], const double sta_vec3[], const double sta_geo2[]){// f(i/o,i,i) SI confirmed
int err=0;
// mind the units. use metre, rad.
	double_vec_subtract(vec3, sta_vec3, 3);
	double sta_lgtd = sta_geo2[0];
	double sta_latd = sta_geo2[1];//printf("tef2slf lgtd=%lf latd=%lf\n",sta_lgtd,sta_latd); 
	
	common_rot3_z(vec3, Mpi/2.0 + sta_lgtd);
	common_rot3_x(vec3, Mpi/2.0 - sta_latd);//x axis in direction east. y north.
	//printf("tef2slf 
return(err);
}




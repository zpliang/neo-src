//c----------version 0.7.28--------------------------------------------------------------------
#include <math.h>
double troprf_c( int  laser, int  iobs, double	fld, double  p, double	t, double  w, double  sel, double  hsta, double  slat )
{
//c...purpose:	compute the tropospheric refraction correction for
//c  			observations using radio or optical frequencies
//c
//c...adapted for Shorde by R Eanes and J Ries
//....translated to C by zpl
//c...input parameters:
//c
//c  laser	 0 = radio frequency	1 = optical frequency
//c  iobs	 1 = range	  4 = laser elevation	 5 = radar altimeter
//c  fld	 parameter depending on optical frequency (for laser only)
//c  p		 atmospheric pressure in millibars
//c  t		 atmospheric temperature in degrees kelvin
//c  w		 water vapor pressure in millibars
//c  sel	 sine of elevation angle (should be 1.0 for altimeter)
//c  hsta	 station height in meters (should be 0.0 for altimeter)
//c  slat	 sine of station latitude (for laser range only)
//c
//c
//c...references:
//c
//c  		 c. Goad and L. Goodman, a modified hopfield troposphere
//c  			refraction correction model, Dec. 1974.
//c  			(very old)
//c
//c  		 Marini and Murray, correction to laser range tracking
//c  			data for atmospheric refraction at elevations above
//c  			10 degrees, GSFc report x-591-73-351, Nov. 1973.
//c
//c  		 J. Saastamoinen, atmospheric correction for the
//c  			troposphere and stratosphere in radio ranging
//c  			of satellites, geophysical monograph #15, american
//c  			geophysical union, Washington, D.c., William byrd
//c  			press, richmond, va, 1972.
//c  			(at elevations above 10 degrees)
//c
//		implicit real *8 (a-h,o-z)
	bool   wet;
	int i;
	double alpha[ 10 ], 
			rn[ 10 ];
//c
	double b0 = 7.839257591e-5, 
			ae = 6378.155e+0;
//c
//c
	double troprf = 0.0e+0;
	double cel, 
			tkelvn, 
			dev, 
			ht, 
			rtop;
	double a, 
			a2, 
			ab, 
			b, 
			twob, 
			fourb, 
			b2, 
			c, 
			c2phi;
	double dr, 
			fph, 
			q, 
			xns;




	if( sel <= 0.0e+0 )
		return ( troprf );
//c
//c...check for missing atmospheric data
	if( p == 0.0e+0 )
		p = 1013.5e+0  - 0.113e+0 * hsta;
	if( t == 0.0e+0 )
		t = 293.16e+0;
	if( w == 0.0e+0 )
		w = 9.35e+0;
//c
//c...branch according to observation type
	if( iobs == 1 )
		goto  Flag_10;											//	  go to 2 goto								    
	if( iobs == 4 )
		goto  Flag_100;
	if( iobs == 5 )
		goto  Flag_80;
	return ( troprf );
//c
//c
//c...branch for laser range
Flag_10:
	if( laser != 0 )
		goto  Flag_90;
//c
//c
//c...correction to range observation using radio frequencies
	cel    = sqrt( 1.0e+0  - pow(sel,2) );
	tkelvn = 1.0e+0 / t;
	wet    = ( w > 0.0e+0 );
//c
//c...compute dry parameters
	dev    = 77.624e-6 * tkelvn;
//c
//c...compute height of troposphere with saastamoinen 90 degree correction
	ht	   = 1.1385e-5 / dev;
	dev    = dev * p;
	goto  Flag_40;
//c
//c...compute wet parameters
Flag_30:
	wet = 0;
	dev = tkelvn * ( 371900.0e-6 * tkelvn - 12.92e-6 );
	ht	= 1.1385e-5 * ( 1255.0e+0 * tkelvn + 0.05e+0 ) / dev;
	dev = dev * w;
//c
//c...the following are used for dry and wet component computation
Flag_40:
	rtop = sqrt( pow(( ae + ht ), 2)  - pow(( ae * cel ), 2) ) - ae * sel;
	a		= -sel / ht;
	b		= -b0 * pow( cel , 2 ) / ht;
	a2		= pow(a , 2);
	b2		= pow(b , 2);
	ab		= a * b;
	twob	= b + b;
	fourb	= twob + twob;
	rn[ 1 ] = rtop;
	for( i = 1; i <= 8; i++ )								//	< >  										    
		rn[ i + 1 ] = rn[ i ] * rtop;
//c
//c...compute component of correction
	alpha[ 2 ] = a + a;
	alpha[ 3 ] = a2 + a2 + fourb / 3.0e+0;
	alpha[ 4 ] = a * ( fourb - b + a2 );
	alpha[ 5 ] = 0.2e+0 * pow(a2 , 2 ) + 2.4e+0 * a2 * b + 1.2e+0 * b2;
	alpha[ 6 ] = twob * alpha[ 4 ] / 3.0e0;
	alpha[ 7 ] = b2 * ( 6.0e+0 * a2 + fourb ) * 1.42857142857e-1;
	alpha[ 8 ] = 0.0e+0;
	alpha[ 9 ] = 0.0e+0;
	if( b2 < 1.0e-35 )
		goto  Flag_60;
	alpha[ 8 ] = ab * b2 * 0.5e0;
	alpha[ 9 ] = pow(( b2 / 3.0e+0 ) , 2);
Flag_60:
	dr = rtop;
	for( i = 2; i < +9; i++ )
		dr = dr + alpha[ i ] * rn[ i ];
	troprf = troprf + dr * dev * 1000.0e+0;
	if( wet )
		goto  Flag_30;
	return ( troprf );
//c
//c
//c...correction to radar altimeter using modified saastamoinen model
Flag_80:
	troprf = 0.002277e+0 * ( p + w * ( 0.05e+0	+ 1255.0e+0 / t ) );
	return ( troprf );
 //c
//c
//c...correct range observation using only zenith refraction value
//c  (zenith correction in mm has been stored in place of pressure)
Flag_90:
	if( p > 1500.0e+0 )
	{
		cel    = sqrt( 1.0e+0  - pow(sel , 2) );
		troprf = ( 1.0e-3 * p ) / ( sel + 1.0e-3 * cel / sel );
	}
	else
	{
//c
//c...correction to laser range observation using Marini and Murray model
		a = 0.002357e+0 * p + 0.000141e+0 * w;
		c2phi  = 1.0e+0 - 2.0e+0*pow(slat, 2);
		  c  	 = 1.163e+0 - 0.00968e+0*c2phi - 0.00104e+0*t\
					+ 0.00001435e+0*p;
		b = 1.084e-8 * p * t * c + 9.468e-8 * p * p / ( t * ( 3.0e+0  - 1.0e+0 / c ) );
		fph = 1.0e+0  - 0.0026e+0 * c2phi - 3.1e-7 * hsta;
		troprf = fld * ( a + b ) / ( fph * ( sel + b / ( ( a + b ) * ( sel + 0.01e+0 ) ) ) );
	}
	return ( troprf );
//c
//c
//c...correction to elevation observation using Marini and murray model
Flag_100:
	xns = 80.343e+0 * fld * ( p - 0.140647e+0 * w ) / t;
	q	= 1.0e+0 / ( sel + sqrt( pow(sel , 2 ) + 0.0025284e+0 ) );
	cel = sqrt( 1.0e+0  - pow(sel , 2) );
	troprf = q * cel * ( 6.011612e-4  + 1.92056e-6 * ( xns - 313.0e+0 ) );
	return ( troprf );
//c
}																//c.....end troprf								    

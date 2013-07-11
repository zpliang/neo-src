// purpose: convert CPF file to tb(SLR guidance) file. 

// [*] first we convert CPF file to TEF format (time, x, y, z)

// [*] then we convert TEF format to SLF(station-centered frame) (time, az, el, rg)

// [*] last, add atmospheric compensation.

// usage: [==] <cpf name> <station file> <begin mjd> <day span>

#include "include/testinclude.h"

#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>
#include <gmpxx.h>

// #include <iostream>
#include <string> //STL

using namespace std;


// GMP functions
int
hermite_gmp (const int ityp, 
	const  mpf_class  x[], const  mpf_class  y[], const  mpf_class  z[], 
		const int nmax, const int nval, 
		const  mpf_class  xp,  mpf_class  &yp,  mpf_class  &zp);
int interp_mabc_v(const double mjd, const T_ARRAY &Amabc, const unsigned n, double mdes[] );
int interp_mabc_vvv(const double mjdA[], const unsigned int len,
			const T_ARRAY &Amabc, const unsigned n, T_ARRAY &dAmxyz );
int interp_mabc_vb(const mpf_class mp, const T_ARRAY &Amabc, const unsigned n, mpf_class m7des[]);
int interp_mabc_vvvb(const mpf_class mjdA[], const unsigned int len,
			const T_ARRAY &Amabc, const unsigned n, T_ARRAY &dAmxyz );
            
int write_tb_line_1(const double fmjd, const double sod, const double rae[], char* tbline);

int main (int argc, char** argv) {
int err=0;
	unsigned long nCpf;
	unsigned long len;
	unsigned long i,j;
	double prmt[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};	//for(i=0;i<14;++i)prmt[i]=0.0;
	char cpfname[100]="./ajMar1_7.hts";
    char stfname[100]="./chan7237.txt";    
	char m2str[10], sdump[50], tbline[100];
    bool bGap=1;
	mpf_class  MjdBegin, MjdEnd, Freq, Span, dtmjd, zp;
	mpf_class *MjdSeries; 
	
//---------argument parser---------------	
	if(argc>2){
		strncpy(cpfname,argv[1],99);
        strncpy(stfname,argv[2],99);
	}//default has been set. 
	if(argc>3) gmp_sscanf(argv[3],"%Ff",&MjdBegin);
	else MjdBegin = 55256.0;// use mjd0!
	if(argc>4) gmp_sscanf(argv[4],"%Ff",&Span);
	else Span = 1;



//---------------Class objects---------
    Freq=86400;
	dtmjd=1.0/Freq;
	nCpf=5000;// for Ajisai, 360 lines/day.
	zp=(Span*Freq  +1 ); len = zp.get_si();// reserve output budget
	MjdSeries = new mpf_class[len];

	CFile3 cpffile(cpfname,nCpf);// parse file
	CArray2 Amxyz(nCpf);
	CPF2Amxyz(cpffile, Amxyz);//conversion
	CArray2 ATefSeries(len+500);  //allocate
	CFile3 datfile(stfname, 30); // station info
	read_sta_dat_1(datfile, prmt, m2str);	
//---------------print TEF coordinate from CPF--------	
	for(i=0;i<len;i++) MjdSeries[i] = MjdBegin + i*dtmjd; 

	interp_mabc_vvvb(MjdSeries, len, Amxyz, 5, ATefSeries );// Interpolate 
//	ATefSeries.print();//Array offers print function.
// now we have ATefSeries.




// /////////////////////////// test 1 /////////////////////
    int iy, im, id, jerr;
    double d1, d2, fd;
    iy=2013;
    im=7;
    id=1;
    // printf("%4d/%2.2d/%2.2d\n",iy,im,id);
    jerr=iauCal2jd(iy, im, id, &d1, &d2); //d2 is mjd
    // // printf ( "%9.1f +%13.6f =%15.6f\n", d1, d2, d1 + d2 );
    // j=mjd2yd(d2,iy,id);
    // // printf ( "year is %4d, doy is %3d \n",iy,id);
    // j=iauJd2cal(d1,d2,&iy,&im,&id,&fd);
    // // printf ( "mjd=%8f => %4d/%02d/%02d    %4.4f\n", d2, iy,im,id,fd);
    // d2=yd2mjd(2013,182);
    // // printf ( "mjd=%8f \n",d2);
// /////////////////////////////////////////////////////////
    
    
/////////////////////////////////////////TEF to tb line////////////////////////
	char inputstr[500];
	// int i;
	double tefpos[4], tefvel[3], mrae[4];
	double ElMin=5.0;
	// double satid=8606101.0;
	// double RngErr=0.0;
	double sod;
	
	// printf("argument:%s\n",argv[1]);
	//---------argument parser---------------	
	// if(argc>4){
		// sscanf(argv[1],"%lf",&satid);//if(argv[1][0]=='-' && argv[1][1]=='s')
		// strncpy(datname,argv[2],99);
		// sscanf(argv[3],"%lf",&ElMin);
		// sscanf(argv[4],"%lf",&RngErr);
	// }
	// else;//default has been set. 
	

	
    // ----------Loop through ATefSeries ----------------
    for (i=0;i<ATefSeries.nRecNum;i++){
        for (j=0;j<7;j++) tefpos[j]=ATefSeries.body[i].p[j];    //copy from array.
        mxyz2mobs(tefpos,prmt,mrae);// convert to rae. R in seconds.
		if(mrae[3]>ElMin*M_deg2rad){ // elevation threshold
            if (bGap==1) {bGap=0;printf("#T(H:M:S)     AZ(D)      ELV(D)   RANGE(NS)       US         H'          A'       Rate[X]\n");} 
            //when transition, do: print header.
            sod = floor(0.5+(mrae[0]-floor(mrae[0]))*86400.0);
            write_tb_line_1(mrae[0],sod, mrae+1,tbline);
			printf("%s\n",tbline);//direct output
		}
        else { // now is gap time!
            if (bGap==0) {bGap=1;printf("\n");} //when transition, do: insert gap mark.
        }
    }
    
	// do{// read streamed input: four doubles.
		// if(fgets(inputstr,500,stdin) == NULL) break;
		// sscanf(inputstr,"%lf %lf %lf %lf", // %lf %lf %lf", 
			// &tefpos[0], &tefpos[1], &tefpos[2], &tefpos[3]);//, &tefvel[0], &tefvel[1], &tefvel[2]);
		// if(tefpos[0]<=0.0) break;	
		// mxyz2mobs(tefpos,prmt,mrae);// convert to rae. R in seconds.
		// if(mrae[3]>ElMin*M_deg2rad){ // elevation threshold
			// // mrae[1]+=range_perturb_701(RngErr, mrae[0]);
			// // rounded seconds. a shortcut, for integer seconds only! 
			// sod = floor(0.5+(mrae[0]-floor(mrae[0]))*86400.0);
			// // write_merit_II_2(mrae[0]+2400000.5,sod,mrae+1,satid,m2str,sdump,m2line); // convert to meritII line
            // write_tb_line_1(mrae[0],sod, mrae+1,tbline);
			// printf("%s\n",tbline);//direct output
		// }
	// }while(tefpos[0]>0.0);    
    
////////////////////////////////////////    
delete [] MjdSeries;

return(err);
}


int write_tb_line_1(const double fmjd, const double sod, const double rae[], char* tbline);

/*
 T(H:M:S)     AZ(D)      ELV(D)   RANGE(NS)       US         H'          A'       Rate
  8:44:26    35.4522     5.0127    17017243.8    17017.24   5: 0:45    35:27: 8 -5.442775
[sod to hms] [az deg]   [el deg] [range m2ns]    [x 1000]  [deci to sexa] [..]   ["-0.0"]
*/
int write_tb_line_1(const double fmjd, const double sod, const double rae[], char tbline[]){
int err=0;    
    int ihr, imin, isec;
    int iAz_dmsf[4],iEl_dmsf[4];
    double AzDeg,ElDeg,AzRad,ElRad,Rg_ns,Rg_Us,RgRate;
    char AzSign,ElSign;
    
    AzRad=rae[1];
    ElRad=rae[2];
    
    // calculate required values.
    err+=sod_to_hms(sod, ihr,imin,isec);
    AzDeg=AzRad*M_rad2deg;
    ElDeg=ElRad*M_rad2deg;
    Rg_ns=rae[0]*1.0e3;
    Rg_Us=rae[0];   // mxyz2mobs gives 2way Us.
    iauA2af(0,ElRad,&ElSign,iEl_dmsf);
    iauA2af(0,AzRad,&AzSign,iAz_dmsf);
    RgRate=-0.0;
    
    // print values.
    sprintf(tbline," %02d:%02d:%02d %10.4lf %10.4lf %13.1lf %11.2lf  %02d:%02d:%02d   %03d:%02d:%02d %9.5f",
                     ihr,imin,isec, AzDeg,  ElDeg,
                                                    Rg_ns, Rg_Us,   iEl_dmsf[0],iEl_dmsf[1],iEl_dmsf[2],
                                                                                      iAz_dmsf[0],iAz_dmsf[1],iAz_dmsf[2],
                                                                                                     RgRate
                                                                );
    
    
return(err);    
}
int interp_mabc_vb(const mpf_class mp, const T_ARRAY &Amabc, const unsigned n, mpf_class m7des[]){// debugging
// Interpolate from sample array($Amabc) against $mjdp.
// $m7[] stores result.
// input: mjd value, support array of sample, interpolation method type $n, result array.
int err=0;
	mpf_class m0, intv;
	unsigned long index;
	unsigned long i,j;
	long bl_nmjd,bl_nsod;
	mpf_class sobp;
	mpf_class ap, bp, cp, av, bv, cv;
	mpf_class vx, vy, vz, zp;
	//mpf_class mp, mjd;
	mpf_class *m = new mpf_class [n*2];
	mpf_class *sob = new mpf_class [n*2]; //second of block
	mpf_class  *a = new mpf_class [n*2];
	mpf_class  *b = new mpf_class [n*2];
	mpf_class  *c = new mpf_class [n*2];
	mpf_class  *va= new mpf_class [n*2];
	mpf_class  *vb= new mpf_class [n*2];
	mpf_class  *vc= new mpf_class [n*2];
	mpf_class  *z = new mpf_class [n*2];
	bool bErrFlag;
	//for(i=0;i<7;++i)m7des[i]=0.0;
	
	m0   = Amabc.body[0].p[0] ; // find start value of the sample.
	intv = Amabc.body[1].p[0] - m0;//find time interval.

	//mjd = mjdp;
	//index =(unsigned long)floor_gmp((mp-m0)/intv - n);//find base index: beginning of 2n points.
	zp = ((mp-m0)/intv - n); // zp as passer-by
	index = zp.get_si()+1; //gmp_printf("zp %Ff zp.si %ld\n", zp.get_mpf_t(), zp.get_si());
	bErrFlag=0;
	//mp = mjdp; // ap=fa(mp).	
	for(i=0;i<n*2;i++){ // get 2*n base points
		j = i + index; 
		if(i==0){		}
		if(0<=j && j<Amabc.nRecNum){
			m[i] = Amabc.body[j].p[0];
			sob[i] = floor(0.5+(m[i]-m[0])*86400);
			a[i] = Amabc.body[j].p[1];
			b[i] = Amabc.body[j].p[2];
			c[i] = Amabc.body[j].p[3];
			va[i] = Amabc.body[j].p[4];
			vb[i] = Amabc.body[j].p[5];
			vc[i] = Amabc.body[j].p[6];
		}else bErrFlag=1;
	}
	if(bErrFlag){
		printf("#Interp_mabc_6b Error: Array access out of range!\n");
		//mp =-1; 
		ap = -111111; bp = -111111; cp = -111111;
		av = -111111; bv = -111111; cv = -111111;
		err=1; goto exit;
	}
	else{
		zp=floor(m[0]); bl_nmjd = zp.get_si(); // zp as passer-by
		zp=floor(0.5+ (m[0]-bl_nmjd)*86400); bl_nsod = zp.get_si();// zp as passer-by
		sobp=floor((mp - bl_nmjd)*86400 - bl_nsod + 0.5 ); // for tef generation only: use integer second.
		hermite_gmp(-1,sob, a,z,n*2,n*2,sobp, ap, av);
		hermite_gmp(-1,sob, b,z,n*2,n*2,sobp, bp, bv);
		hermite_gmp(-1,sob, c,z,n*2,n*2,sobp, cp, cv);
	}
	m7des[0]=mp;
	m7des[1]=ap;
	m7des[2]=bp;
	m7des[3]=cp;
	m7des[4]=av;
	m7des[5]=bv;
	m7des[6]=cv;
exit:
delete [] m;
delete [] sob;
delete [] a;
delete [] b;
delete [] c;	
delete [] va;
delete [] vb;
delete [] vc;	
delete [] z;
return(err);
}

int interp_mabc_vvvb(const mpf_class mjdA[], const unsigned int len,
			const T_ARRAY &Amabc, const unsigned n, T_ARRAY &dAmxyz ){
int err=0;			
	unsigned int k,i;
	mpf_class Mjd;
	mpf_class mdes[7];
	double D_mdes[7];
	for(k=0;k<len;k++){ // for each element in $mjdA[]
		Mjd = mjdA[k];
		interp_mabc_vb(Mjd, Amabc, n, mdes);
		for(i=0;i<7;i++)D_mdes[i]=mdes[i].get_d();
		dAmxyz.in(D_mdes);
	}
return(err);
}


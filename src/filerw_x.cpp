//version 2011.07.14
//#include "./alllibs.h"
#include "filerw.h"
int read_sta_dat_1(const CFile3 &datfile, double prmt[], char m2s[]){
int err=0;
	unsigned int i;
	char *str;
	char dump[5];
	int end;
	double longtdeg, latitdeg;
	for(i=0,end=0;(end==0)&&(i<datfile.nRecNum);i++){
		str = datfile.body[i].s;
		switch ( str[0] ){
			case 'a': {sscanf(str, "%2s %lf,%lf,%lf",dump, prmt+5, prmt+6, prmt+7);break;};
			case 'b': {sscanf(str, "%2s %lf,%lf,%lf",dump, &longtdeg, &latitdeg, prmt+10);break;};
			case 'c': {sscanf(str, "%2s %lf,%lf,%lf",dump, prmt+11, prmt+12, prmt+13);break;};
			case 'd': {sscanf(str, "%2s ",dump);break;};
			case 'e': {sscanf(str, "%2s %s",dump, m2s	);break;};
			case 'z': {end=1;break;};
			case  '#': {break;};
			default: {printf("station file: fault!");break;};
		};
		//printf("i=%d end=%d str=%s\n",i,end,str);
	};
	prmt[8]=longtdeg*M_deg2rad;
	prmt[9]=latitdeg*M_deg2rad;
	//printf("i=%d, str=%s, m2s=%s\n",i,str,m2s);
return(err);
}

int read_eop_dat(const CFile3 &eopfile, const double jd, double eop[]){
int err=0;// for eop file format 1.
		//int yr, mon, day;
		double mjd, imjd;
		double dd;
		double pmx, pmxe, pmy, pmye, dut1, dut1e, lod, lode, dPsi, dPsie, dEps, dEpse;
		double Bpmx, Bpmy, Bdut1, BdPsi, BdEps;
		char *str;
		char sdump[10];
		unsigned int index;
		const char *formatstring1="%lf %s %lf %lf %lf %lf %s %lf %lf %lf %lf";
		const char *formatstring2="%s %lf %lf %lf %lf %lf %lf %lf %lf %lf";
		
		mjd = jd -2400000.5;
		for(index=0;index<5;index++)eop[index]=0.0;
		
		for(index=0;index<eopfile.nRecNum;){
			str=eopfile.body[index].s;
			sscanf(str+7,"%lf", &imjd);//printf("mjd=%lf,imjd=%lf\n",mjd,imjd);
			dd = mjd-imjd;
			if(dd>0.5) index+=int(dd+0.5);
			else if(dd<-0.5) index+=int(dd-0.5);
			else {
			sscanf(str+7, formatstring1, 
				&imjd,
				sdump, &pmx, &pmxe,
				&pmy, &pmye,
				sdump, &dut1, &dut1e,
				&lod, &lode);
			sscanf(str+94, formatstring2,
				sdump, &dPsi, &dPsie,
				&dEps, &dEpse,
				&Bpmx, &Bpmy,
				&Bdut1, &BdPsi, &BdEps);
			break;
			}
		}
		//printf("imjd=%lf\n",imjd);
	eop[0]=pmx; //arcsec
	eop[1]=pmy; //arcsec
	eop[2]=dut1;	//sec
	eop[3]=OBLIQUITY_deg+dEps*1e-3*M_arcsec2deg;//Eps in deg. dEps in milliarcsec
	eop[4]=dPsi; //milliarcsec
/*
format1
10 1 1 55197.00 I  0.098663 0.000039  0.192890 0.000045  I 0.1140690 0.0000044  0.5206 0.0055 
format2
 I   -64.730    0.243    -5.324    0.127  0.098699  0.192933  0.1140681   -63.846    -4.901  

Data	
Year, Month, Day, Modified Julian Date

PM-x [arcsec], error_PM-x [arcsec],
PM-y [arcsec], error_PM-y [arcsec],
UT1-UTC [seconds], error_UT1-UTC [seconds],
LOD [milliseconds], error_LOD [milliseconds],
dPsi [milliarcsec], error_dPsi [milliarcsec],
dEps [milliarcsec], error_dEps [milliarcsec]
(from Bulletin A)

PM-x [arcsec], PM-y [arcsec], UT1-UTC [seconds],
dPsi [milliarcsec], dEps [milliarcsec]
(from Bulletin B)*/
return(err);
}

int read_eop_dat_2(const CFile3 &eopfile, const double jd, double eop[]){ 
int err=0; //mind the different unit. for eop file format c04
		//int yr, mon, day;
		double mjd, imjd;
		double dd;
		double pmx, pmxe, pmy, pmye, dut1, dut1e, lod, lode, dPsi, dPsie, dEps, dEpse;
		//double Bpmx, Bpmy, Bdut1, BdPsi, BdEps;
		char *str;
		//char sdump[10];
		unsigned int index;
		//const char *formatvalue="%lf %lf %lf %lf %lf %lf %lf";
		//const char *formaterr="%lf %lf %lf %lf %lf %lf";
		
		mjd = jd -2400000.5;
		for(index=0;index<5;index++)eop[index]=0.0;
		
		for(index=0;index<eopfile.nRecNum;){
			str=eopfile.body[index].s;
			sscanf(str+12,"%lf", &imjd);//printf("mjd=%lf,imjd=%lf\n",mjd,imjd);
			dd = mjd-imjd;
			if(dd>0.5) index+=int(dd+0.5);
			else if(dd<-0.5) index+=int(dd-0.5);
			else {
				sscanf(str+12, "%lf %lf %lf %lf %lf %lf %lf", 
					&imjd, &pmx, 	&pmy, &dut1, 	&lod, &dPsi, &dEps);
				sscanf(str+87, "%lf %lf %lf %lf %lf %lf",
					&pmxe, &pmye, &dut1e, &lode, &dPsie, &dEpse);
			break;
			}
		}
		//printf("imjd=%lf\n",imjd);
	eop[0]=pmx; //arcsec
	eop[1]=pmy; //arcsec
	eop[2]=dut1; //sec
	eop[3]=OBLIQUITY_deg+dEps*M_arcsec2deg;//Eps in deg. dEps in arcsec
	eop[4]=dPsi*1e3; //milliarcsec
/*                         EOP (IERS) 05 C04

  
             FORMAT(3(I4),I7,2(F11.6),2(F12.7),2(F11.6),2(F11.6),2(F11.7),2F12.6)
**********************************************************************************
  
      Date      MJD      x          y        UT1-UTC       LOD         dPsi      dEps       x Err     y Err   UT1-UTC Err  LOD Err    dPsi Err   dEpsilon Err
                         "          "           s           s            "         "        "          "          s           s            "         "
     (0h UTC)
2010   1   1  55197   0.098699   0.192933   0.1140681   0.0005535  -0.063846  -0.004901   0.000010   0.000013  0.0001493  0.0000018    0.000263    0.000209

Data	
Year, Month, Day, Modified Julian Date

PM-x [arcsec], error_PM-x [arcsec],
PM-y [arcsec], error_PM-y [arcsec],
UT1-UTC [seconds], error_UT1-UTC [seconds],
LOD [milliseconds], error_LOD [milliseconds],
dPsi [milliarcsec], error_dPsi [milliarcsec],
dEps [milliarcsec], error_dEps [milliarcsec]
(from Bulletin A)

PM-x [arcsec], PM-y [arcsec], UT1-UTC [seconds],
dPsi [milliarcsec], dEps [milliarcsec]
(from Bulletin B)*/
return(err);
}
int read_eop_dat_3(const CFile3 &eopfile, const double jd, double eop[]){ //10.23 tested 
int err=0; //same as _2 but interpolate. for eop file format c04
		double mjd, mjdb, mjdt, imjdb, imjdt;
		double dd, pp;
		double pmxb, pmyb, dut1b, lodb, dPsib, dEpsb;		
		double pmxt, pmyt, dut1t, lodt, dPsit, dEpst;
		double pmxeb, pmyeb, dut1eb, lodeb, dPsieb, dEpseb;
		double pmxet, pmyet, dut1et, lodet, dPsiet, dEpset;
		char *str1, *str2;
		unsigned int index;
		
		mjd = jd -2400000.5; // the corresponding mjd
		mjdb=floor(mjd);  // floor of mjd. base.
		mjdt=mjdb+1.0;  // ceiling of mjd. top.
		pp = mjd - mjdb;  // pp: fraction of the day
				
		for(index=0;index<eopfile.nRecNum;){ // not actually a loop.
		// just to constrain the index value.
			str1=eopfile.body[index].s;	// with rec string
			sscanf(str1+12,"%7lf", &imjdb);	//  find the mjd at point
			//printf("mjd=%lf,imjd=%lf\n",mjd,imjd);
			dd = mjdb-imjdb;	// see the difference in days(and in records)
			if(dd>0.5) index+=int(dd+0.5);	//  try to work out the integer index
			else if(dd<-0.5) index+=int(dd-0.5);	// if |dd|>0.5, loop to try again.
			else {//|dd|<0.5 means the record is found. read this and next record 
				str2=eopfile.body[index+1].s; // str1 and str2 are neighbours.
				sscanf(str1+12, "%lf %lf %lf %lf %lf %lf %lf",  //read bottom eop
					&imjdb, &pmxb, 	&pmyb, &dut1b, 	&lodb, &dPsib, &dEpsb);
				sscanf(str1+87, "%lf %lf %lf %lf %lf %lf",
					&pmxeb, &pmyeb, &dut1eb, &lodeb, &dPsieb, &dEpseb);
				sscanf(str2+12, "%lf %lf %lf %lf %lf %lf %lf", //read top eop
					&imjdt, &pmxt, 	&pmyt, &dut1t, 	&lodt, &dPsit, &dEpst);
				sscanf(str2+87, "%lf %lf %lf %lf %lf %lf",
					&pmxet, &pmyet, &dut1et, &lodet, &dPsiet, &dEpset);
			break; // when found, break.
			}
		}
	if(imjdb!=mjdb || imjdt!=mjdt)
		printf("mjdb=%7.1lf,imjdb=%7.1lf,mjdt=%7.1lf,imjdt=%7.1lf\n",mjdb,imjdb,mjdt,imjdt);
	dd=1.0-pp;
	eop[0]=pmxb*dd+pmxt*pp; //arcsec
	eop[1]=pmyb*dd+pmyt*pp; //arcsec
	eop[2]=dut1b*dd+dut1t*pp; //sec
	eop[3]=OBLIQUITY_deg+(dEpsb*dd+dEpst*pp)*M_arcsec2deg;//Eps in deg. dEps in arcsec
	eop[4]=(dPsib*dd+dPsit*pp)*1e3; //milliarcsec

return(err);
}

int CPF2Amxyz(const CFile3 &cpffile, T_ARRAY &Amxyz){
// converts purged CPF file to mxyz array.
int err=0;//the mxyz is UTC(MJD),TEF.
	char *instr; double mxyz[7];
	unsigned int i;
	unsigned int arcnt;		//putchar('1');//arcnt is array count
	for(i=0, arcnt=0;(i<cpffile.nRecNum) && (Amxyz.ind<Amxyz.nRecNum);i++){
		instr=cpffile.body[i].s; //putchar('2');
		if((instr[0]=='1')&&(instr[1]=='0')){//if 10 record
			extract_CPF_rec_1(instr, mxyz); 
			Amxyz.in(mxyz);
		}
	} //Amxyz.ind=arcnt;
return(err);
}

int mxyz2mobs(const double mxyz[], const double pm[], double mrae[]){
int err=0;
	double rvec[3];
	int j;
	mrae[0]=mxyz[0];

	for(j=0;j<3;j++)rvec[j]=mxyz[j+1];
	tef2slf(rvec, pm+5, pm+8);
	cartes3_to_ah(rvec, mrae+1);
	mrae[1]= mrae[1]*2.0*M_invSpeedOfLight;
	refr_cor(mrae[1], mrae[3], pm[11], pm[12], pm[13], pm[10], pm[9]);//refraction correction
	//prmt[0~4] is eop(pmx,pmy,dut,Eps,dPsi)
	//prmt[5,6,7] is stavec(x,y,z)
	//prmt[8,9,10] is stageo(long, lat, alt)
	//prmt[11,12,13] is meteo para (p, T, rh)
return(err);	
}

int extract_tbrec_1b(const char longstr[], 
				int &nYoc, int &nDoy, double &fsod, 
				double &fAz, double &fEl, double &fR, 
				double &p, double &T, double &rh){
int err=0;
	
	char sdump[50];
	//int yr, mon, day;
	int hr, min, sec;
	double azdeg, eldeg, rangens, rangeUs;
	
	switch (longstr[3]){
		case (':') : {
		sscanf(longstr,
		" %d:%d:%d %lf %lf %lf %lf %s",
		&hr, &min, &sec,
		&azdeg, &eldeg, &rangens, &rangeUs, sdump);
		fsod = hr*3600.0+min*60.0+sec;
		fAz	=	azdeg * M_deg2rad;
		fEl	=	eldeg * M_deg2rad;
		fR	=	rangeUs;
		break;}
	//case ('1'): sscanf(longstr,
	//"%d %d %d", 
	//&yr, &mon, &day
	//);break;
	//case ('T'):
	//case ('H'):
		default : {
		printf("not data!\n");
		fsod = 0.0;
		fAz	=	0.0;
		fEl	=	0.0;
		fR	=	0.0;}
	}
	
	//sscanf(longstr,
	//" %d:%d:%d %lf %lf %lf %lf %s",
	//&hr, &min, &sec,
	//&azdeg, &eldeg, &rangens, &rangeUs, sdump);
// //did not change nYoc and nDoy.
	//fsod = hr*3600.0+min*60.0+sec;
	//fAz	=	azdeg * M_deg2rad;
	//fEl	=	eldeg * M_deg2rad;
	//fR	=	rangeUs;
	p		= 1000.0;
	T		=	293.0;
	rh	=	0.80;

return(err);
}

int extract_tbrec_2b(const char longstr[], 
				double &fsod, 
				double &fAz, double &fEl, double &fR, 
				double &p, double &T, double &rh){
int err=0;
	
	char sdump[50];
	//int yr, mon, day;
	int hr, min, sec;
	double azdeg, eldeg, rangens, rangeUs;
	
	switch (longstr[3]){
		case (':') : {
		sscanf(longstr,
		" %d:%d:%d %lf %lf %lf %lf %s",
		&hr, &min, &sec,
		&azdeg, &eldeg, &rangens, &rangeUs, sdump);
		fsod = hr*3600.0+min*60.0+sec;
		fAz	=	azdeg * M_deg2rad;
		fEl	=	eldeg * M_deg2rad;
		fR	=	rangeUs;
		break;}
		default : {
		printf("not data!\n");
		fsod = 0.0;
		fAz	=	0.0;
		fEl	=	0.0;
		fR	=	0.0;}
	}
	
	p		= 1000.0;
	T		=	293.0;
	rh	=	0.80;

return(err);
}

int extract_CPF_rec_1(const char longstr[], double txyz[]){
int err=0;
	char sType[3];
	int nDrcflg, nMJD, nLpSec;
	double fSoD, x,y,z;
	sscanf(longstr,"%s %d %d %lf %d %lf %lf %lf",
				sType, &nDrcflg, &nMJD, &fSoD, &nLpSec,
				&x, &y, &z);
	txyz[0]= nMJD+fSoD*M_sec2day;//mjd
	txyz[1]= x;//meter
	txyz[2]= y;//meter
	txyz[3]= z;//meter
	if(sType[0]!='1'||sType[1]!='0')printf("CPF error: not 10\n");
return(err);	
}

//int extract_CPF_head();






//version 2011.05.15
// Arr1.cpp: implementation of the Arr1 classes.
//
//////////////////////////////////////////////////////////////////////

#include "Arr2.h"
d7r::d7r(const double m7[])
{
	len=7;
	in(7, m7);
}
 
d7r::d7r()
{
	len=7;
	double zr[7]={0,0,0,0,0,0,0};
	for(int i=0;i<7;i++)zr[i]=0;
	in(7, zr);
	//printf("c");
}
 
d7r::~d7r()
{

}

void d7r::in(const int len, const double arr[])
{
	int i, l;
	l = (len>7)? 7: len;
	for(i=0;i<l;++i) p[i]=arr[i];
}

void d7r::in(const double arr[])
{
	int i;
	for(i=0;i<7;++i) p[i]=arr[i];
}

double* d7r::out(){
	return(p);
}

char* d7r::sout(){
	for(int i=0;i<7;i++)sprintf(s+i*25, "%25.10lf",p[i]);
	return(s);
}

void d7r::print(){
	printf("%s\n", this->sout());
}

//---------array RW---------------

 
CArray2::CArray2()
{
	nRecNum=0;
	ind=0;
};

 
CArray2::~CArray2()
{
	delete [] body;
};

 
CArray2::CArray2(const unsigned long recnum){
	nRecNum=0;
	ind=0;
	body = new d7r[recnum];
	nRecNum=recnum;
};

void CArray2::in(const unsigned long i, const double a[]){
	if(i<nRecNum){
		body[i].in(a);//i is real index from 0.
		ind=i+1; //ind is number of records.
	}else printf("CArray2 error: overflow!\n");
};

unsigned long CArray2::in(const double a[]){
	if(ind<nRecNum){
		body[ind].in(a);
		++ind;
	}else printf("CArray2 error: overflow!\n");
	return(ind);
};

void CArray2::print(){
	unsigned long i;
	for(i=0;i<ind;i++)	body[i].print();
};

void CArray2::save(char filename[]){
	unsigned long i;
	FILE * fp = fopen(filename, "w");
	for(i=0;i<ind;i++){
	fprintf(fp,"%s\n", body[i].sout());
	}
	fclose(fp);
};


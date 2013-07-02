//version 0.09.10
// Record.cpp: implementation of the CRec3 class.
//
//////////////////////////////////////////////////////////////////////

#include "Rec3.h"
// #include <stdio.h>
// #include <string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CRec3::CRec3(const char* str)
{
	len=N_RecMaxLen;
	in(str);
}
 
CRec3::CRec3()
{
	len=N_RecMaxLen;
	in("Whoops!");
	//printf("c");
}
 
CRec3::~CRec3()
{

}

 
void CRec3::in(const char* str)
{
	strncpy(s,str,len);
}

//for simple records.should be covered by child class.
 
char* CRec3::out(){
	return(s);
}

void CRec3::print(){
	printf("%s\n",this->out());
}

//---------FileRW---------------

 
CFile3::CFile3()
{

	strncpy(filename,"none",5);
	nRecNum=0;
};

 
CFile3::~CFile3()
{
	delete [] body;
};

 
CFile3::CFile3(const char* infilename, const unsigned long recnum){
	FILE* infp;
	char longstr[N_RecMaxLen];
	unsigned long reccnt;
	body = new CRec3[recnum];
	
	strncpy(filename,infilename,32);
	infp = fopen(infilename, "r");
	if (infp == NULL){
		printf("Failed to open file: %s\n", infilename);
	}
	else{
		for( reccnt=0 ;(reccnt< N_M2maxRecNum) && (reccnt<recnum) ; reccnt++ )	{
			if(NULL == fgets(longstr, N_RecMaxLen-1, infp))break;
			body[reccnt].in(longstr);
		}
		nRecNum = reccnt;
	}
	fclose(infp);
};


void CFile3::print(){
	unsigned long i;
	for(i=0;i<nRecNum;i++)
		printf("%s",body[i].out());
};


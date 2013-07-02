//version 2011.04.21
// Record.h: interface for the CRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORD_H__D0E62041_95D4_4B7B_9908_CA795D0DFC0F__INCLUDED_)
#define AFX_RECORD_H__D0E62041_95D4_4B7B_9908_CA795D0DFC0F__INCLUDED_

#include <stdio.h>
#include <string.h>
//#include <vector>
//#include "./class-constant.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define N_M2maxRecNum	1000000 //2012.04.16 from 20000
#define N_RecMaxLen 200

class CRec3  {
public:
	CRec3 (const char*);
	CRec3 ();
	virtual ~CRec3();

	void	in(const char*);
	char*		out();
	void	print();

	unsigned int len;
	char s[N_RecMaxLen];
};


class CFile3 {
public:
	CFile3();
	CFile3(const char*, const unsigned long);
	virtual ~CFile3();

	void print();

	char filename[50];//from 32 to 50.2011-04-21
	unsigned long nRecNum;

//protected:
//	std::vector<CRec3> body; //rec number restricted by vector
	CRec3 *body;
};

#endif // !defined(AFX_RECORD_H__D0E62041_95D4_4B7B_9908_CA795D0DFC0F__INCLUDED_)

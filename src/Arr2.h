//version 2011.05.15

#ifndef h_Arr_2_h
#define h_Arr_2_h

#include <stdio.h>
//#include <string.h>

class d7r {
public:
	d7r (const double[]);
	d7r();
	virtual ~d7r();
	
	void in(const int, const double[]);
	void in(const double[]);
	double *out();
	char *sout();
	void print();
	
	unsigned int len;
	double p[7]; // 7 fields 
	char s[200]; // 200 columns are sufficient.
};
 
class CArray2 {
public:
	CArray2();
	CArray2(const unsigned long);
	virtual ~CArray2();
	unsigned long in(const double []);
	void in(const unsigned long i, const double a[]);
	void print();
	void save(char filename[]);

	unsigned long nRecNum;
	unsigned long ind; //ind is number of records.
//protected:
//	std::vector<CRec3> body; //rec number restricted by vector
	d7r *body;
};

#endif




//#include <stdlib.h>
int sod_to_hms(double sod, int &h, int &m, int &s){
int err=0;
    long int isod;
    isod = (long int)sod;
    h = isod/3600;  if (h>23) err=h/24;
    s = isod%60;
    m = isod/60 - h*60 ;
return(err);
}



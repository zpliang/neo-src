// version 2011.05.01
#include "./double-vec.h"
int double_vec_add(double vec1[], const double vec2[], const int n);
int double_vec_add(double vec1[], const double vec2[], const double vec3[], const int n);
int double_vec_assign(double vec2[], const double vec1[], const int n);
int double_vec_perturb(double vec[], const double delta, const int k);
int double_vec_subtract(double vec1[], const double  vec2[], const int n);
int double_vec_subtract(double vec1[], const double vec2[], const double vec3[], const int n);
int double_vec_scaling(double vec[], const double  scale, const int n);


int double_vec_assign(double vec2[], const double vec1[], const int n){
int err=0;
	for(int i=0;i<n;i++){
		vec2[i] = vec1[i];
	}
return(err);
}

int double_vec_add(double vec1[], const double vec2[], const int n){
int err=0; //vec1 = vec1 + vec2;
	for(int i=0;i<n;i++){
		vec1[i] = vec1[i] + vec2[i];
	}
return(err);
}

int double_vec_add(double vec1[], const double vec2[], const double vec3[], const int n){
int err=0; //vec1 = vec2 + vec3;
	for(int i=0;i<n;i++){
		vec1[i] = vec2[i] + vec3[i];
	}
return(err);
}

int double_vec_subtract(double vec1[], const double vec2[], const int n){
int err=0; //vec1 = vec1 - vec2;
	for(int i=0;i<n;i++){
		vec1[i] = vec1[i] - vec2[i];
	}
return(err);
}

int double_vec_subtract(double vec1[], const double vec2[], const double vec3[], const int n){
int err=0; //vec1 = vec2 - vec3;
	for(int i=0;i<n;i++){
		vec1[i] = vec2[i] - vec3[i];
	}
return(err);
}

int double_vec_scaling(double vec[], const double scale, const int n){
int err=0;//vec = vec*scale;
	for(int i=0;i<n;i++){
		vec[i] *= scale;
	}
return(err);
}

int double_vec_perturb(double vec[], const double delta, const int k){
int err=0;
	vec[k] += delta;
return(err);
}


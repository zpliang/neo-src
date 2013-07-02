#ifndef h_double_vec_h
#define h_double_vec_h

int double_vec_add(double vec1[], const double vec2[], const int n);
int double_vec_add(double vec1[], const double vec2[], const double vec3[], const int n);
int double_vec_assign(double vec2[], const double vec1[], const int n);
int double_vec_perturb(double vec[], const double delta, const int k);
int double_vec_subtract(double vec1[], const double  vec2[], const int n);
int double_vec_subtract(double vec1[], const double vec2[], const double vec3[], const int n);
int double_vec_scaling(double vec[], const double  scale, const int n);

#endif // h_double_vec_h


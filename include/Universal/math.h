#ifndef UNIVERSAL_MATH_H
#define UNIVERSAL_MATH_H

#include<vector>
#include<cstdlib>
#include<cmath>
#include<Universal/complex.h>

#define GLOBAL_SCALE 10000000
#define PI 3.1415926
#define PHI_0(x) ((2*x+1)*(x-1)*(x-1))
#define PHI_1(x) (x*(x-1)*(x-1))
#define POWER(a,b,c) \
    c = 1;\
    for(int i=0;i<b;i++) c = c*a;
#define WNP(n,p,c) \
    c.real(cos(2*M_PI*p/n));\
    c.imag(-1*sin(2*M_PI*p/n));

namespace math
{
    void chase(double* x, const double* a, const double* b, const double* c,
        const double* f, const int size);
    void spline(double* sy, const double* x, const double* y, const double* sx,
        int length, int lsy);
    void fft(Complex* f, int N);
    void ifft(Complex* f, int N);
    void reciprocal(std::vector<double>& x, std::vector<double>& y);
}

#endif // UNIVERSAL_MATH_H

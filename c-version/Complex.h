#ifndef __COMPLEX_H
#define __COMPLEX_H

#include <math.h>
typedef struct {
    double real;
    double imag;
} Complex;


inline double abs_complex(Complex a) { 
    return sqrtl(a.real * a.real + a.imag * a.imag);
}
// 复数加法
inline Complex add_complex(Complex a, Complex b) { 
    return (Complex){a.real + b.real, a.imag + b.imag}; 
}
// 复数减法
inline Complex sub_complex(Complex a, Complex b) { 
    return (Complex){a.real - b.real, a.imag - b.imag}; 
}
// 复数乘法
inline Complex mul_complex(Complex a, Complex b) { 
    return (Complex){a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real}; 
}
// 复数除法
inline Complex div_complex(Complex a, Complex b) { 
    double denominator = b.real * b.real + b.imag * b.imag; 
    return (Complex){(a.real * b.real + a.imag * b.imag) / denominator, (a.imag * b.real - a.real * b.imag) / denominator};
}
inline Complex exp_complex(double angle) {
    double real = cos(angle); 
    double imag = sin(angle);
    return (Complex){real, imag}; 
}

inline Complex conj_complex(Complex a) {
    return (Complex){a.real, -a.imag};
}

inline void swap_complex(Complex *a, Complex *b) {
    Complex tmp = *a; 
    *a = *b;
    *b = tmp;
}

#endif 
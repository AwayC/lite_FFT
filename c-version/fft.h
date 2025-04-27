#ifndef __FFT_H
#define __FFT_H

#include "Complex.h"
#include <assert.h>
#include <math.h>
#define PI acos(-1.0)

/********* need to resize your array's lenght to 2 ^ k, if you use fft ***********
 * 
 * 
 * Complex signal[1024], fft_result, ifft_result; 
 * 
 * fft(signal, fft_resualt, 0); 
 * ifft(signal, ifft_result, 0); 
 * 
 * 
 * 
 */



void fft(Complex *x, Complex *ret, int N, int inverse) { 
    int logn = log2(N); 
    assert((1 << logn) == N); 
    for(int i = 0, j = 0;i < N;i ++) { 
        if(i < j) { 
            if(ret == x) swap_complex(&x[i], &x[j]);
            else ret[i] = x[j], ret[j] = x[i]; 
        } else if(i == j) {
            ret[i] = x[i]; 
        }
        for(int k = N >> 1;(j ^= k) < k;k >>= 1);
    }
    for(int h = 2;h <= N;h <<= 1) { 
        int hh = h >> 1; 
        Complex wn = exp_complex((inverse ? 2 : -2) * PI / h); 
        for(int i = 0;i < N;i += h) { 
            Complex w = {1.0, 0.0}; 
            for(int j = 0;j < hh;j ++) { 
                Complex t = mul_complex(ret[i + j + hh], w); 
                ret[i + j + hh] = sub_complex(ret[i + j], t); 
                ret[i + j] = add_complex(ret[i + j], t); 
                w = mul_complex(wn, w); 
            }
        }
    }
    if(inverse) { 
        for(int i = 0;i < N;i ++) { 
            ret[i].real /= N; 
            ret[i].imag /= N; 
        }
    }
}

void dft(Complex *x, Complex* ret, int N, int inverse) { 
    for(int i = 0;i < N;i ++) { 
        for(int j = 0;j < N;j ++) { 
            double angle = (inverse ? 2 : -2) * PI * i * j / N;
            Complex w = exp_complex(angle); 
            ret[i] = add_complex(ret[i], mul_complex(x[j], w));
        }
    }
}



#endif // __FFT_H
#include <stdio.h>
#include "fft.h"
#include "Complex.h"
#include <math.h>

#define prarr_com(a, n) do { \
        for(int i = 0;i < n;i ++) { \
            printf("%f ", abs_complex(a[i])); \
        } \
        printf("\n"); \
    } while(0); 

const int N = 1024; 
Complex signal[N]; 
Complex fft_result[N];
Complex ifft_result[N];
void init_signal();
int Fs = 2000; 

void init_signal() {
    for(int i = 0;i < N;i ++) { 
        signal[i].real = sin(2 * 100 * M_PI * i / Fs) * 0.5 
            + sin(2 * 200 * M_PI * i / Fs) * 0.3
            + sin(2 * 300 * M_PI * i / Fs) * 0.2;
        signal[i].imag = 0;
    }
}
int main() { 
    init_signal(); 
    fft(signal, fft_result, N, 0); 
    fft(fft_result, ifft_result, N, 1);
    prarr_com(signal, N); 
    prarr_com(fft_result, N); 
    prarr_com(ifft_result, N);
}
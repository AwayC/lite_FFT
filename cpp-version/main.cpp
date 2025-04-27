#include <vector>
#include <cmath> 
#include <iostream> 
#include "fft.h"
#include "Complex.h"

int Fs = 2000; 
const int N = 1024; 

#define PRINT(a) do {for(int i = 0;i < a.size();i ++) std::cout << a[i].abs() << " ";std::cout << std::endl;} while(0); 
void init_signal(std::vector<Complex>& signal) {
    for(int i = 0;i < signal.size();i ++) { 
        signal[i].real = sin(2 * 100 * M_PI * i / Fs) * 0.5 
            + sin(2 * 200 * M_PI * i / Fs) * 0.3
            + sin(2 * 300 * M_PI * i / Fs) * 0.2;
        signal[i].imag = 0.0;
    }
}
int main() { 
    std::vector<Complex> signal(N); 
    FastFourier fft(N); 
    init_signal(signal); 
    PRINT(signal); 
    fft.transform(signal);
    PRINT(signal); 
    fft.transform(signal); 
    PRINT(signal); 
    
}
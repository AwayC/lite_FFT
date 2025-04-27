import numpy as np
import matplotlib.pyplot as plt

# 生成示例信号
Fs = 2000  # 采样频率
T = 1.0 / Fs  # 采样间隔
N = 1024  # 采样点数
t = np.linspace(0.0, N*T, N, endpoint=False)

# 生成信号：50Hz正弦波 + 120Hz正弦波 + 噪声
signal = 0.5 * np.sin(100.0 * 2.0*np.pi*t) + \
         0.3 * np.sin(200.0 * 2.0*np.pi*t) + \
         0.2 * np.sin(300.0 * 2.0*np.pi*t) + \
         0.2 * np.random.randn(N)



class Complex:
    def __init__(self, real = 0.0, imag = 0.0):
        self.real = real
        self.imag = imag
    def __add__(self, other):
        return Complex(self.real + other.real, self.imag + other.imag)
    def __sub__(self, other):
        return Complex(self.real - other.real, self.imag - other.imag)
    def __mul__(self, other):
        return Complex(self.real * other.real - self.imag * other.imag, self.real * other.imag + self.imag * other.real)

comlex_signal = [Complex(signal[i], 0.0) for i in range(N)]  # 修正拼写错误应为complex_signal

def fft(x):
    n = len(x) 
    logn = int(np.log2(n))
    # 位反转排列
    for i in range(n):
        rev = 0
        for j in range(logn):
            rev |= ((i >> j) & 1) << (logn - j - 1)
        if i < rev:
            x[i], x[rev] = x[rev], x[i]
    
    # 迭代FFT计算
    for k in range(1, logn + 1):
        m = 1 << k  # 当前处理的块大小
        m_half = m // 2
        for i in range(0, n, m):
            for j in range(m_half):
                angle = 2 * np.pi * j / m
                twiddle = x[i + j + m_half] * Complex(np.cos(angle), -np.sin(angle)) 

                x[i + j + m_half] = x[i + j] - twiddle
                x[i + j] = x[i + j] + twiddle
    return x

# 执行FFT变换时应该使用复数信号
fft_result = fft(comlex_signal)[:N//2]  # 使用自定义复数信号

magnitude = [np.sqrt(c.real**2 + c.imag**2) for c in fft_result][:N//2]  # 手动计算幅度

print(max(magnitude))
freq = np.arange(N // 2) * Fs / N

# 可视化结果
plt.figure(figsize=(12, 6))

# 原始信号
plt.subplot(2, 1, 1)
plt.plot(t, signal)
plt.title('signal')
plt.xlabel('time(s)')
plt.ylabel('幅度')

# 频域信号
plt.subplot(2, 1, 2)
plt.plot(freq, magnitude)
plt.title('频域分析 (FFT)')
plt.xlabel('频率 (Hz)')
plt.ylabel('幅度')

plt.tight_layout()
plt.savefig('fft_analysis.png')
plt.show()

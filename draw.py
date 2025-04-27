import numpy as np
import matplotlib.pyplot as plt

def read_out_file(filename):
    """读取main.out文件中的浮点数数组"""
    with open(filename, 'r') as f:
        data = f.read().split()
    return np.array([float(x) for x in data], dtype=np.float32)

# 读取输出数据
N = 1024  # 与main.c中的N保持一致
signal = read_out_file('./out/main.out')[:N]      # 原始信号
fft_result = read_out_file('./out/main.out')[N:N*2]  # FFT结果
ifft_result = read_out_file('./out/main.out')[N*2:]  # IFFT结果

# 创建时间轴和频率轴
t = np.arange(N) / N
freq = np.fft.fftfreq(N, d=1/N)[:N//2]
py_result = np.fft.fft(signal)[:N//2]

plt.figure(figsize=(15, 8))

# 原始时域信号
plt.subplot(3, 1, 1)
plt.plot(t, signal)
plt.title('Original Time Domain Signal')
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')

# 频域信号（取前半部分）
plt.subplot(3, 1, 2)
plt.plot(freq[:N//2], np.abs(fft_result[:N//2]))
plt.title('Frequency Domain (FFT)')
plt.xlabel('Frequency (Hz)')
plt.ylabel('Magnitude')
plt.xlim(0, 500)  # 聚焦0-500Hz范围

# 逆变换恢复的时域信号
plt.subplot(3, 1, 3)
plt.plot(freq[:N//2], np.abs(py_result))
plt.title('PY Transform (FFT)')
plt.xlabel('Frequency (Hz)')
plt.ylabel('Amplitude')

plt.tight_layout()
plt.savefig('fft_ifft_analysis.png')
plt.show()

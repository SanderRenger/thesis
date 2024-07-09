from numpy import loadtxt
import numpy as np
from matplotlib import pyplot as plt
from scipy.interpolate import interp1d
import math
#read text file into NumPy array
Ts=10

#os.path.join(os.getcwd(), parentdir, filename)
i=7
j=2
x = np.load('cmake-build-debug/test/Cluster'+str(j)+'/Neuron'+str(i)+'.npy')
y = np.load('cmake-build-debug/temp/Layer'+str(j)+'/PyTorchNeuron'+str(i)+'.npy')
plt.title("Potential")
plt.xlabel("timestep")
plt.ylabel("potential")
plt.plot(x[0],'red')
plt.plot(y,'blue')
plt.show()
print(np.min(y))
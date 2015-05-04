import numpy as np
import os
import matplotlib.pyplot as plt
import matplotlib

#y = np.transpose(np.loadtxt('models-solidestim.txt',unpack=True,dtype=['str','str',float,float]))
y = np.loadtxt('models-spinestim.txt', dtype='str')

y = np.transpose(y)


liste = np.zeros(np.shape(y))

fig1 = plt.gcf()

for i in range(2,4):
    for k in range(np.shape(y)[1]):
        liste[i][k] = float(y[i][k])




for i in range(0, len(liste[2])):
    plt.errorbar(i,liste[2][i], yerr=liste[3][i], fmt = 'ro')

matplotlib.rc('xtick', labelsize=20)
matplotlib.rc('ytick', labelsize=40)

x = range(0,len(liste[2]))
plt.xticks(x, y[1], rotation = 60)
#plt.plot(liste[3], 'ro')
plt.ylabel("Spine", fontsize=16)

plt.show()

fig1.savefig('spinestim.png', dpi=100)










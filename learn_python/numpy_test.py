#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0,4*3.1415,100)
y = np.sin(x)

plt.figure()
plt.plot(x,y,label="$sin(x)$",color="red",linewidth=2)
plt.legend()
plt.show()

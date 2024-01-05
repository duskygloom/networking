#!/bin/python3
import math
import numpy as np
import matplotlib.pyplot as plt
import sys
import io
from sys import argv

if __name__=='__main__':
  print(len(argv))
  if(len(argv)!=3):
     print('\nUsage : python3 {} datafile title\n'.format(argv[0]))
     exit(1)
  x = np.loadtxt(argv[1])[:, 0]
  y = np.loadtxt(argv[1])[:, 1]
  plt.plot(x,y)
  plt.title(argv[2])
  plt.show()

#!/bin/python3
import math
import numpy as np
import sys 
import io
from sys import argv 

def gen_zero_mean_normal_rv(sigma, num_samples):
  f = io.open("normal.dat","a")
  n = np.random.normal(0.0,sigma,num_samples)
  f.write('{} \n'.format(n))

if __name__=='__main__':
  if(len(argv)!=3):
    print('\nUsage : python3 {} ebno_db num_samples\n'.format(argv[0]))
    exit(1)
  ebno_db = (float)(argv[1])
  num_samples = (int)(argv[2])
  N_0 = 1.0/math.pow(10.0,ebno_db/10.0)
  print('N_0 = {}'.format(N_0)) 
  sigma = math.sqrt(N_0/2.0)
  print('sigma = {}'.format(sigma)) 
  gen_zero_mean_normal_rv(sigma, num_samples)

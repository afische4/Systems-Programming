#!/usr/bin/env python3

import re
import sys

num_prey = 0
num_pred = 0
datfile = "dinosaur.dat"

prey = sys.argv[1]
predator = sys.argv[2]

f = open(datfile, 'r')

dinoframe = list()
headers = f.readline().split('\t')
for line in f:
  if(len(line.split('\t')) == len(headers)):
    data = line.split('\t')
  if(re.search(prey, data[5], re.IGNORECASE)):
      num_prey += 1
  if(re.search(predator, data[5], re.IGNORECASE)):
      num_pred += 1
yrrat = (num_prey / num_pred)
print(f'number of prey: {num_prey}')
print(f'number of predator: {num_pred}')
print(f'ratio: {yrrat}')
f.close()

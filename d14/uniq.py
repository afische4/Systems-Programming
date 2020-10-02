#!/usr/bin/env python
import sys
import argparse
import pdb
import filterInput

#parser = argparse.ArgumentParser(description='uniq filter', formatter_class=argparse.RawTextHelpFormatter)
#parser.add_argument('-d', dest='datfile_in', type=str, default='dinosaur.dat', help='data file to read')
#args = parser.parse_args()

#datfile = args.datfile_in

datfile = sys.argv[1] #??
data = filterInput.inputdata()
words = data.readfile(datfile)
names = dict()
  

for name in words:
  name = name.strip()
  if name in names:
    names[name] += 1
  else:
    names[name] = 1

# Iterating over the dictionary,
# print name
#pdb.set_trace()

for name, key in names.items() :
  print(f'{name}')


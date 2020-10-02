#!/usr/bin/env python
import sys
import argparse
import pdb

helpmsg ="""Usage: unique.py [flags]

        -c      Prefix lines by the number of occurrences
        -d      Only print duplicate lines
        -i      Ignore differences in case when comparing, prints out full line in lowercase
        -u      Only print unique lines

    By default, unique.py prints one of each type of line. """

parser = argparse.ArgumentParser(description=helpmsg, formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('-u', dest='uniq', action='store_true', default=False)
parser.add_argument('-d', dest='dup', action='store_true', default=False)
parser.add_argument('-i', dest='lcase', action='store_true', default=False)
parser.add_argument('-c', dest='count', action='store_true', default=False)
args = parser.parse_args()

uniq = args.uniq
dup = args.dup
lcase = args.lcase
count = args.count
data = sys.stdin.readlines()
words = []
names = dict() 
#create data array
for line in data:
  words.append(line)
#create dictionary
if lcase:
  for name in words:
    name = name.strip()
    name = name.lower()
    if name in names:
      names[name] += 1
    else:
      names[name] = 1
else:
  for name in words:
    name = name.strip()
    if name in names:
      names[name] += 1
    else:
      names[name] = 1
#print out according to flags
if count:
  if uniq:
    for name, key in names.items() :
      if (key == 1):
        print(f'{key} {name}')
  elif dup:
    for name, key in names.items() :
      if (key > 1):
        print(f'{key} {name}')
  else: 
    for name, key in names.items() :
      print(f'{key} {name}')
else:
  if uniq:
    for name, key in names.items() :
      if (key == 1):
        print(f'{name}')
  elif dup:
    for name, key in names.items() :
      if (key > 1):
        print(f'{name}')
  elif len(sys.argv) == 1 or lcase:
    for name, key in names.items() :
      print(f'{name}')


import re
import sys
import pdb

class inputdata():
  def __init__(self):
    self.data = [] 

  def readfile(self, datfile):
    if datfile == None:
      datfile = 'dinosaur.dat'
    f = open(datfile, 'r')
    errors = 0
    for line in f:
      temp = line.split('\t') 
      #pdb.set_trace()
      for i in temp:
        self.data.append(i)
    #pdb.set_trace() 
    return self.data 
    f.close()


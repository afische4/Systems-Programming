import re
import sys
import pdb

class dinodata():
  def __init__(self, preys, preds):
    self.preys = preys
    self.preds = preds
    self.data = []

  def readdinos(self, datfile):
    if datfile == None:
      datfile = 'dinosaur.dat'
    f = open(datfile, 'r')
    headers = f.readline().split('\t')
    errors = 0
    for line in f:
      if(len(line.split('\t')) == len(headers)):
        temp = line.split('\t') 
        self.data.append(temp[5])
      else:
        errors += 1
    f.close()
        
  def preypredrat(self):
    num_prey = 0
    num_pred = 0
    for i in self.data:
      for a in self.preys: 
        if(re.search(a, i, re.IGNORECASE)):
          num_prey += 1
      for b in self.preds:
        if(re.search(b, i, re.IGNORECASE)):
          num_pred += 1 
    yrrat = (num_prey / num_pred)
    return num_prey, num_pred, yrrat



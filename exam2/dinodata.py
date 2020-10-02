import re
import sys
import pdb
from simplecrypt import encrypt, decrypt
from base64 import b64encode, b64decode

class dinodata():
  def __init__(self):
    self.data = [] 

  def readdinos(self, datfile):
    if datfile == None:
      datfile = 'dinosaur.dat'
    f = open(datfile, 'r')
    self.headers = f.readline().split('\t')
    errors = 0
    for line in f:
      if(len(line.split('\t')) == len(self.headers)):
        temp = line.split('\t') 
        self.data.append(temp[5])
      else:
        errors += 1
    
    f.close()
        
  def preypredrat(self, preys):
    num_prey = 0
   
    for i in self.data:
      #for a in preys: 
      if(re.search(str(a), i, re.IGNORECASE)):
        num_prey += 1
    return num_prey

  def dinoencrypt(fcn):
    def inner(self, datfile, dat):
      if self.pswd == '':
        fcn(self, datfile, dat)
        return
      dat = encrypt(self.pswd, dat)
      dat = b64encode(dat).decode('utf-8')
      fcn(self, datfile, dat)
      return 
    return inner 

  @dinoencrypt
  def filewriteline(self, datfile, dat):
    fd = open(datfile, 'a')
    fd.write(dat)
    fd.write('\n')
    fd.close()

  def save_df(self, datfile_out, columns, limit):
    title = ''
    for p in columns:
      if p == columns[0]:
        title = self.headers[p]
      else:
        title = title + '\t' + self.headers[p]
    self.filewriteline(datfile_out, title)
    for i in range(0, limit):
        temp = ''
        for j in columns:
          if j == columns[0]:
            temp = self.data[i][j]
          else:
            temp = temp + '\t' + self.data[i][j]
        #pdb.set_trace()
        self.filewriteline(datfile_out, temp)





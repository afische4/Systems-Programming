import re
import sys
import pdb


class dinodata():
  def __init__(self):
    self.dinos = list()
    self.ages = list()

  def readdinos(self, zipdat, dist):
    dinos = 'dinosaur.dat'
    d = open(dinos, 'r')
    headers = d.readline().split('\t')
    i = 0
    for line in d:
      if(len(line.split('\t')) == len(headers)):
        temp = line.split('\t')
        dist = float(dist)
        lat = float(temp[19])
        lng = float(temp[18])
        x = float(zipdat[0])
        y = float(zipdat[1])
        if((lat >= x-dist) and (lat <= x+dist) and (lng >= y-dist) and (lng <= y+dist)):
          self.dinos.append(list())
          self.dinos[i].append(temp[5]) # name of dino  #maybe don't need this
          self.dinos[i].append(lat)  #latitude of dino
          self.dinos[i].append(lng)  #longitude of dino
          self.dinos[i].append((float(temp[15])+float(temp[16]))/2)
          self.ages.append((float(temp[15])+float(temp[16]))/2)   #age
          i +=1
    d.close()
    #pdb.set_trace()
    return self.dinos, self.ages
  
  def zip_range(self, zipcode):
    zips = 'zipcodes.dat'
    z = open(zips, 'r')
    zipdat = []
    for line in z:
      line = line.split(';')
      if (zipcode == line[0]):
        x = line[3]
        y = line[4]
        name = line[1]
        state = line[2]
        zipdat = [x,y, name, state]
    z.close()
    #print(zipdat)
    return zipdat

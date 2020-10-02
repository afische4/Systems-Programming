import re
import sys
import pdb
import staticmap
import matplotlib.pyplot as plt 
import matplotlib.image as mpimg
import matplotlib.font_manager as fm
import math
from staticmap import StaticMap, CircleMarker


class mapmaker():
  def __init__(self, zipcode):
    self.zipcode = zipcode
    
  def plotDinos(self, zipdat, dinos, dist, ages):
    lat = float(zipdat[0]) # latitude
    lng = float(zipdat[1])
    center = [lng, lat] 
    plot = StaticMap(512, 512 )
    zipCenter = CircleMarker(center, '#000000', 10)
    plot.add_marker(zipCenter)
    color_adjust = 0

    for i in dinos:
      age = float(i[3])
      dinoLat = float(i[1])
      dinoLng = float(i[2])
      color = self.getColor(age, ages)
      dinoMark = CircleMarker((dinoLng, dinoLat), color, 10)
      plot.add_marker(dinoMark)
    zoom = None
    image = plot.render(zoom, center)
    name = str(self.zipcode) + '_'+ str(dist) +'.png'
    image.save(name)
    #print(name)
    img = mpimg.imread(name)
    dist = float(dist)
    fig, ax = plt.subplots(figsize=(6,6))
    ax.imshow(img, extent=[lng-dist,lng+dist,lat-dist,lat+dist], aspect='auto')
    title = 'Dinosaurs near ' + str(zipdat[2]) + ', ' + str(zipdat[3])
    plt.show()
    #print(title)
    font = fm.FontProperties(size=6)
    fig.text(0.5, 0.89, title, horizontalalignment='center', fontproperties=font)
    for label in (ax.get_xticklabels() + ax.get_yticklabels()):
      label.set_fontproperties(font)    
    plt.savefig(name)

  def getColor(self, age, ages):
    if len(ages) > 1:
      maxage = max(ages)
      minage = min(ages)
      if maxage != minage:
        age = abs(minage - age)
        agerange = maxage - minage
      else:
        agerange = age
      age = age/agerange 
      color_adjust = round(age * 255)
      red = color_adjust
      blue = 255 - color_adjust
      red = hex(red)
      blue = hex(blue)
      red = red[2:]
      blue = blue[2:]
      if len(blue) == 1:
        blue = blue + '0'
      if len(red) == 1:
        red = red + '0'
      color = '#' + red + '00' + blue
    else:
      color = '#FF0000'
    return color



import staticmap
import matplotlib
import math
import sys
import argparse
import dinodata
import mapmaker

descr = """Usage: m2a.py [flags]

      -z      zipcode
      -d      longitude and latitude unit   """

parser = argparse.ArgumentParser(description = descr, formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('-z', dest ='zipcode')
parser.add_argument('-d', dest ='unit')
args = parser.parse_args()

zipcode = args.zipcode
dist = args.unit
dinos = dinodata.dinodata()
zipdat = dinos.zip_range(zipcode)
dinos_in_range, dino_ages = dinos.readdinos(zipdat, dist)
graph = mapmaker.mapmaker(zipcode)
image = graph.plotDinos(zipdat, dinos_in_range, dist, dino_ages)


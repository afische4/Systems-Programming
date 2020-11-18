import argparse
import re
import sys
import pdb
import dataframe

parser = argparse.ArgumentParser()
parser.add_argument('-f', dest='datfile', type=str, required=True, help='file name to read')
args = parser.parse_args()

datfile = args.datfile

f = open(datfile, 'r')


df = dataframe.Dataframe()
df.append(['a', 'b', 'c'])
df.append(['mid', 'name', 'year', 'genres'])

errors = 0

pdb.set_trace()

for line in f:
	(mid, nameyear, genres) = line.split('::')

	x = re.search('(.+)\s\(([0-9]{4})\)', nameyear)

	try:
		name = x.group(1)
		year = int(x.group(2))
		df.append([mid, name, year, genres])
	except AttributeError as ex:
		errors += 1

f.close()

print(errors)


import re
import sys
import pdb

datfile = sys.argv[1]

f = open(datfile, 'r')

dataframe = list()
headers = [ 'mid', 'name', 'year', 'genres' ]

errors = 0

for line in f:
	(mid, nameyear, genres) = line.split('::')

	x = re.search('(.+)\s\(([0-9]{4})\)', nameyear)

	try:
		name = x.group(1)
		year = int(x.group(2))
	except AttributeError as ex:
		errors += 1

	#pdb.set_trace()

f.close()

print(errors)


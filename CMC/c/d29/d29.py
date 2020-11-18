from cdinodata import *

cdd = cdinodata()

num_dinos = cdd.readdinos("dinosaur.dat")

dinos = cdd.get_dinos()

for i in range(0, 30):
    d = dinos[i]

    print(e['lat'], e['lng'], e['maxma'], e['minma'], e['namelen'], e['name'])

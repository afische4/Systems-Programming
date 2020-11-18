from cdinodata import *

cdd = cdinodata()

num_dinos = cdd.readdinos("dinosaur.dat")

dinos = cdd.get_dinos()

for i in range(0, 30):
    d = dinos[i]

    cdd.save_dino(d, f'wrk/dino_{i}.bin')
    e = cdd.load_dino(f'wrk/dino_{i}.bin')
    
    print(e['lat'], e['lng'], e['maxma'], e['minma'], e['namelen'], e['name'])

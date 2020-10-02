import time
import pdb

cached = dict()

def cache(fcn):
    def inner(a):
        if a not in cached.keys():
            cached[a] = fcn(a)
        return cached[a]
    return inner

@cache
def expensive(a):
    time.sleep(2)
    return a+1

#newe = cache(expensive)

pdb.set_trace()
expensive(5)
expensive(5)

expensive(6)
expensive(6)
expensive(6)


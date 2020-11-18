from geolib import geolib

gl = geolib()

r = gl.geodist(41.676388, -86.250275, 90, 0)

print(r)

r = gl.palindrome("civic")

print(r)

p = dict()
p['age'] = 80
p['name'] = "Donald Duck"

print(p)

p = gl.setperson(p)

print(p)

people = gl.initpeople(4)

print(people)


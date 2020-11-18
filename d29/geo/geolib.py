import ctypes
import pathlib

class c_person(ctypes.Structure):
	_fields_ = [('age', ctypes.c_int),
		    ('name', ctypes.c_char_p)]

class geolib:

	def __init__(self):
		self.libname = pathlib.Path().absolute() / "libgeodist.so"
		self.c_lib = ctypes.CDLL(self.libname)

	def geodist(self, lat1, lng1, lat2, lng2):
		lat1 = ctypes.c_double(lat1)
		lng1 = ctypes.c_double(lng1)
		lat2 = ctypes.c_double(lat2)
		lng2 = ctypes.c_double(lng2)

		self.c_lib.geodist.restype = ctypes.c_double
		ret = self.c_lib.geodist(lat1, lng1, lat2, lng2)
		return ret

	def palindrome(self, word):
		word = ctypes.c_char_p(word.encode('utf-8'))

		self.c_lib.geodist.restype = ctypes.c_int
		ret = self.c_lib.palindrome(word)

		if(ret==1):
			ret = True
		else:
			ret = False

		return ret

	def setperson(self, person):
		wrkperson = c_person()

		wrkperson.age = ctypes.c_int(person['age'])
		wrkperson.name = ctypes.c_char_p(person['name'].encode('utf-8'))

		wrkperson = ctypes.pointer(wrkperson)

		self.c_lib.setperson(wrkperson)

		wrkperson = wrkperson.contents

		person['age'] = wrkperson.age
		person['name'] = wrkperson.name.decode('utf-8')

		return person

	def initpeople(self, numpeople):
		cnumpeople = ctypes.c_int(numpeople)

		elems = (ctypes.POINTER(c_person) * numpeople)()
		wrkpeople = ctypes.cast(elems, ctypes.POINTER(ctypes.POINTER(c_person)))

		self.c_lib.initpeople(wrkpeople, cnumpeople)

		retpeople  = list()

		for i in range(0, numpeople):
			w = wrkpeople[i].contents
			p = dict()
			p['age'] = w.age
			p['name'] = w.name.decode('utf-8')
			retpeople.append(p)

		return retpeople


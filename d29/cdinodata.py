import ctypes
import pathlib

class c_dino(ctypes.Structure):
    _fields_ = [('lat', ctypes.c_double),('lng', ctypes.c_double),
            ('maxma',ctypes.c_double), ('minma', ctypes.c_double), ('namelen', ctypes.c_int), ('name', ctypes.c_char_p)]

class cdinodata:
    
    def __init__(self, maxdinos=30000):
        self.libname = pathlib.Path().absolute() / "libdinos.so" 
        self.c_lib = ctypes.CDLL(self.libname)
        # create array of 30000 dino structs
        # elements are type c_dino and there are maxdinos of them
        # dino *dinos[30000] ----> pointer to array of 30000 dinos
        # POINTER(c_dino) * 30000
        # **dinos = POINTER(POINTER(c_dinos))
        elems = (ctypes.POINTER(c_dino) * maxdinos)()
        self.dinos = ctypes.cast(elems, ctypes.POINTER(ctypes.POINTER(c_dino)))
        #pass
    
    def readdinos(self, fn):
        self.c_lib.readdinos.restype = ctypes.c_int
        #readdinos parameters are filename and array of dino structs **dinos
        datfile = ctypes.c_char_p(fn.encode('utf-8'))
        self.ret = self.c_lib.readdinos(datfile, self.dinos)
        return self.ret
        #pass

    def get_dinos(self):
        res = list()
        for i in range(0, self.ret):
            d = self.dinos[i].contents
            p = dict()
            p['lat'] = d.lat
            p['lng'] = d.lng
            p['minma'] = d.minma
            p['maxma'] = d.maxma
            p['namelen'] = d.namelen
            p['name'] = d.name.decode('utf-8')
            res.append(p)
        return res


        #pass

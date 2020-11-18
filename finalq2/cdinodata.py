import ctypes
import pathlib

class c_dino(ctypes.Structure):
    _fields_ = [("lat", ctypes.c_double),
                ("lng", ctypes.c_double),
                ("maxma", ctypes.c_double),
                ("minma", ctypes.c_double),
                ("namelen", ctypes.c_int),
                ("name", ctypes.c_char_p)]

class cdinodata:
    
    def __init__(self, maxdinos=30000):
        self.libname = pathlib.Path().absolute() / "libdinos.so"
        self.c_lib = ctypes.CDLL(self.libname)
    
        elems = (ctypes.POINTER(c_dino) * maxdinos)()
        self.c_dinos = ctypes.cast(elems, ctypes.POINTER(ctypes.POINTER(c_dino)))
        self.numdinos = -1

        self.dinos = list()
    
    def readdinos(self, fn):

        cfn = ctypes.c_char_p(fn.encode('utf-8'))
    
        self.c_lib.readdinos.restype = ctypes.c_int
        self.numdinos = self.c_lib.readdinos(cfn, self.c_dinos)

        for i in range(0, self.numdinos):
            d = self.c_dinos[i].contents
            dd = dict()
            dd['lat'] = d.lat
            dd['lng'] = d.lng
            dd['maxma'] = d.maxma
            dd['minma'] = d.minma
            dd['namelen'] = d.namelen
            dd['name'] = d.name.decode('utf-8')
            #d.name = d.name.decode('utf-8')
            self.dinos.append(dd)

        return self.numdinos

    def get_dinos(self):
        return self.dinos

    def save_dino(self, dino, fn):
        #need type dino *d and char *fn
        self.d = ctypes.cast(dino, ctypes.POINTER(c_dino))
        f = ctypes.c_char_p(fn.encode('utf-8'))
        self.c_lib.save_dino(self.d, f)

    def load_dino(self, fn):
        f = ctypes.c_char_p(fn.encode('utf-8')
        #self.c_lib.load_dino.restype = ctypes.POINTER
        self.c_lib.load_dino(self.d, f)
        d = dino.contents
#THE LIBRARY SAYS LOAD DINOS IS LOAD_DINOS(DINO *D, CHAR *F) BUT THE FQ2 SAYS NO DINO *D ???????
        return d

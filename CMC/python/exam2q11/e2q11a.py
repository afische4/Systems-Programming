import pdb

from muchmath import MuchMath

def test_matrixAdd():
    mm = MuchMath()
        
    X = [[44, 1, 9],
         [2, 3, 15],
         [14, 13, 12]]
        
    Y = [[3, 2, 4],
         [6, 99, 8],
         [9, 32, 8]]
        
    res = mm.matrixAdd(X, Y)
     
    ref = [[47, 3, 13],
           [8, 102, 23],
           [23, 45, 20]]

    return(res == ref)

#pdb.set_trace()

v = test_matrixAdd()

print(v)


import pdb

from muchmath import MuchMath

def test_matrixAdd():
    mm = MuchMath()
        
    X = [[44, 1, 9, 74],
         [2, 3, 15, 6],
         [14, 13, 12, 1]]
        
    Y = [[3, 2, 4, 2],
         [6, 99, 8, 62],
         [9, 32, 8, 21]]
    pbd.set_trace() 
    res = mm.matrixAdd(X, Y)
     
    ref = [[47, 3, 13, 76],
           [8, 102, 23, 68],
           [23, 45, 20, 22]]

    return(res == ref)

#pdb.set_trace()

v = test_matrixAdd()

print(v)


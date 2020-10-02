import unittest
import sys
import filecmp
import matplotlib.image as mpimg
from dinodata import dinodata

class dinodataTest(unittest.TestCase):
  def test_readdinos(self):
    dino = dinodata()
    dinotest1, testage1 = dino.readdinos([41.701415, -86.24498,'Notre Dame', 'IN'], 1)
    test1 = []
    test2 = [['Numenius americanus', 40.560001, -89.754997, 0.00585]]
    test3 = [0.00585]
    
    self.assertEqual(test1, dinotest1)
    self.assertEqual(test1, testage1)
    
    dinotest2, testage2 = dino.readdinos([40.134957,-90.55222, 'Rushville','IL'],1)
    
    self.assertEqual(test2, dinotest2)
    self.assertEqual(test3, testage2)

  def test_zip_range(self):
    dino = dinodata()
    ziptest = dino.zip_range('46556')
    res = ['41.701415', '-86.24498','Notre Dame', 'IN']
    self.assertEqual(res, ziptest)

unittest.main()

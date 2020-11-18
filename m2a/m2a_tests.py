import unittest
import sys
import filecmp
import matplotlib.image as mpimg
from dinodata import dinodata
from mapmaker import mapmaker


class m2aTest(unittest.TestCase):
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

  def test_plotDinos(self):
    mapmake = mapmaker(46556)
    plotDinos = mapmake.plotDinos([41.701415, -86.24498,'Notre Dame', 'IN'], [], 1, [])
    map1 = '46556_1.png'
    map1 = mpimg.imread(map1)
   
    mapmake2 = mapmaker(91210)
    dino = dinodata()
    plot2, age2 = dino.readdinos([33.786594,-118.298662, 'Glendale','CA'],2)
    plotDinos2 = mapmake2.plotDinos([33.786594,-118.298662, 'Glendale','CA'],plot2,2,age2)
    map2 = '91210_2.png'
    map2 = mpimg.imread(map2)
 
    test = 'maptest1.png'
    test1 = mpimg.imread(test)
    test = 'maptest2.png'
    test2 = mpimg.imread(test)

    self.assertEqual(test1.all(), map1.all())
    self.assertEqual(test2.all(), map2.all())

  def test_getColor(self):
    mapmake = mapmaker(46556)
    testcolor = mapmake.getColor(10, [0, 15, 10, 5])
    testcolor2 = mapmake.getColor(5, [5, 5])
    testcolor3 = mapmake.getColor(5, [5])
    self.assertEqual(testcolor,'#aa0055')
    self.assertEqual(testcolor2,'#ff0000')
    self.assertEqual(testcolor3, '#FF0000')
unittest.main()

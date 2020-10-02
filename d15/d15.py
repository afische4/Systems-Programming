import unittest
from muchmath import MuchMath

class MuchMathTest(unittest.TestCase):

    def test_triangle(self):
        muchmath = MuchMath()
        t = muchmath.triangleArea(4,5)
        self.assertEqual(t,10)

    def test_celtofar(self):
        muchmath = MuchMath()
        p = muchmath.celsiusToFahrenheit(0)
        self.assertEqual(p,32)

    def test_matrixadd(self):
        X = [(1,1),(1,1)]
        Y = [(0,1,2),(1,1,1), (0,2,0)]
        muchmath = MuchMath()
        res = muchmath.matrixAdd(X,Y)
        ans = [[1,2],[2,2]]
        self.assertEqual(ans, res)

    def test_computelcm(self):
        muchmath = MuchMath()
        res = muchmath.compute_lcm(5,2)
        self.assertEqual(res,10)
        res2 = muchmath.compute_lcm(2,5)
        self.assertEqual(res2,10)

    def test_leapyear(self):
        muchmath = MuchMath()
        if1 = muchmath.leapyear(2021)
        if2 = muchmath.leapyear(2024)
        if3 = muchmath.leapyear(2800)
        el4 = muchmath.leapyear(2700)
        self.assertFalse(if1)
        self.assertTrue(if2)
        self.assertFalse(el4)
        self.assertTrue(if3)

unittest.main()


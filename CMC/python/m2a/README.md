# Python Milestone Part A - Dinosaur Map

VALUE: 20 points
DUE: October 5, 2020

Write a program that creates a map of dinosaur finds within a specified distance of a specified zip code.  You will need to cross reference zipcodes.dat and dinosaur.dat.  Example outputs are provided as:

$ python3 m2a.py -z 23456 -d 5
(see 23456_5.png)

$ python3 m2a.py -z 66208 -d 20
(see 66208_20.png)

$ python3 m2a.py -z 91210 -d 1
(see 91210_1.png)

$ python3 m2a.py -z 62681 -d 2
(see 62681_2.png)

The -z flag refers to a zipcode.  The -d flag refers to a "longitude unit" and "latitude unit" just like in D6.

## Rubric

You have flexibility in exactly how you implement this program, but it must follow the rubric below:

20 POINTS TOTAL

a) 5 points.  Distance calculation performed via functions in a module.  The module should be based on dinodata from the daily assignments.  Reading in zipcode data, dinosaur data, cross-referencing, and calculations should all be performed in this module.

b) 5 points.  Create a new module named mapmaker (not dinodata) with functions that create the map image.  Your dinodata and this new mapmaker module should not communicate directly.  Your main program should use dinodata to get information that you then give to mapmaker.

c) 3 points.  Your mapmaker module should be completely unaware of dinosaur-specific formatted data.  It should just receive GPS coordinates and color data and plot them on a map.  The idea is that dinodata and mapmaker could be used independently for completely different tasks.

d) 2 points.  The points on the map should vary in color based on age.  You may choose the range, but be sure the colors differences are visible.  For example, the newest could be blue and the oldest could be red, with a rainbow of colors in between.  You may normalize the colors to just one one on the map, or you may use a universal normalization for all data entries.

e) 3 points.  You must write independent test scripts for your two modules (mapmaker and dinodata).  Your test scripts should have inputs and outputs specified for every function in the module.  Functions that output visual data like the map image can be verified via sample images that are checked manually.  For example, you would write a program called test_X.py that just calls one function with some sample data.  Then you would also provide a file called, again just for example, figure_X.png.  The idea is that you would manually check figure_X.png against whatever test_X.py displayed.  I will expect a minimum of one test program per function in your modules.

f) 2 points.  You should provide a script called m2a.py that has the -z and -d flags (at a minimum, you may include more) and operates as shown above to generate a map using mapmaker and dinodata.

I will be grading these by hand, so don't worry if your images look a little different from the samples.  But whatever maps you make, they should at least contain the same information (a map background, a black dot for the center of the zipcode, and color dots for each dinosaur find within the specified distance).

## Modules

You may use these modules to aid your quest:

staticmap
matplotlib
math

Do NOT use these modules:

pandas
numpy

If you want to use more modules than that, ask via the Discord #m2a channel.  I may install some more in the official Python installation.

## Logistics

Your program must work on the student machines using the official Python installation.  However, because you're working with images and such, you'll probably want to install Python on your own computer.  You may do this, but you are on your own in terms of tech support.  Unfortunately I don't have time to fix issues on your own computers.

If you are using Linux or Mac, you can access GUI programs on the student machines via the -X flag of ssh:

    $ ssh -C -X USERNAME@student0X.cse.nd.edu

Note you will also want to use the -C flag, which means compression.  Forwarding X windows uses a ton of data, so compressing it will speed things along.

If you are using Windows, there are instructions available here:

http://laptops.eng.uci.edu/software-installation/using-linux/how-to-configure-xming-putty

Basically it just means install a program called Xming and check some flags in PuTTY.

Another option is to use the library computers in Fitzpatrick, which are already set up for X forwarding.

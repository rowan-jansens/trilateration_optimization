# Trilateration Optimization
## INTRODUCTION

This is a model to demonstrate how a satellite constellation of 3+ satellites can 
use optimization to pinpoint the position (x,y,z) of a point when giving the
radius between the point and each satellite.

## RUNNING THE CODE

Code can be compiled using:
$gcc trilateration_code.c -o trilateration_code -lm

Code can be executed using:
$./trilateration_code

## GENERATING PLOTS
By installing gnuplot, you will be able to take a look at the error
functions for a particular configuration.

-To generate a 3d surface plot of the error function for only x and y,
run the "surface.p" script using:
$gnuplot surface.p

-To generate a 2d plot of the individual error functions for each
coordinate, run the "2d.p" script using:
$gnuplot 2d.p

## INTUITION

While each satellites "knows" the radius between it and the point,
the point could lie anywhere on a sphere centered around the satellite.
With multiple satellites, the intersection of these spheres narrow down
the possible locations of the point. In a perfect world, the spheres of
4+ satellites with perfectly measured radii would intersect at exactly
one point.  However, in the real world it is unlikely that you would get
such a perfect scenario and often the spheres do not intersect at a
single point which forces us to find alternative methods to locate the
point.

This model uses a mean square error function to determine how good/bad a
guessed point replaces the actual point by calculating the radius between
the satellites and the guess and comparing those with the true radii
between the sat and the point.  Not surprisingly, plotting the MSE function
(2d.png) for a particular configuration shows that it seems to be a strange
combination of quadratics (it is the mean SQUARED error after all) where
the function drops to near 0 when the guess and the point are equal.

Using a bit of calculus, we know that the slope of a quadratic such as x^2
at a given point is equal to twice the distance from that point to the
minimum of the quadratic.
(e.g. the slope of the graph x^2 at 3 is 3*2 or 6)

In most cases we can divide the slope of the quadratic by 2 to determine
the exact distance we need to move in a given direction to end up at the
minimum. This is VERY convenient! Because the error function is mostly
made of of different combinations of x^2 terms, the program can now
calculate the slope of the error function for a certain guess and get
an exact amount of how much the guess needs to be changed in order to
minimize the function.  If the quadratic error function has terms other
than x^2, we can still use this “half slope” method but we may need to
repeat this cycle a few times to hone in on the minimum (i.e. we won't
get there in just one step, we have to take a little walk)

But there's a catch...

Depending on the configuration of the satellites, the point, and the
initial guess, the minimizer can gut stuck in a local minimum (slope = 0)
that is not the global minimum of the error function (error >> 0).  At
this point, it thinks its has found the point even though the error is
still far from 0.  However, there is an essay fix for this.  Through
graphical analysis, we can see that these "local minimums" are often
symmetrical(ish) with the global minimum. If the program detect that it
has gotten stuck in such a local minimum it simple multiplies its current
guess by (-1) effectively jumping across the y axis and often landing
in/near the true global minimum.

The program runs the above logic in a loop for a few cycles to ensure
that it has arrived at the lowest value possible. It does this for
each varible/axis (x, y, z).  In other words, first it minimizes
the x coordinate, then y, then z, to arive at a solution.

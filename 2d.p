set terminal png size 1000, 700
set output '2d.png'
set datafile separator ','
set grid
set xlabel 'Position'
set ylabel 'MSE'
set title 'Individual Error Functions for the x, y, and z Coordinates for a Given Point+Satellite Configuration'
plot '2d.dat' u 1:2 w l title 'X-coordinate', '2d.dat' u 1:3 w l title 'Y-coordinate', '2d.dat' u 1:4 w l title 'Z-coordinate'

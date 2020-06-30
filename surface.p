set terminal png size 1000, 700
set output 'surface.png'
set datafile separator ','
set pm3d
set grid
set xlabel 'x-coordinate' rotate parallel
set ylabel 'y-coordinate' rotate parallel
set zlabel 'Mean Squared Error' rotate parallel
set title 'Surface Plot of the Error function for a Given Point+Satalite Configuration'
splot 'surface.dat' pt 0 ps 1 title 'MSE of X and Y Coordinates'

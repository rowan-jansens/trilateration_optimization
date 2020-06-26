set terminal png size 1000, 1000
set output '2d.png'
set datafile separator ','
set grid
set xlabel 'Position'
set ylabel 'MSE'
set title 'Plot of the Individual Error function of the x, y, and z Coordinates for a Given Point+Satalite Configuration'
plot '2d_data.csv' u 1:2 w l title 'X-coordinate', '2d_data.csv' u 1:3 w l title 'Y-coordinate', '2d_data.csv' u 1:4 w l title 'Z-coordinate'

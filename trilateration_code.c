#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double x1 = 0;      //set satellite positions
double Y1 = 0;
double z1 = 0;
double x2 = 200;
double y2 = 200;
double z2 = 200;
double x3 = -200;
double y3 = -200;
double z3 = -200;

double px, py, pz;   //the coordinates of the point

double gx, gy, gz;
double disx1, disx2, disx3, offx1, offx2, offx3;     //temporary variables
double disy1, disy2, disy3, offy1, offy2, offy3;
double disz1, disz2, disz3, offz1, offz2, offz3;
double ex1, ex2, ex3, ey1, ey2, ey3, ez1, ez2, ez3;
double stepx, stepy, stepz;
int kill_timex, kill_timey, kill_timez;
int i, j;
char defaults = 'n';

//get Mean Square Error for x axis

double msex(double gx){
  disx1 = fabs(px - x1);
  disx2 = fabs(px - x2);
  disx3 = fabs(px - x3);
  offx1 = fabs(gx - x1);
  offx2 = fabs(gx - x2);
  offx3 = fabs(gx - x3);
  ex1 = disx1 - offx1;
  ex2 = disx2 - offx2;
  ex3 = disx3 - offx3;
  return (pow(ex1, 2) + pow(ex2, 2) + pow(ex3, 2)) / 3;  
}

//get Mean Square Error for y axis

double msey(double gy){
  disy1 = fabs(py - Y1);
  disy2 = fabs(py - y2);
  disy3 = fabs(py - y3);
  offy1 = fabs(gy - Y1);
  offy2 = fabs(gy - y2);
  offy3 = fabs(gy - y3);
  ey1 = disy1 - offy1;
  ey2 = disy2 - offy2;
  ey3 = disy3 - offy3;
  return (pow(ey1, 2) + pow(ey2, 2) + pow(ey3, 2)) / 3;  
}

//get Mean Square Error fo z axis

double msez(double gz){
  disz1 = fabs(pz - z1);
  disz2 = fabs(pz - z2);
  disz3 = fabs(pz - z3);
  offz1 = fabs(gz - z1);
  offz2 = fabs(gz - z2);
  offz3 = fabs(gz - z3);
  ez1 = disz1 - offz1;
  ez2 = disz2 - offz2;
  ez3 = disz3 - offz3;
  return (pow(ez1, 2) + pow(ez2, 2) + pow(ez3, 2)) / 3;  
}

//get x-axis error slope

double get_slopex(double gx){
  return (msex(gx+0.000001)-msex(gx))/((gx+0.000001)-gx);
    }

//get y-axis error slope

double get_slopey(double gy){
  return (msey(gy+0.000001)-msey(gy))/((gy+0.000001)-gy);
    }

//get z-axis error slope

double get_slopez(double gz){
  return (msez(gz+0.000001)-msez(gz))/((gz+0.000001)-gz);
    }

int setup(){
  printf("Would you like to use a default satellite configuration? (y/n)\n");
  scanf("%c", &defaults);

  printf("Please enter the coordinates (x y z) of a point: \n");
  scanf("%lf %lf %lf", &px, &py, &pz);

  if (defaults == 'n'){
    printf("Enter the coordinates (x y z) of the 1st satellite: ");
    scanf("%lf %lf %lf", &x1, &Y1, &z1);
    printf("Enter the coordinates (x y z) of the 2nd satellite: ");
    scanf("%lf %lf %lf", &x2, &y2, &z2);
    printf("Enter the coordinates (x y z) of the 3rd satellite: ");
    scanf("%lf %lf %lf", &x3, &y3, &z3);
  }
  return 0;
}

int main(){

  setup();
  gx = 0;       //set initial guess points
  gy = 0;
  gz = 0;
  kill_timex = 0;     //kill_time prevents endless looping error
  kill_timey = 0;
  kill_timez = 0;

  //run optimization for each axis
  
  //Un-comment the "printf" staments to see the steps the program
  //takes during optimization

  while (msex(gx) > 0.0001 && kill_timex < 6){
    if (get_slopex(gx) < 0.0001 && get_slopex(gx) > -0.0001){
      if(msex(gx) > msex(gx * -1)){
        gx = gx * -1;
      }
    }
    else{
      //printf("Current X Poistion: %f, Error: %f, Error Slope: %f, Step: %f\n",
      //gx, msex(gx), get_slopex(gx), get_slopex(gx)/2);
      stepx = (get_slopex(gx)/2);
      gx = gx - stepx;
      kill_timex++;
    }
  }
  
  while (msey(gy) > 0.0001 && kill_timey < 6){
    if (get_slopey(gy) < 0.0001 && get_slopey(gy) > -0.0001){
      if(msey(gy) > msey(gy * -1)){
	gy = gy * -1;
      }
    }
    else{
      //printf("Current Y Poistion: %f, Error: %f, Error Slope: %f, Step: %f\n",
      //gy, msey(gy), get_slopey(gy), get_slopey(gy)/2);
      stepy = (get_slopey(gy)/2);
      gy = gy - stepy;
      kill_timey++;
    }
  }
  
  while (msez(gz) > 0.0001 && kill_timez < 6){
    if (get_slopez(gz) < 0.0001 && get_slopez(gz) > -0.0001){
      if(msez(gz) > msez(gz * -1)){
    gz = gz * -1;
      }
    }
    else{
      //printf("Current Z Poistion: %f, Error: %f, Error Slope: %f, Step: %f\n",
      //gz, msez(gz), get_slopez(gz), get_slopez(gz)/2);
      stepz = (get_slopez(gz)/2);
      gz = gz - stepz;
      kill_timez++;
    }
  }

  //print out the cords of the calculated point along with the error
  printf("X: %f\t\tError: %f\nY: %f\t\tError: %f\nZ: %f\t\tError: %f\n",
  gx, msex(gx), gy, msey(gy), gz, msez(gz));


  //create a data file for a 3d surface plot for 2 of the 3 variable
  
  FILE * fpointer1 = fopen("surface.dat", "w");
  for (j=1000; j>=-1000; j-=10){
    for (i=-1000; i<=1000; i+=10){
      fprintf(fpointer1, "%d,%d,%f\n",i, j, ((msex(i) + msey(j)) / 100000));
	}
    fprintf(fpointer1, "\n");
  }
  fclose(fpointer1);

  //create a data file for a 2d surface plot for all 3 variables
  
  FILE * fpointer2 = fopen("2d.dat", "w");
  for (i=-1000; i<=1000; i+=10){
    fprintf(fpointer2, "%d,%f,%f,%f\n", i, msex(i) / 100000, msey(i) / 100000, msez(i) / 100000);
	}
  fclose(fpointer2);

  return 0;
}

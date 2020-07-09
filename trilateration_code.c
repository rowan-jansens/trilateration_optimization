#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int sat_num = 8;   //how many satellites the system will use (up to 24)

double sat[24][3] = {   //define the cords of each satellite (up to 24)
  {-500, 500, -500},
  {-500, -500, -500},
  {500, -500, -500},
  {500, 500, -500},
  {-500, 500, 500},
  {-500, -500, 500},
  {500, -500, 500},
  {500, 500, 500}
};

double point[3];  //the cords of the point to be trilaterated

int i, j, k, a; //for-loop variables

//return mse when given a guess and axis(x y or z)
//Axis: x = 0, y = 1, z = 2
double mse(int axis, double guess){   
  double mse_val = 0;
  for (i = 0; i < sat_num; i++){
    double distance_real = fabs(point[axis] - sat[i][axis]);
    double distance_guess = fabs(guess - sat[i][axis]);
    double error = fabs(distance_real - distance_guess);
    mse_val = mse_val + pow(error, 2);
    }
  return (mse_val / sat_num);
}

//return slope of mse for a given guess and axis
double slope(int axis, double guess){
  double guess_prime = guess + 0.000001;
  double delta_y = mse(axis, guess_prime) - mse(axis, guess);
  double delta_x = guess_prime - guess;
  return (delta_y / delta_x);
}

//optimizer to find guess with minimum error
double optimize(int axis, double guess){
  int kill = 0;
  char variables[3] = {'X', 'Y', 'Z'};
  printf("Position: %f, Error: %f, Slope: %f, Step: %f\n",
  guess, mse(axis, guess), slope(axis, guess), slope(axis, guess) / -2);
  while (mse(axis, guess) > 0.001 && kill < 6){    
    if (slope(axis, guess) < 0.001 && slope(axis, guess) > -0.001){
      guess = guess * -1;
    }
    else{
      guess += (slope(axis, guess) / -2);
    }
    printf("Position: %f, Error: %f, Slope: %f, Step: %f\n",
    guess, mse(axis, guess), slope(axis, guess), slope(axis, guess) / -2);
  }
  printf("%c Coordinate: %f\n\n", variables[a], guess);
}

//make some data for graphs
int make_data(){
  FILE * fpointer1 = fopen("surface.dat", "w");
  for (j=2000; j>=-2000; j-=50){
    for (k=-2000; k<=2000; k+=50){
      fprintf(fpointer1, "%d %d %f\n", k, j, ((mse(0, k) + mse(1, j)) / 100000));
	}
    fprintf(fpointer1, "\n");
  }
  fclose(fpointer1);


  FILE * fpointer2 = fopen("2d.dat", "w");
  for (j = -2000; j < 2000; j += 20){
      fprintf(fpointer2, "%d %f %f %f\n", j, mse(0, j) / 100000, mse(1, j) / 100000, mse(2, j) / 100000);
  }
  fclose(fpointer2);
}


int set_sat(){
  printf("How many satelites would you like to define? (max 24) ");
  scanf("%d", &sat_num);
  for (i=0; i<sat_num; i++){
    printf("Enter coordinates of satellite #%d (x, y, z): ", (i+1));
    scanf("%lf, %lf, %lf", &sat[i][0], &sat[i][1], &sat[i][2]);
  }
}

int setup(){
  char defaults;
  printf("Would you like to use a default satellite configuration? (y/n) ");
  scanf("%c", &defaults);
  if (defaults == 'n'){
    set_sat();
  }
  printf("Enter a point to be trilaterated: (x, y, z) ");
  scanf("%lf, %lf, %lf", &point[0], &point[1], &point[2]);
  printf("\n");
}

int main(){

  setup();
 
  for (a = 0; a < 3; a++){    //loop through all three axis and optimize
    double guess = sat[0][a];
    optimize(a, guess);
  }

  make_data();

  return 0;
}


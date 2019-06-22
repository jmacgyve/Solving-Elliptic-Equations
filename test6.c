#include<stdio.h>
#include<math.h>
#include <time.h>
int N = 10;
long double h = 0.1; //1/N
long double  eps = 0.000001;
int	COUNT = 0;
long double beta = 1.0;

void print_array(long double array[N+1][N+1]);
void init_array(long double array[N+1][N+1]);
void boundary_condition(long double array[N+1][N+1]);
void anal_solution(long double **p, int N);
long double f_xy_00(int i, int j);
long double f_xy_minus10(int i, int j);
long double max_value(long double arr[]);
long double Norm(long double U[N+1][N+1], long double NEW[N+1][N+1]);
void    Jacobi(long double U[N+1][N+1], long double NEW[N+1][N+1]);
char is_point_in_cyrcle(long double i, long double j);
void left_linear_interpolation(int i, int j, long double U[N+1][N+1], long double NEW[N+1][N+1]);
void right_linear_interpolation(int i, int j, long double U[N+1][N+1], long double NEW[N+1][N+1]);
void up_slinear_interpolation(int i, int j, long double U[N+1][N+1], long double NEW[N+1][N+1]);
void down__linear_interpolation(int i, int j, long double U[N+1][N+1], long double NEW[N+1][N+1]);
long double double_left_linear_interpolation(int i, int j, long double U[N+1][N+1]);
long double double_right_linear_interpolation(int i, int j, long double U[N+1][N+1]);
long double double_up_linear_interpolation(int i, int j, long double U[N+1][N+1]);
long double double_down_linear_interpolation(int i, int j, long double U[N+1][N+1]);

int main(){
  long double array[N+1][N+1];
  long double new[N+1][N+1];

  init_array(array); init_array(new);
  boundary_condition(array); boundary_condition(new);
  print_array(array);
  printf("\n\n\n\n\n");
  Jacobi(array, new);
  //print_array(new);
  return 0;
}

void print_array(long double array[N+1][N+1]){
  int i = 0, j = 0;
        while(i < (N+1))
        {
                j = 0;
                while(j < (N+1))
                {
                        printf("%-10Lf ", array[i][j]);
                        j++;
                }
                printf("\n");
                i++;
        }
	return ;
}

void init_array(long double array[N+1][N+1]){
  int i = 1, j = 1;
	while(i < N)
	{	j = 1;
		while(j < N)
		{
			array[i][j] = 1.0;
			j++;
		}
		i++;
	}
}

void boundary_condition(long double array[N+1][N+1]){
  int i = 0;
  int j = 0;
  while((i < (N+1)) && (j < (N + 1)))
	{
		array[0][j] = 0.0;
		array[i][0] = 0.0;
		array[N][j] = j * h;
		array[i][N] = i * h;
		i++;			j++;
	}
}

long double f_xy_00(int i, int j){
  return 0.0; //f(x,y) = 0
}

long double f_xy_minus10(int i, int j){
  return -10.0; //f(x,y) = -10
}

void anal_solution(long double **p, int N){
    int i,j;
    for (i=0;i<N+1;i++){
        for (j=0;j<N+1;j++){
            p[i][j] = i*j*h*h; }}
}

long double max_value(long double arr[]){
	long double res = 0;
	int c = 0;
	res = arr[0];
	while(c < (N+1))
        {
        	if(arr[c] > res)
                        res = arr[c];
                c++;
        }
	return res;
}

long double Norm(long double U[N+1][N+1], long double NEW[N+1][N+1]){
	int i = 0;
	int j = 0;
	int r = 0;
	int c;
	long double temp[N+1][N+1];
	long double max[N+1];
	long double pre_res[N+1];
	long double res;
	while(i < (N+1))
	{
		j = 0;
		while(j < (N+1))
		{
			temp[i][j] = NEW[i][j] - U[i][j];
			temp[i][j] = fabsl(temp[i][j]);
			max[j] = temp[i][j];
			j++;
		}
		pre_res[r] = max_value(max);
		r++;
		i++;
	}
	res = max_value(pre_res);
	return res;
}

char is_point_in_cyrcle(long double i, long double j){
  char t = 't', f = 'f';
  if (((i - 0.2)*(i - 0.2) + (j - 0.25)*(j - 0.25) - 0.04) < 0){
    return t;
  }
  else return f;
}

void left_linear_interpolation(int i, int j, long double U[N+1][N+1], long double NEW[N+1][N+1]){
  //TODO f_xy_minus10 ПОМЕНЯТЬ НА -10!!!
  long double x = i*h, y = j*h;
  long double tmp_value = 0.0;
  long double delta = 0.0;
  delta = -sqrt(0.2*0.2 - (y-0.25)*(y-0.25)) + 0.5 - (x-1);
  tmp_value = (-U[i][j]*(delta/(h-delta))) + (-10)*(h/(h-delta));
  NEW[i][j] = (U[i+1][j]+ tmp_value + U[i][j+1]+U[i][j-1] - h*h*(-10))/4;
}

void right_linear_interpolation(int i, int j, long double U[N+1][N+1], long double NEW[N+1][N+1]){
  //TODO f_xy_minus10 ПОМЕНЯТЬ НА -10!!!
  long double x = i*h, y = j*h;
  long double tmp_value = 0.0;
  long double delta = 0.0;
  delta = (x+1) - sqrt(0.2*0.2 - (y-0.25)*(y-0.25)) + 0.5;
  tmp_value = (-U[i][j]*(delta/(h-delta))) + (-10)*(h/(h-delta));
  NEW[i][j] = (tmp_value + U[i-1][j] + U[i][j+1]+U[i][j-1] - h*h*(-10))/4;
}

void up_linear_interpolation(int i, int j, long double U[N+1][N+1], long double NEW[N+1][N+1]){
  //TODO f_xy_minus10 ПОМЕНЯТЬ НА -10!!!
  long double x = i*h, y = j*h;
  long double tmp_value = 0.0;
  long double delta = 0.0;
  delta = (y+1) - sqrt(0.2*0.2 - (x-0.5)*(x-0.5)) + 0.25;
  tmp_value = (-U[i][j]*(delta/(h-delta))) + (-10)*(h/(h-delta));
  NEW[i][j] = (U[i+1][j] + U[i-1][j] + tmp_value + U[i][j-1] - h*h*(-10))/4;
}

void down__linear_interpolation(int i, int j, long double U[N+1][N+1], long double NEW[N+1][N+1]){
  //TODO f_xy_minus10 ПОМЕНЯТЬ НА -10!!!
  long double x = i*h, y = j*h;
  long double tmp_value = 0.0;
  long double delta = 0.0;
  delta = - sqrt(0.2*0.2 - (x-0.5)*(x-0.5)) + 0.25 - (y-1);
  tmp_value = (-U[i][j]*(delta/(h-delta))) + (-10)*(h/(h-delta));
  NEW[i][j] = (U[i+1][j] + U[i-1][j] + U[i][j+1] + tmp_value - h*h*(-10))/4;
}

void Jacobi(long double U[N+1][N+1], long double NEW[N+1][N+1]){
  long double tot_time = 0.0;
  time_t start_t =0, end_t =0;
  start_t = clock();
	int i = 1;
	int j = 1;
	long double res;
  long double tmp_value = 0.0;
	while(i < N)
	{
		j = 1;
		while(j < N)
		{
      if ((is_point_in_cyrcle(i*h, j*h)) == 't' ){
          if (is_point_in_cyrcle((i-1)*h, j*h) == 'f') { U[i-1][j] = double_left_linear_interpolation(i, j, U); } //NEW[i][j] = (U[i+1][j] + tmp_value + U[i][j+1]+U[i][j-1]-h*h*(-10))/4;       printf("%f\n", NEW[i][j]);}
          if (is_point_in_cyrcle((i+1)*h, j*h) == 'f') {U[i+1][j] = double_right_linear_interpolation(i, j, U);} //NEW[i][j] = (tmp_value + U[i-1][j]+U[i][j+1]+U[i][j-1]-h*h*(-10))/4;}
         if (is_point_in_cyrcle(i*h, (j+1)*h) == 'f') {U[i][j+1] = double_up_linear_interpolation(i, j, U);}  //NEW[i][j] = (U[i+1][j] + U[i-1][j]+tmp_value+U[i][j-1]-h*h*(-10))/4;}
          if (is_point_in_cyrcle(i*h, (j-1)*h) == 'f') {U[i][j-1] = double_down_linear_interpolation(i, j, U);} //NEW[i][j] = (U[i+1][j] + U[i-1][j]+U[i][j+1]+tmp_value-h*h*(-10))/4;}
          NEW[i][j] = (U[i+1][j]+U[i-1][j]+U[i][j+1]+U[i][j-1]-h*h*(-10))/4;
          long double a = NEW[i][j];
          //printf("%Lf\n", a);
      }
      else{
        NEW[i][j] = (U[i+1][j]+U[i-1][j]+U[i][j+1]+U[i][j-1])/4;
      }
			j++;
		}
		i++;
	}
//print_array(NEW);
//printf("\n\n\n\n\n");
	//если норма больше погрешности
	res = Norm(U, NEW);
	if(res > eps)
	{
		COUNT++;
		i = 1; j = 1;
		while(i < N)
		{
			j = 1;
			while(j < N)
			{
				U[i][j] = NEW[i][j];
				j++;
			}
			i++;
		}
		Jacobi(U, NEW);
	}
	else
	{
    end_t = clock();
    tot_time = (long double)(end_t - start_t)/(CLOCKS_PER_SEC);
		printf("res = %Lf; COUNT = %d; time = %Lf s\n" , res, COUNT, tot_time);
    print_array(NEW);
	}
	return ;
}

long double double_left_linear_interpolation(int i, int j, long double U[N+1][N+1]){
  //TODO f_xy_minus10 ПОМЕНЯТЬ НА -10!!!
  long double x = i*h, y = j*h;
  long double tmp_value = 0.0;
  long double delta = 0.0;
  delta = -sqrt(0.2*0.2 - (y-0.25)*(y-0.25)) + 0.5 - (x-1);
  tmp_value = (-U[i][j]*(delta/(h-delta))) + (-10)*(h/(h-delta));
  return tmp_value;
}

long double double_right_linear_interpolation(int i, int j, long double U[N+1][N+1]){
  //TODO f_xy_minus10 ПОМЕНЯТЬ НА -10!!!
  long double x = i*h, y = j*h;
  long double tmp_value = 0.0;
  long double delta = 0.0;
  delta = (x+1) - sqrt(0.2*0.2 - (y-0.25)*(y-0.25)) + 0.5;
  tmp_value = (-U[i][j]*(delta/(h-delta))) + (-10)*(h/(h-delta));
  return tmp_value;
}

long double double_up_linear_interpolation(int i, int j, long double U[N+1][N+1]){
  //TODO f_xy_minus10 ПОМЕНЯТЬ НА -10!!!
  long double x = i*h, y = j*h;
  long double tmp_value = 0.0;
  long double delta = 0.0;
  delta = (y+1) - sqrt(0.2*0.2 - (x-0.5)*(x-0.5)) + 0.25;
  tmp_value = (-U[i][j]*(delta/(h-delta))) + (-10)*(h/(h-delta));
  return tmp_value;
}

long double double_down_linear_interpolation(int i, int j, long double U[N+1][N+1]){
  //TODO f_xy_minus10 ПОМЕНЯТЬ НА -10!!!
  long double x = i*h, y = j*h;
  long double tmp_value = 0.0;
  long double delta = 0.0;
  delta = - sqrt(0.2*0.2 - (x-0.5)*(x-0.5)) + 0.25 - (y-1);
  tmp_value = (-U[i][j]*(delta/(h-delta))) + (-10)*(h/(h-delta));
  return tmp_value;
}

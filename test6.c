#include<stdio.h>
#include<math.h>
#include <time.h>
int N = 10;
double h = 0.1; //1/N
double  eps = 0.000001;
int	COUNT = 0;

void print_array(double array[N+1][N+1]);
void init_array(double array[N+1][N+1]);
void boundary_condition(double array[N+1][N+1]);
void anal_solution(double **p, int N);
double f_xy_00(int i, int j);
double f_xy_minus10(int i, int j);
double max_value(double arr[]);
double Norm(double U[N+1][N+1], double NEW[N+1][N+1]);
void    Jacobi(double U[N+1][N+1], double NEW[N+1][N+1]);
char is_point_in_cyrcle(double i, double j);

int main(){
  double array[N+1][N+1];
  double new[N+1][N+1];

  init_array(array); init_array(new);
  boundary_condition(array); boundary_condition(new);
  //print_array(array);
  printf("\n\n\n\n\n");
  Jacobi(array, new);
  //print_array(new);
  return 0;
}

void print_array(double array[N+1][N+1]){
  int i = 0, j = 0;
        while(i < (N+1))
        {
                j = 0;
                while(j < (N+1))
                {
                        printf("%-10f ", array[i][j]);
                        j++;
                }
                printf("\n");
                i++;
        }
	return ;
}

void init_array(double array[N+1][N+1]){
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

void boundary_condition(double array[N+1][N+1]){
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

double f_xy_00(int i, int j){
  return 0.0; //f(x,y) = 0
}

double f_xy_minus10(int i, int j){
  return -10.0; //f(x,y) = -10
}

void anal_solution(double **p, int N){
    int i,j;
    for (i=0;i<N+1;i++){
        for (j=0;j<N+1;j++){
            p[i][j] = i*j*h*h; }}
}

double max_value(double arr[]){
	double res = 0;
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

double Norm(double U[N+1][N+1], double NEW[N+1][N+1]){
	int i = 0;
	int j = 0;
	int r = 0;
	int c;
	double temp[N+1][N+1];
	double max[N+1];
	double pre_res[N+1];
	double res;
	while(i < (N+1))
	{
		j = 0;
		while(j < (N+1))
		{
			temp[i][j] = NEW[i][j] - U[i][j];
			temp[i][j] = fabs(temp[i][j]);
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

void Jacobi(double U[N+1][N+1], double NEW[N+1][N+1]){
  double tot_time = 0.0;
  time_t start_t =0, end_t =0;
  start_t = clock();
	int i = 1;
	int j = 1;
  double beta = 1.0;
	double res;

  int point_position = 0;
	while(i < N)
	{
		j = 1;
		while(j < N)
		{
      if ((is_point_in_cyrcle(i*h, j*h)) == 't' ){
        //printf("%f ", i*h);
        if(is_point_in_cyrcle((i-1)*h, j*h) == 'f') point_position++;
        if (is_point_in_cyrcle((i+1)*h, j*h) == 'f') point_position++;
        if (is_point_in_cyrcle(i*h, (j+1)*h) == 'f')point_position++;
        if (is_point_in_cyrcle(i*h, (j-1)*h) == 'f') point_position++;

        printf("%d\n", point_position);
        point_position = 0;
        switch (point_position) {
          case 1:
            //printf("SLEVA TOCHKA\n");
            break;
          case 2:
            printf("SPRAVA TOCHKA\n");
            break;
          case 3:
           //printf("VVERHU TOCHKA\n");
            break;
          case 4:
            //printf("VNIZU TOCHKA\n");
            break;
        }
      }
      else {
        NEW[i][j] = (U[i+1][j]+U[i-1][j] + pow(beta,2)*(U[i][j+1]+U[i][j-1]) - h*h*f_xy_00(i,j))/(2*(1+pow(beta,2)));
      }
			j++;
		}
		i++;
	}

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
    tot_time = (double)(end_t - start_t)/(CLOCKS_PER_SEC);
		printf("res = %f; COUNT = %d; time = %fs\n" , res, COUNT, tot_time);
    //print_NEW(NEW);
	}
	return ;
}

char is_point_in_cyrcle(double i, double j){
  char t = 't', f = 'f';
  if (((i - 0.2)*(i - 0.2) + (j - 0.25)*(j - 0.25) - 0.04) < 0){
    return t;
  }
  else return f;
}

void linear_interpolation(){
  
}

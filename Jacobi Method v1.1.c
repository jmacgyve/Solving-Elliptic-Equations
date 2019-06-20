//Eugene Goldyrev 2019
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//......ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ......//

int	COUNT = 0;
int	N = 111; //размер сетки NхN
double  eps = 0.000001; //точность - задается зависимо от задачи

//. . . . . Ф У Н К Ц И И . . . . . //
/*
Матрица U - начальная - k итерация
Матрица NEW - матрица k+1 итерации
*/
void    print_U(double U[N+1][N+1]);
void    print_NEW(double NEW[N+1][N+1]);
double	Norm(double U[N+1][N+1], double NEW[N+1][N+1]);       //    || NEW - U || < E
double	max_value(double arr[]); //max массива
void    Jacobi(double U[N+1][N+1], double NEW[N+1][N+1]);

int	main()
{
	double U[N+1][N+1];
	double NEW[N+1][N+1];

	int i = 0;
	int j = 0;
	double h = 0.1; // 1/N = 1/10 = 0.1

	//задание граничных условий
	while((i < (N+1)) && (j < (N + 1)))
	{
		U[0][j] = 0.0;		NEW[0][j] = 0.0;
		U[i][0] = 0.0;		NEW[i][0] = 0.0;
		U[N][j] = j * h;	NEW[N][j] = j * h;
		U[i][N] = i * h;	NEW[i][N] = i * h;
		i++;			j++;
	}

	//задание начального приближения
	i = 1; j = 1;
	while(i < N)
	{	j = 1;
		while(j < N)
		{
			U[i][j] = 1.0;
			j++;
		}
		i++;
	}

	printf("МАТРИЦА В САМОМ НАЧАЛЕ С ГРАНИЧНЫМИ УСЛОВИЯМИ И НАЧАЛЬНЫМ ПРИБЛИЖЕНИЕМ\n");
	print_U(U);
	printf("\n"); printf("\n"); printf("\n");

	Jacobi(U, NEW);
	return 0;
}

void	print_U(double U[N+1][N+1])
{
	int i = 0, j = 0;
        while(i < (N+1))
        {
                j = 0;
                while(j < (N+1))
		{
                        printf("%-10f ", U[i][j]);
                        j++;
                }
                printf("\n");
                i++;
        }
	return ;
}

void	print_NEW(double NEW[N+1][N+1])
{
	int i = 0, j = 0;
        while(i < (N+1))
        {
                j = 0;
                while(j < (N+1))
                {
                        printf("%-10f ", NEW[i][j]);
                        j++;
                }
                printf("\n");
                i++;
        }


	return ;
}

double max_value(double arr[])
{
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

double Norm(double U[N+1][N+1], double NEW[N+1][N+1])
{
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

void    Jacobi(double U[N+1][N+1], double NEW[N+1][N+1])
{
	int i = 1;
	int j = 1;
	double res;
	while(i < N)
	{
		j = 1;
		while(j < N)
		{
			NEW[i][j] = 0.25*(U[i+1][j] + U[i-1][j] + U[i][j+1] + U[i][j-1]);
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
		printf("res = %f\n COUNT = %d\n", res, COUNT);
//		print_NEW(NEW);
	}
	return ;
}

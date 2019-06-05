#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//не работает при граничном условии if (((i*dx - 0.33333)*(i*dx - 0.33333)+(j*dy-0.5)*(j*dy-0.5) - 0.04) == 0) F(x,y) = -10
//else if (((i*dx - 0.33333)*(i*dx - 0.33333)+(j*dy-0.5)*(j*dy-0.5) - 0.04) != 0) F(x,y) = 0
//1399 итераций
//граничные условия соблюдены 
//ВСЕГДА return 0.0;
#define ROW 101
#define COL 101
#define pi 3.141592
#define itmax 10000

void    poisson_solver(double **u, double **u_anal, double tol, double omega, int BC, int method, char *dir_name);
double func0(int i,int j,double dx,double dy);
double funcMinus10(int i,int j,double dx,double dy);
void initialization(double **p);
void error_rms(double **p, double **p_anal, double *err);
void func_anal(double **p, int row_num, int col_num, double dx, double dy);
void write_u(char *dir_nm,char *file_nm, double **p,double dx, double dy);
void SOR(double **p,double dx, double dy, double tol, double omega, double *tot_time,int *iter,int BC);

int main(void)
{
    double **u;
    double **u_anal;

    char *dir_name ;

    int i, method, BC;
    double tol, omega;

    int make_fold= system("mkdir RESULT");

    // --------------------------------------------------------
    //                    Выделение памяти
    // --------------------------------------------------------
    u      = (double **) malloc(ROW *sizeof(double));
    u_anal = (double **) malloc(ROW *sizeof(double));

    for (i=0;i<ROW;i++)
    {
      u[i]      = (double *) malloc(COL * sizeof(double));
      u_anal[i] = (double *) malloc(COL * sizeof(double));
    }

    //--------------------
    //   Параметры для работы
    //--------------------
    tol = 1e-8;
    omega = 1.8;
    dir_name = "./RESULT/";

    printf("\n");
    printf("---------------------------------------- \n");
    printf("Nx : %d, Ny : %d\n",ROW,COL);
    printf("Tolerance : %f, Omega : %f \n",tol, omega);
    printf("---------------------------------------- \n");
    printf("\n");


    BC = 2;
    method = 2; //SOR Method

    poisson_solver(u,u_anal,tol,omega,BC,method,dir_name);

    free(u);
    free(u_anal);

    return 0;
}

void    poisson_solver(double **u, double **u_anal, double tol, double omega, int BC, int method, char *dir_name)
{

  char *file_name ;

  int iter = 0;
  double Lx = 1.0, Ly = 1.0;
  double dx, dy, err = 0, tot_time = 0;

  dx = Lx/(ROW-1);
  dy = Ly/(COL-1);

  //-----------------------------
  //      Analytic Solutions
  //-----------------------------
  file_name = "Analytic_solution.plt";
  func_anal(u_anal,ROW,COL,dx,dy);

  write_u(dir_name,file_name,u_anal,dx,dy);

  switch (method)
  {
    case 2 :
       //-----------------------------
       //         SOR Method
       //-----------------------------
       initialization(u);
       SOR(u,dx,dy,tol,omega,&tot_time,&iter,BC);
       error_rms(u,u_anal,&err);
       printf("HardCase SOR  4 - Error : %e, Iteration : %d, Time : %f s \n",err,iter,tot_time);

       file_name = "SOR_result.plt";
       write_u(dir_name,file_name,u,dx,dy);
      break;
  }

}

double func0(int i,int j,double dx,double dy)
{
    return (0.0);
}

double funcMinus10(int i,int j,double dx,double dy)
{
    return (-10.0);
}

void initialization(double **p)
{
    int i,j;
    for (i=0;i<ROW;i++){
        for (j=0;j<COL;j++){
            p[i][j] = 0.0; }}

}

void error_rms(double **p, double **p_anal, double *err)
{
  int i,j;
  for (i=0;i<ROW;i++){
    for (j=0;j<COL;j++){
      *err = *err + pow(p[i][j] -p_anal[i][j],2);
    }
  }

  *err = sqrt(*err)/(ROW*COL);
}


void func_anal(double **p, int row_num, int col_num, double dx, double dy)
{
    int i,j;
    for (i=0;i<row_num;i++){
        for (j=0;j<col_num;j++){
            p[i][j] = i*dx*j*dy; }} //U(x,y) = xy;
}

void write_u(char *dir_nm,char *file_nm, double **p,double dx, double dy)
{
    FILE* stream;
    int i,j;
    char file_path[50];
    sprintf(file_path,"%s%s",dir_nm,file_nm);

    stream=fopen(file_path,"w");
    fprintf(stream,"ZONE I=%d J=%d \n",ROW,COL);
    for (i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
          fprintf(stream,"%f %f %f \n",i*dx,j*dy,p[i][j]); }}
          //  fprintf(stream,"%f %f\n",i*dx, j*dy); }}
    fclose(stream);
}


void SOR(double **p,double dx, double dy, double tol, double omega, double *tot_time,int *iter,int BC)
{
    int i,j,k,it;
    double beta,rms;
    double SUM1,SUM2;
    double **p_new;
    time_t start_t =0, end_t =0;
    double analSolReterned = 0.0;

    start_t = clock();
    beta = dx/dy;

    p_new = (double **) malloc(ROW *sizeof(double));
    for (i=0;i<ROW;i++)
    {
      p_new[i]      = (double *) malloc(COL * sizeof(double));
    }

    initialization(p_new);

    for (it=1;it<itmax;it++){
        SUM1 = 0;
        SUM2 = 0;

        for (i=1;i<ROW-1;i++){
            for (j=1;j<COL-1;j++){

                //if ((pow((i*dx-0.33333),2)+pow((j*dy-0.5),2)-0.04) == 0) analSolReterned = -10.0;
              //  else analSolReterned = 0.0;
              if (((i*dx - 0.33333)*(i*dx - 0.33333)+(j*dy-0.5)*(j*dy-0.5) - 0.04) == 0)
              {
                analSolReterned = -10.0;
                printf("CATCHED %f\n\n\n\n", analSolReterned);
                return ;
              }
              else analSolReterned = 0.0;




                p_new[i][j] =  (p[i+1][j]+p_new[i-1][j]
                                + pow(beta,2) *(p[i][j+1]+p_new[i][j-1])
                                - dx*dx*analSolReterned)/(2*(1+pow(beta,2)));
                p_new[i][j] = p[i][j] + omega * (p_new[i][j] - p[i][j]);
            }
        }

        //------------------------
        //  Boundary conditions
        //------------------------

        // Boundary - Case 2
        if (BC ==2){
          for (j=0;j<COL;j++){
              p_new[0][j] = 0.0;
              p_new[ROW-1][j] = j*dy;
          }

          for (i=0;i<ROW;i++) {
              p_new[i][0] = 0.0;
              p_new[i][COL-1] = i*dx;
          }
        }

        //------------------------
        //  Алгоритм
        //------------------------
        for (i=1;i<ROW-1; i++){
            for (j=1;j<COL-1;j++){

              //if ((pow((i*dx-0.33333),2)+pow((j*dy-0.5),2)-0.04) == 0) analSolReterned = -10.0;
            //  else analSolReterned = 0.0;
            if (((i*dx - 0.33333)*(i*dx - 0.33333)+(j*dy-0.5)*(j*dy-0.5) - 0.04) == 0)
            {
              analSolReterned = -10.0;
              printf("CATCHED %f\n\n\n\n", analSolReterned);
              return ;
            }
            else analSolReterned = 0.0;



                SUM1 += fabs(p_new[i][j]);
                SUM2 += fabs(p_new[i+1][j] + p_new[i-1][j]
                             + pow(beta,2)*(p_new[i][j+1] + p_new[i][j-1])
                             - (2+2*pow(beta,2))*p_new[i][j]-dx*dx*analSolReterned);
            }
        }

        if ( SUM2/SUM1 < tol ){
            free(p_new);
            *iter = it;
            end_t = clock();
            *tot_time = (double)(end_t - start_t)/(CLOCKS_PER_SEC);
            break;
        }
        // printf("Iteration : %d, SUM1 : %f, SUM2 : %f, Ratio : %f \n",it,SUM1,SUM2,SUM2/SUM1);
        //------------------------
        //         Update
        //------------------------
        for (i=0;i<ROW;i++){
            for (j=0;j<COL;j++){
                p[i][j] = p_new[i][j];}}

    }
    for (i=0;i<ROW;i++){
        for (j=0;j<COL;j++){
            printf("%f ", p[i][j]);}
          printf("\n");}

}

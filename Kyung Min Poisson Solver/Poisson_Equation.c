#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"

//-----------------------------------
//        Productivity tools
//-----------------------------------

void poisson_solver(double **u, double **u_anal, double tol, double omega,
                    int BC, int method, char *dir_name);

int main(void)
{
    double **u;
    double **u_anal;

    char *dir_name ;

    int i, method, BC;
    double tol, omega;

    int make_fold= system("mkdir RESULT");

    // --------------------------------------------------------
    //                    Memory allocation
    // --------------------------------------------------------
    u      = (double **) malloc(ROW *sizeof(double));
    u_anal = (double **) malloc(ROW *sizeof(double));

    for (i=0;i<ROW;i++)
    {
      u[i]      = (double *) malloc(COL * sizeof(double));
      u_anal[i] = (double *) malloc(COL * sizeof(double));
    }

    //--------------------
    //   Initial setting
    //--------------------
    tol = 1e-6;
    omega = 1.8;
    dir_name = "./RESULT/";

    printf("\n");
    printf("---------------------------------------- \n");
    printf("Nx : %d, Ny : %d\n",ROW,COL);
    printf("Tolerance : %f, Omega : %f \n",tol, omega);
    printf("---------------------------------------- \n");
    printf("\n");

    //----------------------------------------
    //       Poisson Solver Type
    //
    // BC = 1 : Boundary condition Case 2
    // method = 1 : Jacobi method
    BC = 2;
    method = 1;

    poisson_solver(u,u_anal,tol,omega,BC,method,dir_name);

    free(u);
    free(u_anal);

    return 0;
}

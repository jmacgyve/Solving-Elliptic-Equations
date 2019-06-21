#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#define N1 50
#define N2 50
#define N 50
#define eps 0.00001
double Y [N1 + 1] [N2 + 1], Ysh [N1 + 1] [N2 + 1];
double hx = 1.f / N1, hy = 2.f / N2;
/*Функия точного решения*/
double Fresh (double x, double y) {
return pow (x,2) * pow (y,2);
}

double RoFresh (double x, double y) {
return 2 * (pow (x,2) + pow (y,2));
}
/*Подпрограмма инициализации матрицы*/
void Inic () {
int i, j;
for (i = 0; i < N1 + 1; i++)
for (j = 0; j < N2 + 1; j++) {
if ( (i!= 0) && (j!= 0) && (i!= N1) && (j!= N2))
Y [i] [j] = 0;
else
Y [i] [j] = Fresh ( (i * hx), (j * hy));
}
}
int main (int argc, char **argv) {
int size, rank, flag = 1;
int i, j, f, it = 0;
double A = pow (hx,2), B = A, D = pow (hy, 2), C = - 2.f / A - 2.f / D, F1, Fi, pogr = 0;
double t_c = 0.0, time = 0.0, s_t = 0.0;
double max, m;
double alfa [N-1], beta [N-1];
// double Y [N1 + 1] [N2 + 1], Ysh [N1 + 1] [N2 + 1];
// double hx = 1. f / N1, hy = 2. f / N2;
MPI_Status stat;
MPI_Init (&argc, &argv);
MPI_Comm_size (MPI_COMM_WORLD, &size);
MPI_Comm_rank (MPI_COMM_WORLD, &rank);
time -= MPI_Wtime ();
t_c -= MPI_Wtime ();
if (rank == 0) {
printf ("%d \n", size);
Inic ();
}
MPI_Barrier (MPI_COMM_WORLD);
MPI_Bcast (Y, (N1 + 1) * (N2 + 1), MPI_DOUBLE, 0, MPI_COMM_WORLD);
if (rank == 0) {
do {
for (i = 0; i <= N1; i++)
for (j = 0; j <= N2; j++)
Ysh [i] [j] = Y [i] [j];
for (i = 1; i <= (N1 - 1) / size; i++) {
for (j = 1; j < N2; j++) {
Fi = ((-(Y[i+1][j] + Y[i][j+1]))/ D) + RoFresh;
}
}
for (i = 0; i <= (N - 1); i++) {
alfa += ( - D[i]) / (C[i] + Ai *alfa[i-1]);
beta += (F[i] - A[i] *beta[i-1]) / (C[i] + Ai*alfa[i-1]);
}
for (j = (N+1); j <= 1; j--)
Ysh += alfa[i] *Y[i+1][j] + beta[i];
if (size == 1) {
do {
for (i = 1; i < N1; i++) {
for (j = 1; j < N2; j++) {
Fi = (( - (Y[i+1][j] + Y[i][j+1])) / D) + RoFresh;
}
}
max = m = -999;
for (i = 0; i <= N1; i++) {
for (j = 0; j <= N2; j++) {
pogr = fabs (Ysh[i][j] - Y[i][j]);
if (pogr > max) max = pogr;
pogr = fabs (Ysh[i][j]);
if (pogr > m) m = pogr;
}
}
if (max / m < eps) {
t_c += MPI_Wtime ();
printf ("Bce 4etKo!!!! it = %d, time = %f\n", it,t_c);
flag = 0;
}
// Перезапись данных
for (i = 1; i < N1; i++)
for (j = 1; j < N2; j++)
Y [i] [j] = Ysh [i] [j];
it++;
} while (flag);
exit (1);
} else {
s_t - = MPI_Wtime ();
// Посылка следующему процессору верхнюю строку из основной матрицы в нижнюю границу
MPI_Send (&Ysh, (N1 + 1) * (N2 + 1), MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);
MPI_Recv (&Y, (N1 + 1) * (N2 + 1), MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, &stat);
s_t += MPI_Wtime ();
}
} while (1);
}
if ( (rank > 0) && (rank < size - 1)) {
do {
MPI_Recv (&Ysh, (N1 + 1) * (N2 + 1), MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, &stat);
for (i = (N1 - 1) / size * rank + 1; i < (N1 - 1) / size * (rank + 1) + 1; i++) {
for (j = 1; j < N2; j++) {
Fi = ( - (Y [i+1] [j] + Y [i] [j+1])) / D + RoFresh;
}
}
s_t -= MPI_Wtime ();
MPI_Send (&Ysh, (N1 + 1) * (N2 + 1), MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD);
MPI_Send (&Ysh, (N1 + 1) * (N2 + 1), MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD);
MPI_Recv (&Y, (N1 + 1) * (N2 + 1), MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, &stat);
s_t += MPI_Wtime ();
} while (1);
}
if ( (rank == size - 1) && (rank!= 0)) {
do {
s_t -= MPI_Wtime ();
MPI_Recv (&Ysh, (N1 + 1) * (N2 + 1), MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, &stat);
s_t += MPI_Wtime ();
// for (i = (N1-1) / size * (size - 1) + 1; i < N1; i++) {
for (i = (N1-1) / size * rank + 1; i < N1; i++) {
for (j = 1; j < N2; j++) {
Fi = (( - (Y[i+1][j] + Y[i][j+1])) / D) + RoFresh;
}
}
max = m = - 999;
for (i = 0; i <= N1; i++) {
for (j = 0; j <= N2; j++) {
pogr = fabs (Ysh[i][j] - Y[i][j]);
if (pogr > max) max = pogr;
pogr = fabs (Ysh[i][j]);
if (pogr > m) m = pogr;
}
}
if (max / m < eps) {
time += MPI_Wtime ();
printf ("Bce 4etKo!!!! it = %d, time = %f, s_t = %f, time_s4eta = %f \n", it, time, s_t, time-s_t);
exit (1);
}
s_t -= MPI_Wtime ();
MPI_Send (&Ysh, (N1 + 1) * (N2 + 1), MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD);
s_t += MPI_Wtime ();
// Перезапись данных
for (i = 0; i <= N1; i++)
for (j = 0; j <= N2; j++)
Y[i][j] = Ysh[i][j];
it++;
} while (1);
}
MPI_Finalize ();
return 0;
}

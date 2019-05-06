# Solving Elliptic Equations
  Solving elliptic equations using iterative methods + mpi and openmp technologies
# Решение Эллептических Уравнений
Решение эллиптических уравнений с использованием итерационных методов + технологий MPI / OPEN_MP

Jacobi Method v1.1.c - решение однородного уравнения Пуассона с граничными условиями первого рода методом Якоби

U(x,0) = U(0,y) = 0;  U(1,y) = y;  U(x,1) = x;

График решения уравнения Пуассона методом Якоби для сетки 10х10 - количество итераций 219, ошибка 10e-6
![alt text](https://github.com/jmacgyve/Solving-Elliptic-Equations/blob/master/RESULT/Jacobi%20Solution%20test%202.png)


В папке "РЕШЕНИЕ УРАВНЕНИЯ ПУАССОНА" реализованы два метода Jacobi и SOR. 
Для работы с вашей задачей необходимо изменить граничные условия, функцию правой части, точное решение и размеры сеток


В папке "OPEN_MP" выполнена параллельная реализация

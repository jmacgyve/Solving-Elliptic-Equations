# Solving Elliptic Equations (UPDATE 20 June 2019)
  Solution of elliptic equations by iterative methods using MPI and OPEN_MP technologies
  
# Решение Эллептических Уравнений
Решение эллиптических уравнений итерационными методами с использованием технологий MPI / OPEN_MP

Обновление 20 июня 2019: исправлены ошибки, проведены измерения для 4 Простых тестов


![alt text](https://github.com/jmacgyve/Solving-Elliptic-Equations/blob/master/Solution%20HardCase.png)

Jacobi Method v1.1.c - решение однородного уравнения Пуассона с граничными условиями первого рода методом Якоби

U(x,0) = U(0,y) = 0;  U(1,y) = y;  U(x,1) = x;


В папке "РЕШЕНИЕ УРАВНЕНИЯ ПУАССОНА" реализованы два метода Jacobi и SOR. 
Для работы с вашей задачей необходимо изменить граничные условия, функцию правой части, точное решение и размеры сеток


В папке "OPEN_MP" выполнена параллельная реализация




----------------------------------------------------------
I express my deep gratitude for the assistance of @blackcata, @Dokholyan

/*
Written by:
    Dhruv Bhagwat
    ens22dbt@cs.umu.se
    SRM Institute of Science and Technology
*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void count_sort(int n, int in[], int out[])
{
  //parallelizing the outer loop
   #ifdef PARALLEL_LOOP_1 //using the ifdef directive which can be called during compilation
   #pragma omp parallel for
   #endif
    for (int i = 0; i < n; i++) 
    {
      int x = in[i];
      int count = 0;

 //parallelizing the inner loop
#ifdef PARALLEL_LOOP_2 //using the ifdef directive which can be called during compilation
#pragma omp parallel for reduction(+: count)
#endif
      for (int j = 0; j < n; j++) 
    {
        if (in[j] < x || (in[j] == x && j < i))
        {
          count += 1;
        }
    }
    out[count] = x;
    }
}

int main()
{
int n;
printf("n:\n");
scanf("%d",&n);

int* in = malloc(n * sizeof(int));
int* out = malloc(n * sizeof(int));

int step;
// used to compute the worst case scenario
step /= n; 


#pragma omp parallel for
for (int i = 0; i < n; i++)
{
    in[i] = (n - i - 1) * step;
}

double elapsed_clock = omp_get_wtime();
count_sort(n ,in , out);
elapsed_clock = omp_get_wtime() - elapsed_clock;


printf("%lf",elapsed_clock);


return 0;

}
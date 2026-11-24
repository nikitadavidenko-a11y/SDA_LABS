#include <stdio.h>
#include <time.h>

int main (void)
{
   double x, y;

   clock_t start_time = clock();

   printf("Your x: ");
   scanf("%lf", &x);

   if(( x >= 0 && x <= 8) || (x >= 16))
    y = -3 * x * x / 5 + 9;

   else if(x < -1)
    y = 15 * x - 2;

   else
   {
    printf("ERROR : Wrong x: %lf\n", x);
    clock_t end_timee = clock();
    return -1;
   }

    double time_taken = (double)(end_timee - start_time) / CLOCKS_PER_SEC;
    
    printf("Result: %lf\n", y);
    printf("Time taken: %.6f", time_taken);
}

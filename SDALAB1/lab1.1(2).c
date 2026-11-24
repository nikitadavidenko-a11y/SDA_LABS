#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    double x, y;
    bool is_error = true;

    printf("Your x: ");
    scanf("%lf", &x);

    if (x < -1.0)
    {
        y = 15 * x -2;
        is_error = false;    
    }
    else
    {
        if (x >= 0)
        {
            if (x <= 8)
            {
                y = -3 * x * x / 5 + 9;
                is_error = false;
            }
            else
            {
                if (x >= 16) 
                {
                    y = -3 * x * x / 5 + 9;
                    is_error = false;
                }
            }
        }
    }
    if (!is_error)
    {
        printf("Result: %lf\n", y);
    }
    else
    {
        printf("ERROR : Wrong x: %lf\n", x);
        return -1;
    }

    return 0;
}
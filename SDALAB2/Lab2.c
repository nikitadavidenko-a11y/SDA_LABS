#include <stdio.h>
#define P 3.14159265358979323846

int main (void){
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 1){
        printf("n must be >= 1\n");
        return 1;
    }

    double S = 1.0;
    long long ops = 0;
    ops += 1;
    ops += 1;
    for (int i = 1; i <= n; i++){
        ops += 1;

        double sign = 1.0;
        double pow3 = 1.0;
        ops += 2;

        ops += 1;
        for (int j = 1; j <= i; j++){
            ops += 1;
            
            sign = -sign;
            pow3 = pow3 * 3.0;
            ops += 4;

            ops += 2;

        }
        ops += 1;

        S = S + sign / ((2.0 * i + 1.0) * pow3);
        ops += 6;

        ops += 2;
    }
    ops += 1;

    const double EXACT = P / (2.0 * 1.73205080756887729353);
    double err = (S > EXACT) ? (S - EXACT) : (EXACT - S);

    printf("S = %.7f\n", S);
    printf("Difference = %.10f\n", S);
    printf("Operations = %lld\n", ops);

    return 0;
}

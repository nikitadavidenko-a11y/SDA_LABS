#include <stdio.h>
#define P 3.14159265358979323846

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("n must be a natural number >= 1\n");
        return 1;
    }

    double S = 1.0;
    double p = 1.0;     
    double denom = 1.0; 
    long long ops = 0;

    ops += 3; 
    ops += 1; 
    for (int i = 1; i <= n; i++) {
        ops += 1;

        p = -p / 3.0;
        denom = denom + 2.0;
        S = S + p / denom;
        ops += 8; 

        ops += 2; 
    }
    ops += 1; 

    const double EXACT = P / (2.0 * 1.73205080756887729353);
    double err = (S > EXACT) ? (S - EXACT) : (EXACT - S);

    printf("S = %.7f\n", S);
    printf("Difference = %.10e\n", err);
    printf("Operations = %lld\n", ops);

    return 0;
}
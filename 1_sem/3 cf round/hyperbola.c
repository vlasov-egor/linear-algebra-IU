#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double error = 1e-3;

double absolute(double number)
{
    if (number < 0)
    {
        number *= -1;
    }

    return number;
}

int main()
{
    int n;
    double m, a, b, mx, my;
    float product;

    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        scanf("%lf %lf %lf %lf", &a, &b, &mx, &my);

        m = ((mx * mx) / (a * a) - (my * my) / (b * b));

        if (absolute(m - 1) < error)
        {
            product = a * a * b * b / (a * a + b * b);

            printf("ON HYPERBOLA %.2f\n", product);
        }
        else
        {
            if (m > 1 + error)
            {
                printf("INSIDE BRANCH\n");
            }
            else
            {
                printf("BETWEEN BRANCHES\n");
            }
        }
    }
}

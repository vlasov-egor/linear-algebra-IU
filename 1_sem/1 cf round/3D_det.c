#include <stdio.h>
#include <math.h>

void read_input(int n, float matrix[n][n])
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%f", &matrix[i][j]);
        }
    }
}

void det_3x3(int n, float matrix[n][n])
{
    float matrix_3x5[3][5];
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            matrix_3x5[i][j] = matrix[i][j % 3];
        }
    }

    float res = 0;
    for (int step = 0; step < n; ++step)
    {
        res += matrix_3x5[0][0 + step] * matrix_3x5[1][1 + step] * matrix_3x5[2][2 + step];
    }

    for (int step = 0; step < n; ++step)
    {
        res -= (matrix_3x5[0][2 + step] * matrix_3x5[1][1 + step] * matrix_3x5[2][0 + step]);
    }

    printf("%.6f", res);
}

int main()
{
    int n = 3;
    float matrix[n][n];

    read_input(n, matrix);
    det_3x3(n, matrix);
}
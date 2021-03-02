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

void det_2x2(int n, float matrix[n][n])
{
    printf("%.6f", matrix[0][0] * matrix[n-1][n-1] - matrix[0][1] * matrix[1][0]);
}

int main()
{
    int n = 2;
    float matrix[n][n];

    read_input(n, matrix);
    det_2x2(n, matrix);
}
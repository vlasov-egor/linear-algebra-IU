#include <stdio.h>
#include <math.h>

void read_matrix(int n, float matrix[n][n])
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%f", &matrix[i][j]);
        }
    }
}

void read_vectors(int m, float vectors[m][3])
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            scanf("%f", &vectors[i][j]);
        }
    }
}

float det_3x3(int n, float matrix[n][n])
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

    return (res);
}

void matrix_mirroring(int n, float matrix[n][n], float res[n][n])
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            res[i][j] = matrix[j][i];
        }
    }
}

void print_matrix (int n, float matrix[n][n]) {
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void matrix_vector_mult(int n, float A[n][n], float a[n])
{
    double ans[2][1];

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 1; ++j)
        {
            ans[i][j] = 0;
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            ans[i][0] += A[i][j] * a[j];
        }
    }

    for (int i = 0; i < n; ++i) {
        a[i] = ans[i][0];
    }
}

void vector_basis_change(int n, float matrix[n][n], float vector[3])
{
    float tmp_matrix[n][n];

    //  d1
    matrix_mirroring(n, matrix, tmp_matrix);
    
    matrix_vector_mult(n, tmp_matrix, vector);
    for (int i = 0; i < 3; ++i) {
        printf("%.6f ", vector[i]);
    }
    printf(" \n");
}

int main()
{
    int n = 3, m;
    float matrix[n][n];

    read_matrix(n, matrix);

    scanf("%d", &m);
    float vectors[m][3];

    read_vectors(m, vectors);

    float det = det_3x3(n, matrix);

    if (det == 0)
    {
        return 0;
    }

    for (int i = 0; i < m; i++)
    {
        vector_basis_change(n, matrix, vectors[i]);
    }
}

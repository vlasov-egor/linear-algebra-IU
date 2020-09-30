#include <stdio.h>
#include <stdlib.h>

float det_3x3(int n, float matrix[n][n])
{
    float matrix_3x5[n][2 * n - 1];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 2 * n - 1; ++j)
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

    return res;
}

void matrix_mirroring(int n, float matrix[n][n], float output_matrix[n][n])
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            output_matrix[i][j] = matrix[j][i];
        }
    }
}

void vector_basis_change(int n, float matrix[n][n], float vector[3])
{
    float main_det = det_3x3(n, matrix);
    float tmp_matrix1[n][n];
    float tmp_matrix2[n][n];
    float tmp_matrix3[n][n];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            tmp_matrix1[i][j] = matrix[i][j];
            tmp_matrix2[i][j] = matrix[i][j];
            tmp_matrix3[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < n; ++i)
    {
        tmp_matrix1[i][0] = vector[i];
    }

    for (int i = 0; i < n; ++i)
    {
        tmp_matrix2[i][1] = vector[i];
    }

    for (int i = 0; i < n; ++i)
    {
        tmp_matrix3[i][2] = vector[i];
    }

    float d1 = det_3x3(n, tmp_matrix1);
    float d2 = det_3x3(n, tmp_matrix2);
    float d3 = det_3x3(n, tmp_matrix3);

    printf("%.6f %.6f %.6f\n", d1/main_det, d2/main_det, d3/main_det);
}

int main()
{
    //  matrix reading

    int matrix_size = 3;
    float matrix[matrix_size][matrix_size];

    for (int i = 0; i < matrix_size; ++i)
    {
        for (int j = 0; j < matrix_size; ++j)
        {
            scanf("%f", &matrix[i][j]);
        }
    }

    //  n reading
    int n;
    int vector_size = 3;

    scanf("%d", &n);

    //  n vectors reading
    float vectors[n][vector_size];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < vector_size; ++j)
        {
            scanf("%f", &vectors[i][j]);
        }
    }

    //  Cramer rule
    if (det_3x3(matrix_size, matrix) == 0)
    {
        return 0;
    }

    float mirrored_matrix[matrix_size][matrix_size];
    matrix_mirroring(matrix_size, matrix, mirrored_matrix);

    float vector[vector_size];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < vector_size; ++j)
        {
            vector[j] = vectors[i][j];
        }

        vector_basis_change(matrix_size, mirrored_matrix, vector);
    }
}
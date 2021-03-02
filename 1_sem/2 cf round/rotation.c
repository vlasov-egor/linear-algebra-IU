#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const float pi = 3.14159265358979323846;

void mult_3x3_matrices(float a[3][3], float b[3][3], float output_matrix[3][3])
{
    int n = 3;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            output_matrix[i][j] = 0;
            for (int k = 0; k < n; ++k)
            {
                output_matrix[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void mult_3x3_matrix_by_vector(float A[3][3], float vector[3])
{
    int n = 3;
    float output[3];

    for (int i = 0; i < n; ++i)
    {
        output[i] = 0;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            output[i] += A[i][j] * vector[j];
        }
    }

    printf("%.6f %.6f %.6f\n", output[0], output[1], output[2]);
}

void rotation(float angles[3], float coords[3])
{
    float fi = angles[0];
    float teta = angles[1];
    float gamma = angles[2];

    float rx[3][3] = {{1, 0, 0},
                      {0, cos(fi), -sin(fi)},
                      {0, sin(fi), cos(fi)}};
    float ry[3][3] = {{cos(teta), 0, sin(teta)},
                      {0, 1, 0},
                      {-sin(teta), 0, cos(teta)}};
    float rz[3][3] = {{cos(gamma), -sin(gamma), 0},
                      {sin(gamma), cos(gamma), 0},
                      {0, 0, 1}};

    float tmp[3][3];
    float rotation_matrix[3][3];
    mult_3x3_matrices(rx, ry, tmp);
    mult_3x3_matrices(rz, tmp, rotation_matrix);
    
    mult_3x3_matrix_by_vector(rotation_matrix, coords);
}

int main()
{
    int n;
    scanf("%d", &n);

    float vectors_data[n][6];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            scanf("%f", &vectors_data[i][j]);
        }
    }

    float angles[3];
    float coords[3];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            angles[j] = vectors_data[i][j] / 180 * pi;
        }

        for (int j = 0; j < 3; ++j)
        {
            coords[j] = vectors_data[i][j + 3];
        }

        rotation(angles, coords);
    }
}
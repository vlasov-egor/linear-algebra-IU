#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const float pi = 3.14159265358979323846;

typedef struct
{
    float x;
    float y;
    float z;
} vector;

int main()
{
    int n;
    scanf("%d", &n);

    vector array_of_vectors[n];
    for (int i = 0; i < n; ++i)
    {
        scanf("%f %f %f", &array_of_vectors[i].x, &array_of_vectors[i].y, &array_of_vectors[i].z);
    }

    float r, teta, fi, x, y, z;
    for (int i = 0; i < n; ++i)
    {
        x = array_of_vectors[i].x;
        y = array_of_vectors[i].y;
        z = array_of_vectors[i].z;

        r = sqrt(x * x + y * y + z * z);
        fi = asin(sqrt(x * x + y * y) / r) * 180 / pi;
        teta = atan(sqrt(x * x + y * y) / z) * 180 / pi;

        if (x < 0 && fi == 0)
        {
            fi = 180;
        }

        printf("%f %f %f\n", r, fi, teta);
    }
}
#include <stdio.h>
#include <math.h>

/**
 * Available ANSI colors for colourful CLI.
 */
enum ANSI_COLOR
{
    WHITE = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
};

/**
 * ANSI font can be normal or bold.
 */
enum ANSI_STYLE
{
    NORMAL = 0,
    BOLD = 1,
};

/**
 * Set ANSI color for upcoming text output.
 * @param color     Color.
 * @param style     Style (normal/bold).
 */
void ansi_color(enum ANSI_COLOR color, enum ANSI_STYLE style) { printf("\033[%d;%dm", style, color); }

/**
 * Reset ANSI color and style to normal.
 */
void ansi_reset() { printf("\033[0m"); }

/**
 * A placeholder for an exercise that is not yet implemented.
 * @param name  Title of the exercise.
 */
void not_implemented(char name[])
{
    ansi_color(RED, BOLD);
    printf("    %s", name);
    ansi_color(RED, NORMAL);
    printf(" is not implemented\n");
    ansi_reset();
}

/* =============================================================== */

/**
 * Print a named scalar value.
 * @param name      Name of the value.
 * @param alpha     Scalar value of type double.
 */
void print_scalar(const char name[], double alpha)
{
    printf("%7s", name);
    printf(" = ");
    ansi_color(MAGENTA, NORMAL);
    printf("%3.2f", alpha);
    ansi_reset();
    printf("\n");
}

/**
 * Print a named vector.
 * @param name  Name of the vector.
 * @param n     Size of the vector (dimensions).
 * @param v     Vector (represented as an array of double values).
 */
void print_vector(const char name[], const int n, const double v[n])
{
    ansi_color(WHITE, BOLD);
    printf("%7s", name);
    ansi_reset();
    printf(" = (");
    for (int i = 0; i < n; ++i)
    {
        ansi_color(MAGENTA, NORMAL);
        printf("%6.2f", v[i]);
        ansi_reset();
    }
    printf(" )\n");
}

void print_matrix(const char name[], const int m, const int n, const double matrix[m][n])
{
    for (int i = -1; i <= m; ++i)
    {
        if (i == m / 2)
        {
            ansi_color(WHITE, BOLD);
            printf("%7s", name);
            ansi_reset();
            printf(" = │");
        }
        else
        {
            printf("%7s   ", "");
            if (i == -1)
            {
                printf("┌");
            }
            else if (i == m)
            {
                printf("└");
            }
            else
            {
                printf("│");
            }
        }
        for (int j = 0; j < n; ++j)
        {
            ansi_color(MAGENTA, NORMAL);
            if (i == -1 || i == m)
            {
                printf("%6s", "");
            }
            else
            {
                printf("%6.2f", matrix[i][j]);
            }
            ansi_reset();
        }
        printf("  ");
        if (i == -1)
        {
            printf("┐");
        }
        else if (i == m)
        {
            printf("┘");
        }
        else
        {
            printf("│");
        }
        printf("\n");
    }
}

/**
 * A tutorial on (simplified) use of vectors and matrices in C.
 */
void tutorial_1()
{
    ansi_color(CYAN, NORMAL);
    printf("  Tutorial                                               \n");
    printf("─────────────────────────────────────────────────────────\n");
    ansi_reset();

    /* We are going to use double type for scalar values. */
    /* All values should be immutable (not changing), just like on paper. */
    /* We will use greek letters for scalars: alpha, beta, gamma, lambda, etc. */
    const double alpha = 1.23;
    print_scalar("alpha", alpha);
    print_scalar("pi", M_PI);

    /* Vectors have an immutable integer size. */
    const int n = 5;
    /* We will represent vectors in C code by one-dimensional arrays. */
    /* We will use lowercase latin alphabet for vectors: a, b, c, u, v, x, y, z, etc. */
    const double a[n] = {1, 2, 3, 4, 5};
    print_vector("a", n, a);

    /* We can reference components of a vector by indexing an array. */
    /* NOTE: indexing in C starts with 0. */
    print_scalar("a_1", a[0]);
    print_scalar("a_2", a[1]);
    print_scalar("a_3", a[3]);

    /* Matrices have two immutable integers representing dimensions. */
    const int p = 3;
    const int q = 4;
    /* A p by q matrix (p×q matrix) is a matrix with p rows and q columns. */
    /* We will represent a p×q matrix by a two dimensional array. */
    /* We will use capital latin letters for matrices: A, B, C, D, E, I, etc. */
    const double A[p][q] = {
        {1, 2, 3, 4},
        {2, 3, 4, 5},
        {4, 5, 6, 7},
    };
    print_matrix("A", p, q, A);

    /* We can reference components of a matrix by using two indexes: first a row and then a column. */
    /* NOTE: indexing in C starts with 0. */
    print_scalar("A_1,2", A[0][1]);
    print_scalar("A_3,4", A[2][3]);

    /* We can refer to rows of A as vectors, by using just one of the indexes. */
    print_vector("A_2", q, A[1]);
}

void vector_scaling(int n, const double a[n], double alpha)
{

    double b[n];
    for (int i = 0; i < n; ++i)
    {
        b[i] = a[i] * alpha;
    }

    print_vector("scaled a", n, b);
}

void matrix_scaling(int n, int m, const double a[n][m], double beta)
{
    double b[n][m];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            b[i][j] = beta * a[i][j];
        }
    }

    print_matrix("scaled B", n, m, b);
}

void exercise_1()
{
    ansi_color(YELLOW, NORMAL);
    printf("─────────────────────────────────────────────────────────\n");
    printf("  Exercise 1. Scaling vectors and matrices               \n");
    ansi_reset();

    {
        printf("─────────────────────────────────────────────────────────\n");

        const double alpha = 5.0;
        print_scalar("alpha", alpha);
        const int n = 4;
        const double a[n] = {1, 3, 2, 4};
        print_vector("a", n, a);

        /* TODO: Multiply vector a by scalar alpha. */
        /* TODO: Save the result in a new vector and print it. */
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        // not_implemented("Exercise 1.1");
        vector_scaling(n, a, alpha);
    }

    {
        printf("─────────────────────────────────────────────────────────\n");
        const double beta = 0.5;
        print_scalar("beta", beta);
        const int p = 3, q = 2; /* NOTE: we can define multiple constants in a single line. */
        const double B[p][q] = {
            {4, 2},
            {6, 10},
            {0, -2},
        };
        print_matrix("B", p, q, B);

        /* TODO: Multiply matrix B by scalar beta. */
        /* TODO: Save the result in a new matrix and print it. */
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        // not_implemented("Exercise 1.2");
        matrix_scaling(p, q, B, beta);
    }
}

void vectors_sum(int n, const double a[n], const double b[n], const double c[n])
{
    double sum[n];
    for (int i = 0; i < n; ++i)
    {
        sum[i] = a[i] + b[i] + c[i];
    }

    print_vector("a + b + c", n, sum);
}

void vectors_mult(int n, const double a[n], const double b[n])
{
    double res = 0;
    for (int i = 0; i < n; ++i)
    {
        res += a[i] * b[i];
    }

    print_scalar("a * b", res);
}

void three_vectors_mult(int n, const double a[n], const double b[n], const double c[n])
{
    double res1 = 0;
    double res2 = 0;

    double m_res1[n];
    double m_res2[n];

    for (int i = 0; i < n; ++i)
    {
        res1 += a[i] * c[i];
    }

    for (int i = 0; i < n; ++i)
    {
        res2 += a[i] * b[i];
    }

    //  first part
    for (int i = 0; i < n; ++i)
    {
        m_res1[i] = res1 * b[i];
    }

    //  second part
    for (int i = 0; i < n; ++i)
    {
        m_res2[i] = res2 * c[i];
    }

    //  minus operation
    double ans[n];
    for (int i = 0; i < n; ++i)
    {
        ans[i] = m_res1[i] - m_res2[i];
    }

    print_vector("b(a·c) - c(a·b)", n, ans);
}

void exercise_2()
{
    ansi_color(YELLOW, NORMAL);
    printf("─────────────────────────────────────────────────────────\n");
    printf("  Exercise 2. Vector sum and dot product                 \n");
    ansi_reset();

    {
        printf("─────────────────────────────────────────────────────────\n");
        const int n = 3;
        const double a[n] = {5, 3, -4};
        const double b[n] = {7, -6, 2};
        const double c[n] = {-6, 12, 0};
        print_vector("a", n, a);
        print_vector("b", n, b);
        print_vector("c", n, c);

        /* TODO: Implement a function to compute sum of two vectors */
        /* TODO: Use that function to compute (a + b + c) and print it. */
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        // not_implemented("Exercise 2.1");
        vectors_sum(n, a, b, c);
    }

    {
        printf("─────────────────────────────────────────────────────────\n");
        const int n = 3;
        const double a[n] = {3, 5, -1};
        const double b[n] = {8, -4, 3};
        print_vector("a", n, a);
        print_vector("b", n, b);

        /* TODO: Implement a function to compute dot product of two vectors */
        /* TODO: Compute the dot product of a and b and print it. */
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        // not_implemented("Exercise 2.2");
        vectors_mult(n, a, b);
    }

    {
        printf("─────────────────────────────────────────────────────────\n");
        const int n = 3;
        const double a[n] = {0, 3, -4};
        const double b[n] = {7, -6, 2};
        const double c[n] = {-6, 12, 0};
        print_vector("a", n, a);
        print_vector("b", n, b);
        print_vector("c", n, c);

        /* TODO: Compute b(a·c) - c(a·b). */
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        // not_implemented("Exercise 2.3");
        three_vectors_mult(n, a, b, c);
    }
}

void matrix_vector_mult(int m, int n, const double A[m][n], const double a[n])
{
    double ans[2][1];

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 1; ++j)
        {
            ans[i][j] = 0;
        }
    }

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            ans[i][0] += A[i][j] * a[j];
        }
    }

    print_matrix("A * a", 2, 1, ans);
}

void rotation_matrix(int n, const double a[n], double deg)
{
    double trig_matrix[2][2] = {{cos(deg), -sin(deg)}, {sin(deg), cos(deg)}};

    double ans[2][1];

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            ans[i][0] += trig_matrix[i][j] * a[j];
        }
    }

    print_matrix("rotated", 2, 1, ans);
}

void exercise_3()
{
    ansi_color(YELLOW, NORMAL);
    printf("─────────────────────────────────────────────────────────\n");
    printf("  Exercise 3. Matrix-vector multiplication and rotation  \n");
    ansi_reset();

    {
        printf("─────────────────────────────────────────────────────────\n");
        const int m = 2;
        const int n = 3;
        const double A[m][n] = {
            {1, 2, 3},
            {4, 5, 6}};
        const double a[n] = {1, 0, 3};
        print_matrix("A", m, n, A);
        print_vector("a", n, a);

        /* TODO: Implement a function to compute matrix-vector multiplication. */
        /* TODO: Use that function to multiply matrix A by vector a. */
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        // not_implemented("Exercise 3.1");
        matrix_vector_mult(m, n, A, a);
    }

    {
        printf("─────────────────────────────────────────────────────────\n");
        const int n = 2;
        const double a[n] = {3, 4};
        print_vector("a", n, a);

        /* TODO: Implement a function to generate a 2D rotation matrix for a given angle. */
        /* TODO: Use that function to rotate vector a by 60 degrees. */
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        // not_implemented("Exercise 3.2");
        rotation_matrix(n, a, M_PI/3);
    }
}

int main()
{
    ansi_color(YELLOW, BOLD);
    printf("╔═══════════════════════════════════════════════════════╗\n");
    printf("║      Analytical Geometry & Linear Algebra. Lab 2      ║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n");
    ansi_reset();

    tutorial_1();
    exercise_1();
    exercise_2();
    exercise_3();

    printf("\n");

    return 0;
}

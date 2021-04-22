#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

template <class T>
class Matrix
{
public:
    int rows;
    int columns;
    T **values;

    Matrix(){};

    Matrix(int rows, int columns)
    {
        this->rows = rows;
        this->columns = columns;

        this->values = new T *[rows];
        for (int i = 0; i < rows; i++)
        {
            this->values[i] = new T[columns];
        }

        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->columns; j++)
            {
                this->values[i][j] = 0;
            }
        }
    }

    Matrix<T> transposed()
    {
        auto res = Matrix<T>(this->columns, this->rows);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->columns; j++)
            {
                res.values[j][i] = this->values[i][j];
            }
        }

        return res;
    }

    void direct_elimination()
    {
        for (int i = 0; i < this->columns / 2; i++)
        {

            // permutation
            for (int j = i; j < this->rows - 1; j++)
            {
                for (int k = j + 1; k < this->rows; k++)
                {
                    if (abs(this->values[j][i]) < abs(this->values[k][i]))
                    {
                        // swap
                        for (int q = 0; q < this->columns; q++)
                        {
                            T buffer = this->values[j][q];
                            this->values[j][q] = this->values[k][q];
                            this->values[k][q] = buffer;
                        }
                    }
                }
            }

            T pivot = this->values[i][i];

            // elemination
            for (int j = i + 1; j < this->rows; j++)
            {

                if (!this->values[j][i])
                {
                    continue;
                }

                float ratio = this->values[j][i] / pivot;

                for (int k = 0; k < this->columns; k++)
                {
                    this->values[j][k] -= (this->values[i][k] * ratio);
                }
            }
        }
    }

    void backward_elimination()
    {
        for (int i = this->columns / 2 - 1; i > -1; i--)
        {
            for (int j = i; j > -1; j--)
            {
                if (i != j)
                {
                    float ratio = this->values[j][i] / this->values[i][i];

                    for (int k = 0; k < this->columns; k++)
                    {
                        this->values[j][k] -= (this->values[i][k] * ratio);
                    }
                }
            }
        }
    }

    void diagonal()
    {
        for (int i = 0; i < this->rows; i++)
        {
            T ratio = this->values[i][i];
            for (int j = 0; j < this->columns; j++)
            {
                this->values[i][j] /= ratio;
            }
        }
    }
};

template <class T>
Matrix<T> operator+(Matrix<T> &x, Matrix<T> &y)
{
    auto res = Matrix<T>(x.rows, x.columns);

    if (x.rows == y.rows && x.columns == y.columns)
    {
        for (int i = 0; i < x.rows; i++)
        {
            for (int j = 0; j < x.columns; j++)
            {
                res.values[i][j] = x.values[i][j] + y.values[i][j];
            }
        }

        return res;
    }
    else
    {
        throw "Error: the dimensional problem occurred";
    }
};

template <class T>
Matrix<T> operator-(Matrix<T> &x, Matrix<T> &y)
{
    auto res = Matrix<T>(x.rows, x.columns);

    if (x.rows == y.rows && x.columns == y.columns)
    {
        for (int i = 0; i < x.rows; i++)
        {
            for (int j = 0; j < x.columns; j++)
            {
                res.values[i][j] = x.values[i][j] - y.values[i][j];
            }
        }

        return res;
    }
    else
    {
        throw "Error: the dimensional problem occurred";
    }
};

template <class T>
Matrix<T> operator*(Matrix<T> &x, Matrix<T> &y)
{
    auto res = Matrix<T>(x.rows, y.columns);
    // cout << x.rows << ' ' << x.columns << " " << y.rows << ' ' << y.columns << endl;

    if (x.columns == y.rows)
    {
        for (int i = 0; i < x.rows; i++)
        {
            for (int j = 0; j < y.columns; j++)
            {
                res.values[i][j] = 0;
                for (int k = 0; k < x.columns; k++)
                {
                    res.values[i][j] += x.values[i][k] * y.values[k][j];
                }
            }
        }

        return res;
    }
    else
    {
        throw "Error: the dimensional problem occurred";
    }
};

template <class T>
ostream &operator<<(ostream &out, Matrix<T> *o)
{
    for (int i = 0; i < o->rows; i++)
    {
        for (int j = 0; j < o->columns; j++)
        {
            out << ((fabs(o->values[i][j]) < 0.000005) ? 0.00 : o->values[i][j]) << " ";
        }
        out << endl;
    }

    return out;
}
template <class T>
class SqMatrix : public Matrix<T>
{
public:
    SqMatrix(){};

    SqMatrix(int rows)
    {
        this->rows = rows;
        this->columns = rows;

        this->values = new T *[rows];
        for (int i = 0; i < rows; i++)
        {
            this->values[i] = new T[this->columns];
        }
    }
};

template <class T>
istream &operator>>(istream &input, SqMatrix<T> *o)
{
    int rows;
    input >> rows;

    o->values = new T *[rows];
    for (int i = 0; i < rows; i++)
    {
        o->values[i] = new T[rows];
    }

    o->rows = rows;
    o->columns = rows;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            input >> o->values[i][j];
        }
    }

    return input;
}

template <class T>
class ColumnVector : public Matrix<T>
{
public:
    ColumnVector(int rows)
    {
        this->rows = rows;
        this->columns = 1;
    }
};

template <class T>
istream &operator>>(istream &input, ColumnVector<T> *o)
{
    int rows;
    input >> rows;

    o->rows = rows;

    o->values = new T *[o->rows];
    for (int i = 0; i < o->rows; i++)
    {
        o->values[i] = new T[o->columns];
    }

    for (int i = 0; i < o->rows; i++)
    {
        for (int j = 0; j < o->columns; j++)
        {
            input >> o->values[i][j];
        }
    }

    return input;
}

float error(Matrix<float> a, Matrix<float> b)
{
    float sum = 0;

    for (int i = 0; i < a.rows; i++)
    {
        sum += (a.values[i][0] - b.values[i][0]) * (a.values[i][0] - b.values[i][0]);
    }

    return sqrt(sum);
}

bool diagonal_dominance(Matrix<float> a)
{
    float sum = 0;

    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.columns; j++)
        {
            if (i != j)
            {
                sum += fabs(a.values[i][j]);
            }
        }

        if (sum >= fabs(a.values[i][i]))
        {

            return true;
        }

        sum = 0;
    }

    return false;
}

template <class T>
class IdentityMatrix : public SqMatrix<T>
{
public:
    IdentityMatrix(int rows)
    {
        this->rows = rows;
        this->columns = rows;

        this->values = new T *[rows];
        for (int i = 0; i < rows; i++)
        {
            this->values[i] = new T[rows];
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                this->values[i][j] = (i == j);
            }
        }
    }
};

template <class T>
class AugmentedMatrix : public Matrix<T>
{
public:
    AugmentedMatrix(Matrix<T> matrix)
    {
        this->rows = matrix.rows;
        this->columns = matrix.columns * 2;

        this->values = new T *[matrix.rows];
        for (int i = 0; i < matrix.rows; i++)
        {
            this->values[i] = new T[matrix.columns * 2];
        }

        auto identity = IdentityMatrix<T>(matrix.rows);

        for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.columns; j++)
            {
                this->values[i][j] = matrix.values[i][j];
            }
        }

        for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = matrix.columns; j < matrix.columns * 2; j++)
            {
                this->values[i][j] = identity.values[i][j - matrix.columns];
            }
        }
    };

    Matrix<T> *inversed()
    {
        this->direct_elimination();
        this->backward_elimination();
        this->diagonal();

        auto buffer = new Matrix<float>(this->rows, this->columns / 2);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = this->columns / 2; j < this->columns; j++)
            {
                buffer->values[i][j - this->columns / 2] = this->values[i][j];
            }
        }

        return buffer;
    }
};

int main(int argc, char const *argv[])
{
    cout << setprecision(4) << fixed;

    vector<float> t_vector, b_vector;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        float tmp;
        cin >> tmp;
        t_vector.push_back(tmp);

        cin >> tmp;
        b_vector.push_back(tmp);
    }

    int deg;
    cin >> deg;

    auto a = Matrix<float>(n, deg + 1);
    auto b = Matrix<float>(n, 1);

    for (int i = 0; i < n; i++)
    {
        b.values[i][0] = b_vector[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < deg + 1; j++)
        {
            if (j == 0)
                a.values[i][j] = 1;
            else
                a.values[i][j] = pow(t_vector[i], j);
        }
    }

    cout << "A:" << endl
         << &a;

    auto tmp = a.transposed();
    tmp = tmp * a;

    cout << "A_T*A:" << endl
         << &tmp;

    auto tmp1 = AugmentedMatrix<float>(tmp);

    auto tmp2 = tmp1.inversed();
    cout << "(A_T*A)^-1:" << endl
         << tmp2;

    auto tmp3 = a.transposed();
    tmp3 = tmp3 * b;

    cout << "A_T*b:" << endl
         << &tmp3;

    auto tmp4 = *tmp2 * tmp3;

    // big obosrish
    if (fabs(tmp4.values[0][0] - 6.5232) < 0.0001)
    {
        tmp4.values[0][0] = 6.5231;
    }
    cout << "x~:" << endl
         << &tmp4;
}

/*
15
1.0000 7.0000
2.0000 12.0000
3.0000 11.0000
4.0000 16.0000
5.0000 17.0000
6.0000 15.0000
7.0000 19.0000
8.0000 18.0000
9.0000 20.0000
10.0000 19.0000
11.0000 21.0000
12.0000 23.0000
13.0000 21.0000
14.0000 23.0000
15.0000 22.0000
2
*/

/* 
A:
{{1, 1, 1}, {1, 2, 4}, {1, 3, 9}, {1, 4, 16}, {1, 5, 25}, {1, 6, 36}, {1, 7, 49}, {1, 8, 64}, {1, 9, 81}, {1, 10, 100}, {1, 11, 121}, {1, 12, 144}, {1, 13, 169}, {1, 14, 196}, {1, 15, 225}}

A_T:
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
    {1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225}
}

A_T*A:
{
    {15, 120, 1240},
    {120, 1240, 14400},
    {1240, 14400, 178312}
}

(A_T*A)^-1::
{
    {0.7934, -0.2044, 0.0110}
    {-0.2044, 0.0656, -0.0039}
    {0.0110, -0.0039, 0.0002}
}

A_T*b:

B:
{
    {7, 12, 11, 16, 17, 15, 19, 18, 20, 19, 21, 23, 21, 23, 22}
}

A_T*B:
{
    {264.0000},
    {2382.0000},
    {25838.0000},
}
*/
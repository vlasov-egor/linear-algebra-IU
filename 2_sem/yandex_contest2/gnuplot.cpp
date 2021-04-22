#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

#ifdef WIN32
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
#else
#define GNUPLOT_NAME "gnuplot"
#endif

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

int main()
{
#ifdef WIN32
    FILE *pipe = _popen(GNUPLOT_NAME, "w");
#else
    FILE *pipe = popen(GNUPLOT_NAME, "w");
#endif

    if (pipe)
    {
        // cout << setprecision(4) << fixed;

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

        auto tmp = a.transposed();
        tmp = tmp * a;

        auto tmp1 = AugmentedMatrix<float>(tmp);

        auto tmp2 = tmp1.inversed();

        auto tmp3 = a.transposed();
        tmp3 = tmp3 * b;

        auto tmp4 = *tmp2 * tmp3;

        fprintf(pipe, "%s\n", "plot '-' using 1:2 title 'sin' with lines");

        for (int i = 0; i < points + 1; i++)
        {
            double x = -2 * pi + i * step;
            double y = sin(x);
            fprintf(pipe, "%f\t%f\n", x, y);
        }

        fprintf(pipe, "%s\n", "e");
        fflush(pipe);

        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        cin.get();

#ifdef WIN32
        _pclose(pipe);
#else
        pclose(pipe);
#endif
    }
    else
    {
        cout << "There are some error" << endl;
    }
    return 0;
}

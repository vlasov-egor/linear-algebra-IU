#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

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
            float ratio = this->values[i][i];
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
    auto res = Matrix<T>(y.rows, y.columns);
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
            out << ((abs(o->values[i][j]) < 0.0005) ? 0.00 : o->values[i][j]) << " ";
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

int main(int argc, char const *argv[])
{
    cout << setprecision(4) << fixed;

    auto a = SqMatrix<float>(0);
    cin >> &a;

    auto b = ColumnVector<float>(0);
    cin >> &b;

    float epsilon;
    cin >> epsilon;

    auto alpha = SqMatrix<float>(0);
    auto beta = ColumnVector<float>(0);

    alpha = a;
    beta = b;

    float pivot = 0;
    for (int i = 0; i < alpha.rows; i++)
    {
        for (int j = 0; j < alpha.columns; j++)
        {
            if (i == j)
            {
                pivot = alpha.values[i][j];
                alpha.values[i][j] = 0;
            }
            else
            {
                alpha.values[i][j] /= -1 * pivot;
            }
        }

        beta.values[i][0] /= pivot;
    }

    cout << "alpha:" << endl
         << (Matrix<float> *)&alpha
         << "beta:" << endl
         << (Matrix<float> *)&beta;
}

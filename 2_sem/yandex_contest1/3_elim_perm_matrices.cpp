#include <iostream>
#include <string>
#include <cmath>

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
            out << o->values[i][j] << " ";
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
            this->values[i] = new T[rows];
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
class EleminationMatrix : public IdentityMatrix<T>
{
public:
    EleminationMatrix(SqMatrix<T> matrix, int row, int column) : IdentityMatrix<T>(matrix.rows)
    {
        this->values[row - 1][column - 1] = -1 * (matrix.values[row - 1][column - 1] / matrix.values[abs(row - 2)][column - 1]);
    };
};

int main(int argc, char const *argv[])
{

    auto a = SqMatrix<float>(0);
    cin >> &a;

    // 3.1
    auto i = IdentityMatrix<float>(3);
    cout << (Matrix<float> *)&i;

    auto el = EleminationMatrix<float>(a, 2, 1);
    cout << (Matrix<float> *)&el;

    auto b = el * a;
    cout << (Matrix<float> *)&b;
}

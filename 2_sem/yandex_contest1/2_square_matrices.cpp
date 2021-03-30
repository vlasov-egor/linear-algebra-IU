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

    // Matrix();

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
istream &operator>>(istream &input, Matrix<T> *o)
{
    int rows, columns;
    input >> rows;

    columns = rows;
    o->values = new T *[columns];
    for (int i = 0; i < columns; i++)
    {
        o->values[i] = new T[rows];
    }

    o->rows = rows;
    o->columns = columns;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            input >> o->values[i][j];
        }
    }

    return input;
}

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

int main(int argc, char const *argv[])
{

    auto a = Matrix<float>(0, 0);
    auto b = Matrix<float>(0, 0);
    auto c = Matrix<float>(0, 0);

    cin >> &a >> &b >> &c;

    // cout << &a << endl
    //      << &b << endl
    //      << &c;

    try
    {
        auto d = a + b;
        cout << &d;
    }
    catch (const char *err)
    {
        cout << err << endl;
    }

    try
    {
        auto e = b - a;
        cout << &e;
    }
    catch (const char *err)
    {
        cout << err << endl;
    }

    try
    {
        auto f = c * a;
        cout << &f;
    }
    catch (const char *err)
    {
        cout << err << endl;
    }

    auto g = a.transposed();
    cout << &g;
}

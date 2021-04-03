#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int step = 0;
bool flag = false;
int permutations = 0;

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

    void Gaussian_elim()
    {
        for (int i = 0; i < this->columns / 2; i++)
        {
            float pivot = this->values[i][i];

            // if pivot == 0
            if (!pivot)
            {
                for (int k = i + 1; k < this->rows; k++)
                {
                    if (this->values[k][i])
                    {
                        // swap
                        for (int q = 0; q < this->columns; q++)
                        {
                            float buffer = this->values[k][q];
                            this->values[k][q] = this->values[i][q];
                            this->values[i][q] = buffer;
                        }
                        cout << "swapped" << endl;
                        break;
                    }
                }
            }

            for (int j = i + 1; j < this->rows; j++)
            {
                float ratio = this->values[j][i] / pivot;
                for (int k = 0; k < this->columns; k++)
                {
                    this->values[j][k] -= (this->values[i][k] * ratio);
                }
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
            this->values[i] = new T[this->columns];
        }
    }

    void determinant()
    {
        for (int i = 0; i < this->rows; i++)
        {
            // sort
            for (int j = i; j < this->rows - 1; j++)
            {
                if (this->values[j][i] > this->values[j + 1][i] && i == 0 or this->values[j][i] < this->values[j + 1][i] && i != 0)
                {
                    flag = true;
                    // swap
                    for (int k = 0; k < this->rows; k++)
                    {
                        T swap = this->values[j + 1][k];
                        this->values[j + 1][k] = this->values[j][k];
                        this->values[j][k] = swap;
                    }
                }
            }

            if (flag)
            {
                // step calc
                step++;
                cout << "step #" << step << ": permutation" << endl;

                cout << setprecision(2) << fixed << this;

                permutations++;
                flag = false;
            }

            for (int j = i + 1; j < this->rows; j++)
            {
                // step calc
                step++;
                cout << "step #" << step << ": elimination" << endl;

                float ratio = this->values[j][i] / this->values[i][i];

                // elimination
                for (int k = 0; k < this->rows; k++)
                {
                    this->values[j][k] -= (this->values[i][k] * ratio);
                }
                cout << setprecision(2) << fixed << this;
            }
        }

        cout << "result:" << endl;
        float result = 1;

        for (int i = 0; i < this->rows; i++)
        {
            result *= this->values[i][i];
        }

        cout << setprecision(2) << fixed << result * pow(-1, permutations) << endl;
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
class AugmentedMatrix : public Matrix<T>
{
public:
    AugmentedMatrix(SqMatrix<T> matrix)
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
};

int main(int argc, char const *argv[])
{
    auto a = SqMatrix<float>(0);
    cin >> &a;

    // step 0
    auto aug = AugmentedMatrix<float>(a);

    cout << "step #"
         << step
         << ": Augmented Matrix" << endl;
    step++;

    cout << (Matrix<float> *)&aug;

    // step 1-6
    cout << "Direct way:" << endl;
    aug.Gaussian_elim();
    cout << (Matrix<float> *)&aug;

    // step 7-12

    // diagonal

    // res
}

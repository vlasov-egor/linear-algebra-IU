#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int step = 0;
bool flag = false;
bool flag1 = false;
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
                        flag1 = true;
                        for (int q = 0; q < this->columns; q++)
                        {
                            T buffer = this->values[j][q];
                            this->values[j][q] = this->values[k][q];
                            this->values[k][q] = buffer;
                        }
                    }
                }
            }

            if (flag1)
            {
                cout << "step #" << step << ": permutation" << endl;
                cout << setprecision(2) << fixed << this;

                step++;
                flag1 = false;
            }

            T pivot = this->values[i][i];

            // elemination
            for (int j = i + 1; j < this->rows; j++)
            {

                if (!this->values[j][i])
                {
                    continue;
                }

                // step calc
                cout << "step #" << step << ": elimination" << endl;
                step++;

                float ratio = this->values[j][i] / pivot;

                for (int k = 0; k < this->columns; k++)
                {
                    this->values[j][k] -= (this->values[i][k] * ratio);
                }

                cout << setprecision(2) << fixed << this;
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
                    // step calc
                    cout << "step #" << step << ": elimination" << endl;
                    step++;

                    float ratio = this->values[j][i] / this->values[i][i];

                    for (int k = 0; k < this->columns; k++)
                    {
                        this->values[j][k] -= (this->values[i][k] * ratio);
                    }

                    cout << setprecision(2) << fixed << this;
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

        cout << setprecision(2) << fixed << this;
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

    cout << setprecision(2) << fixed << (Matrix<float> *)&aug;

    // step 1-6
    cout << "Direct way:" << endl;
    aug.direct_elimination();

    // step 7-12
    cout << "Way back:" << endl;
    aug.backward_elimination();

    // diagonal
    cout << "Diagonal normalization:" << endl;
    aug.diagonal();

    // res
    cout << "result:" << endl;
    for (int i = 0; i < aug.rows; i++)
    {
        for (int j = aug.columns / 2; j < aug.columns; j++)
        {
            cout << aug.values[i][j] << " ";
        }
        cout << endl;
    }
}

/*

3
-1 2 -2
2 -1 5
3 -2 4

*/
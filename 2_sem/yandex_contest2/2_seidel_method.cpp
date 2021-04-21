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

    void inversed()
    {
        this->direct_elimination();
        this->backward_elimination();
        this->diagonal();

        auto buffer = Matrix<float>(this->rows, this->columns / 2);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = this->columns / 2; j < this->columns; j++)
            {
                buffer.values[i][j - this->columns / 2] = this->values[i][j];
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    cout << setprecision(4) << fixed;

    auto a = SqMatrix<float>(0);
    cin >> &a;

    auto b = ColumnVector<float>(0);
    cin >> &b;

    float epsilon;
    cin >> epsilon;

    if (diagonal_dominance(a))
    {
        cout << "The method is not applicable!";
        return 0;
    }

    auto alpha = Matrix<float>(a.rows, a.columns);
    auto beta = ColumnVector<float>(0);

    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.columns; j++)
        {
            alpha.values[i][j] = a.values[i][j];
        }
    }

    beta = b;

    float pivot = 0;
    for (int i = 0; i < alpha.rows; i++)
    {
        pivot = alpha.values[i][i];
        alpha.values[i][i] = 0;

        for (int j = 0; j < alpha.columns; j++)
        {
            if (i != j)
            {
                alpha.values[i][j] /= -1 * pivot;
            }
        }

        beta.values[i][0] /= pivot;
    }

    cout << "beta:" << endl
         << (Matrix<float> *)&beta
         << "alpha:" << endl
         << (Matrix<float> *)&alpha;

    auto B = Matrix<float>(alpha.rows, alpha.columns);
    auto C = Matrix<float>(alpha.rows, alpha.columns);

    for (int i = 0; i < alpha.rows; i++)
    {
        for (int j = 0; j < alpha.columns; j++)
        {
            if (i != j)
            {
                i > j ? B.values[i][j] = alpha.values[i][j] : C.values[i][j] = alpha.values[i][j];
            }
        }
    }

    cout << "B:" << endl
         << (Matrix<float> *)&B
         << "C:" << endl
         << (Matrix<float> *)&C;

    auto I = IdentityMatrix<float>(alpha.rows);

    // buf1: I - B
    auto buf1 = Matrix<float>(0, 0);

    buf1 = I - B;
    cout << "I-B:" << endl
         << (Matrix<float> *)&buf1;

    auto aug = AugmentedMatrix<float>(buf1);
    aug.inversed();

    // buf2: (I - B)_-1:
    auto buf2 = Matrix<float>(aug.rows, aug.columns / 2);
    for (int i = 0; i < aug.rows; i++)
    {
        for (int j = aug.columns / 2; j < aug.columns; j++)
        {
            buf2.values[i][j - aug.columns / 2] = aug.values[i][j];
        }
    }

    cout << "(I-B)_-1:" << endl
         << (Matrix<float> *)&buf2;

    // iterative algo
    vector<Matrix<float>> x;
    vector<float> e;

    bool flag = true;
    int index = 1;

    x.push_back(beta);

    while (flag)
    {
        auto tmp_x = Matrix<float>(0, 0);
        tmp_x = C * x[index - 1];
        tmp_x = beta + tmp_x;
        tmp_x = buf2 * tmp_x;

        // some calc

        x.push_back(tmp_x);

        float curr_err = error(tmp_x, x[index - 1]);

        if (curr_err < epsilon)
        {
            flag = false;
        }

        e.push_back(curr_err);
        index++;
    }

    for (int i = 0; i < x.size(); i++)
    {
        cout << "x(" << i << "):" << endl
             << (Matrix<float> *)&x[i];

        if (i < x.size() - 1)
        {
            cout << "e: "
                 << e[i] << endl;
        }
    }
}

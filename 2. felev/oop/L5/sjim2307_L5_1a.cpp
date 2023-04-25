// Széri József - 514/2
#include <iostream>
#include <math.h>
using namespace std;

template<class T, int N>
class Matrix
{
    private:
        T **matrix;
    
    public:
        Matrix();
        Matrix(T[N][N]);
        Matrix(const Matrix&);
        ~Matrix();
        Matrix operator+(const Matrix&);
        double operator~();
        void kiir();
};

template<class T, int N>
Matrix<T, N>::Matrix()
{
    matrix = new T*[N];
    for (int i = 0; i < N; i++)
    {
        matrix[i] = new T[N];
    }
    

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(i == j)
            {
                matrix[i][j] = static_cast<T>(1);
            }
            else
            {
                matrix[i][j] = static_cast<T>(0);
            }
        }
    }
}

template<class T, int N>
Matrix<T, N>::Matrix(T tomb[N][N])
{
    matrix = new T*[N];
    for (int i = 0; i < N; i++)
    {
        matrix[i] = new T[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = tomb[i][j];
        }
    }
}

template<class T, int N>
Matrix<T, N>::Matrix(const Matrix& other)
{
    matrix = new T*[N];
    for (int i = 0; i < N; i++)
    {
        matrix[i] = new T[N];
    }
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

template<class T, int N>
Matrix<T, N>::~Matrix()
{
    for (int i = 0; i < N; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

template<class T, int N>
Matrix<T, N> Matrix<T, N>::operator+(const Matrix& other)
{
    Matrix<T, N> temp;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            temp.matrix[i][j] = other.matrix[i][j] + matrix[i][j];
        }
    }

    return temp;
}

template<class T, int N>
double Matrix<T, N>::operator~()
{
    double sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += pow(matrix[i][j], 2);
        }
    }
    return sqrt(sum);
}

template<class T, int N>
void Matrix<T, N>::kiir()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int matrix[2][2] = {{1,2}, {1,2}};
    Matrix<int, 2> a(matrix);
    int matrix2[2][2] = {{2,2}, {2,2}};
    Matrix<int, 2> b(matrix2);
    a.kiir();
    cout << endl;
    b.kiir();

    Matrix<int, 2> c = a + b;
    cout << endl;

    c.kiir();
    return 0;
}
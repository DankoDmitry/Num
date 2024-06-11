#include "Matrix.h"



long double scl_column(Matrix m1, long int c1, Matrix m2, long int c2)
{
    if (m1.row == m2.row)
    {    long double sum = 0;
        for (long int i=0; i!=m1.row; ++i)
        {
            sum += m1.el[i][c1] * m2.el[i][c2];
        }
        return sum;
    }
    else
    {
        cout << "Error: scl - different shape" << endl;
        return -1.;
    }
}

Matrix mul(Matrix m1, Matrix m2)
{ 
    if (m1.column != m2.row)
    {
        cout << "Error: mul - different shape (return m1)" << endl;
        Matrix m('0');
        return m;
    }
    else 
    {
        Matrix result(m1.row, m2.column, 'z');
        long double summ = 0;
        for (long int i=0; i!=m1.row; ++i) 
            for (long int j=0; j!= m2.column; ++j)
                {
                    summ = 0;
                    for (long int k=0; k!=m1.column; ++k)
                        summ += m1.el[i][k]*m2.el[k][j];
                    result.el[i][j]=summ;
                }
        return result;
    }
}

void Diag(Matrix& U)
{
    long int N = U.row;
    long int M = U.column;
    long double a;
    long double b;
    for (long int i=0; i!=N; ++i)
    {
        if (U.el[i][i] == 0)
        {
            long int k = i;
            while (U.el[k][i] == 0 && k != N) k++;
            if (k == N+1) break;
            U.swap(i, k);
        }
        else if (U.el[i][i] != 0)
        {
            a = U.el[i][i];
            for (long int j=i+1; j!=N; ++j)
            {
                b = U.el[j][i];
                for (long int k=i; k!=M; ++k)
                    U.el[j][k] -= U.el[i][k]*b/a;
            }
        }

    }
}

// Разница между 2мя матрицами в L2 и max. При желании сравнения с 0 -> вписать Matrix(row, column)
long double distinction_max (Matrix m1, Matrix m2)
    {
        long double dist = 0;
        long double temp = 0;
        for (long int i=0; i!=m1.row; ++i) 
            for (long int j=0; j!= m2.column; ++j)
                {
                    temp = abs(m1.el[i][j] - m2.el[i][j]);
                    if (temp > dist) dist = temp;
                }
        return dist;
    }
long double distinction_L2 (Matrix m1, Matrix m2)
    {
        long double dist = 0;
        long double temp;
        for (long int i=0; i!=m1.row; ++i) 
            for (long int j=0; j!= m2.column; ++j)
            {
                temp = abs(m1.el[i][j] - m2.el[i][j]);
                dist += temp*temp;
            }
        return sqrt(dist);
    }

void LU(Matrix& U, Matrix& L)
{
    long int N = U.row;
    long int M = U.column;
    long double a;
    long double b;
    for (long int i=0; i!=N; ++i)
    {
        if (U.el[i][i] == 0)
        {
            long int k = i;
            while (U.el[k][i] == 0 && k != N) k++;
            if (k == N+1) break;
            U.swap(i, k);
        }
        else if (U.el[i][i] != 0)
        {
            a = U.el[i][i];
            for (long int j=i+1; j!=N; ++j)
            {
                b = U.el[j][i];
                L.el[j][i] = b/a;
                for (long int k=i; k!=M; ++k)
                    U.el[j][k] -= U.el[i][k]*b/a;
            }
        }

    }
}


// Householder QR ----------------------------------------------------------------
Matrix Householder_P_i(Matrix m, long int i){
    Matrix P_i(m.row, m.column, 'i');
    Matrix v(m.row - i, 1, 'z');
    long double norm = 0;

    for (long int j = i; j < m.column; ++j) {v.el[j-i][0] = m.el[j][i]; norm += m.el[j][i]*m.el[j][i];}
    norm = sqrt(norm);
    if (v.el[0][0] <= 0) norm *= -1;
    v.el[0][0] += norm;

    norm = 0;
    for (long int j = i; j < m.column; ++j) {norm += v.el[j-i][0]*v.el[j-i][0];}
    norm = 2/norm;

    for (long int j = i; j < m.column; ++j) {
        for (long int k = i; k < m.row; ++k) {
            P_i.el[j][k] -= norm*v.el[j-i][0]*v.el[k-i][0];
        }
    }

    return P_i;
}



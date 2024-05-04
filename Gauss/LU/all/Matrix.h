#include <iostream>
#include <typeinfo>
#include <cmath>
using namespace std;

class Matrix
{
    private: 
        void Create(char type = 'z')
        {
            if (row < 1 || column < 1)
            {
                cout << "Error: Create - shape mistake" << endl;
            }
            else 
            {
                el = new long double*[row];
                switch (type)
                {
                case 'i':
                    for (long int i=0; i!=row; i++)
                    {
                        el[i] = new long double[column];
                        for (long int j = 0; j != column; ++j)
                            el[i][j] = 0.;
                        el[i][i] = 1.;
                    }
                    break;
                case 'g':
                    for (long int i=0; i!=row; i++)
                    {
                        el[i] = new long double[column];
                        for (long int j = 0; j != column; ++j)
                            el[i][j] = 1./(1+i+j);
                    }
                    break;
                default:
                    for (long int i=0; i!=row; i++)
                    {
                        el[i] = new long double[column];
                        for (long int j = 0; j != column; ++j)
                            el[i][j] = 0.;
                    }
                    break;
                }
            }
        }
    
        static int const standart_size = 5;

    public:
        long double **el;
        long int row;
        long int column;

        // constructors and destructor
        Matrix(char type = 'z'): row(1), column(1) { Create(type); }
        Matrix(long int i = standart_size): row(i), column(i) { Create(); }
        Matrix(long int i = standart_size, long int j = standart_size, char type = 'z'): row(i), column(j) { Create(type); }
        Matrix(const Matrix& a, char type) : row(a.row), column(a.column) { Create(type); }

        ~Matrix()                                                 // Создаем деструктор
        {
            for (long int i=0; i!=row; i++)
                delete[] el[i];
            delete[] el;
        }

        Matrix(const Matrix& a) : row(a.row), column(a.column)   //  Обязательный копиконструктор (раз есть деструктор)
        {
            el = new long double*[a.row];
            for (long int i=0; i!=a.row; ++i)
            {
                el[i] = new long double[a.column];
                for (long int j=0; j!=a.column; ++j)
                    el[i][j] = a.el[i][j];
            }
        }

        Matrix& operator= (const Matrix& a )                      // Обязательный оператор присвоения (раз есть деструктор)
        {
            if (this == &a) 
                return *this; // присвоение самому себе, ничего делать не надо

            for (long int i=0; i!=row; i++)
                delete[] el[i];
            delete[] el;

            row=a.row;
            column=a.column;
            
            el = new long double*[a.row];
            for (long int i=0; i!=a.row; ++i)
            {
                el[i] = new long double[a.column];
                for (long int j=0; j!=a.column; ++j)
                    el[i][j] = a.el[i][j];
            }
            return *this;
        }

        // Operators
        Matrix& swap(long int i, long int j)      // Меняет местами i-ю и j-ю строки
        {
            auto temp = el[i];
            el[i] = el[j];
            el[j] = temp;
            return *this;
        }
        
        void copy(Matrix m)          // Копирует в нашу матрицу матрицу m
        {
            if (m.row == row && m.column == column)
            {
                for (long int i=0; i!=row; ++i) 
                    for (long int j=0; j!=column; ++j)
                        el[i][j]=m.el[i][j];
            }
            else
            {
                cout << "Error: copy - different shape" << endl;
            }
        }

        void mul(long int x)
        {
            for(long int i=0; i!=row; i++)
                for(long int j=0; j!=column; j++)
                    el[i][j] *= x;
        }
        
        void mul(Matrix m)           // Умножает данную матрицу на матрицу m и записывает туда же
        {
            Matrix result(row, m.column, 'z');
            long double summ = 0;
            for (long int i=0; i!=row; ++i) 
                for (long int j=0; j!= m.column; ++j)
                    {
                        summ = 0;
                        for (long int k=0; k!=column; ++k)
                            summ += el[i][k]*m.el[k][j];
                        result.el[i][j] = summ;
                    }
            this->copy(result);
        }

        void Display()
        {
            for(long int i=0; i!=row; i++)
            {
                for(long int j=0; j!=column; j++)
                {
                    cout.width(13);
                    cout << el[i][j];
                }
                cout << endl;
            }
            cout << endl;
        }
        
        // methods
        long double& Element(long int i, long int j)
        {
            if (i<row && j<column)
                return el[i][j];
            else
                cout << "Error: Element out of the bound" << endl;
        }
 
        char type()
        {
            long int N = row;
            long int M = column;
            if (N != M) return 'r';

            long int e = 0;
            long int l = 0;
            long int u = 0;

            for (long int i=0; i!=N; ++i)
                for (long int j=0; j!=M; ++j)
                {
                    if (i==j && el[i][j] == 1) e+=1;
                    else if (el[i][j] != 0) 
                    {
                        if (i<j) u += 1;
                        else if (i>j) l += 1;
                    }
                }

            if (e == N && l == 0 && u == 0) return 'i';
            if (l == 0 && u != 0) return 'u';
            if (u == 0 && l != 0) return 'l';
            if (l == 0 && u == 0) return 'd';
            return '?';
        }

        long double det() 
        {
            char tp = this->type();
            switch (tp)
            {
            case 'e':
                return 1.;
                // break;
            case '?':
                cout << "unknown det" << endl;
                return -1.;
                // break;
            default:
                long double d = 1.;
                for (long int i=0; i!=row; ++i)
                    d *= el[i][i];
                return d;
                // break;
            }
        }

};
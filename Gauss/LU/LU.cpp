#include <iostream>
#include <cmath>
using namespace std;

class Vector
{
public:
    // Инициализация нулевого вектора
    Vector(int s) :elem{new double[s]}, sz{s}
    {
        for (int i=0; i!=s; i++)
            elem[i]=0;
    }
    // Инициализация списком Vector vl = { 1, 2, 3, 4, 5}; 
    Vector(std::initializer_list<double> lst) :elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())}
    {
        copy(lst.begin(), lst.end(),elem);
    }
    // Операторы
    Vector& operator + (Vector v1) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]+=v1[i]; 
        return *this;
    }
    Vector& operator += (Vector v1) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]+=v1[i]; 
        return *this;
    }  
    Vector& operator - (Vector v1) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]-=v1[i]; 
        return *this;
    }
    Vector& operator -= (Vector v1) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]-=v1[i]; 
        return *this;
    }
    Vector& operator + (int k) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]+=k; 
        return *this;
    }    
    Vector& operator += (int k) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]+=k; 
        return *this;
    }
    Vector& operator - (int k) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]-=k; 
        return *this;
    }
    Vector& operator -= (int k) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]-=k; 
        return *this;
    }
    Vector& operator - () 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]=-elem[i]; 
        return *this;
    }
    Vector& operator * (double k) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]*=k; 
        return *this;
    }
    Vector& operator *= (double k) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]*=k; 
        return *this;
    }
    // // Очистка памяти
    // ~Vector()
    // {
    //     delete[] elem;
    // }
    double& operator[] (int i) { return elem[i]; }
    int size() const { return sz; }
    void input(){
        for (int i=0; i<sz; ++i)
            cin>>elem[i];
    }
    void print()
    {
        for (int i = 0; i!=sz; i++) cout<<elem[i]<<"    ";
        cout << endl;
    }
private:
    double* elem;
    int  sz;
};

class Matrix // Не обязательно квадратные
{
public:
    Vector* vec;
    int row, column;
    char type;

    // Инициализация нулевой матрицы
    Matrix(int r, int c, char tp = 'z') :vec{new Vector(r)}, row{r}, column{c}, type{tp}
    {
        switch (type) 
        {
        // case 'z':
        //     for (int i=0; i!=row; i++)
        //         vec[i]= Vector(column);
        //     break;
        case 'e':
            
            for (int i=0; i!=row; i++)
                {
                    vec[i]=Vector(column);
                    vec[i][i] = 1.;
                }
            break;                
            
        case 'g':
            
                for (int i=0; i!=row; i++)
                {
                    vec[i]=Vector(column);
                    for (int j=0; j!=column; j++)
                        vec[i][j] = 1./(i+j+1);
                }
            break;
            
        default:
            for (int i=0; i!=row; i++)
                vec[i]=Vector(column);
        }
        
    }
    // Вывод/ввод матрицы
    void print() const
    {
        for (int i=0; i!=row; i++)
            vec[i].print();
        cout << endl;
    }
    void input()
    {
        for (int i=0; i!=row; i++)
            vec[i].input();
    }
    
    // Разница между 2мя матрицами в L2 и max. При желании сравнения с 0 -> вписать Matrix(row, column)
    double distinction_max (Matrix m)
    {
        double dist = 0;
        for (int i=0; i!=row; ++i) 
            for (int j=0; j!=column; ++j)
                {
                    double temp = abs(vec[i][j] - m[i][j]);
                    if (temp > dist) dist = temp;
                }
        return dist;
    }
    double distinction_L2 (Matrix m)
    {
        double dist = 0;
        for (int i=0; i!=row; ++i) 
            for (int j=0; j!= column; ++j)
                    dist += abs(vec[i][j] - m[i][j]);
        return sqrt(dist);
    }

    // Операторы 
    Vector operator[] (int i) { return vec[i]; }
    Matrix& operator + (Matrix m) 
    { 
        for (int i=0; i!=row; ++i) // Инициализация элементов 
            vec[i]+=m[i]; 
        return *this;
    }
    Matrix& operator += (Matrix m) 
    { 
        for (int i=0; i!=row; ++i) // Инициализация элементов 
            vec[i]+=m[i]; 
        return *this;
    }
    Matrix& operator - (Matrix m) 
    { 
        for (int i=0; i!=row; ++i) // Инициализация элементов 
            vec[i]-=m[i]; 
        return *this;
    }
    Matrix& operator -= (Matrix m) 
    { 
        for (int i=0; i!=row; ++i) // Инициализация элементов 
            vec[i]-=m[i]; 
        return *this;
    }
    Matrix& operator - () 
    { 
        for (int i=0; i!=row; ++i) // Инициализация элементов 
            vec[i]= -vec[i]; 
        return *this;
    }
    Matrix& operator *= (double k)
    {
        for (int i=0; i!=row; ++i)
            vec[i] *= k;
        return *this;
    } 
    Matrix& copy(Matrix m)          // Копирует в нашу матрицу матрицу m
    {
        for (int i=0; i!=row; ++i) 
            for (int j=0; j!=column; ++j)
                vec[i][j]=m[i][j];
        return *this;
    }
    Matrix& mul(Matrix m)           // Умножает данную матрицу на матрицу m и записывает туда же
    {
        Matrix result(row, m.column);
        for (int i=0; i!=row; ++i) 
            for (int j=0; j!= m.column; ++j)
                {
                    double summ = 0;
                    for (int k=0; k!=column; ++k)
                        summ += vec[i][k]*m[k][j];
                    result[i][j] = summ;
                }
        this->copy(result);
        return *this;
    }
    Matrix& swap(int i, int j)      // Меняет местами i-ю и j-ю строки
    {
        Vector temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
        return *this;
    }

};

// Разница между 2мя матрицами в L2 и max. При желании сравнения с 0 -> вписать Matrix(row, column)
double distinction_max (Matrix m1, Matrix m2)
    {
        double dist = 0;
        for (int i=0; i!=m1.row; ++i) 
            for (int j=0; j!= m2.column; ++j)
                {
                    double temp = abs(m1[i][j] - m2[i][j]);
                    if (temp > dist) dist = temp;
                }
        return dist;
    }
double distinction_L2 (Matrix m1, Matrix m2)
    {
        double dist = 0;
        for (int i=0; i!=m1.row; ++i) 
            for (int j=0; j!= m2.column; ++j)
                    dist += abs(m1[i][j] - m2[i][j]);
        return sqrt(dist);
    }

Matrix mul(Matrix m1, Matrix m2) 
    { 
        Matrix result(m1.row, m2.column);
        for (int i=0; i!=m1.row; ++i) 
            for (int j=0; j!= m2.column; ++j)
                {
                    double summ = 0;
                    for (int k=0; k!=m1.column; ++k)
                        summ += m1[i][k]*m2[k][j];
                    result[i][j]=summ;
                }
        return result;
    }

void LU(Matrix& U, Matrix& L)
{
    int N = U.row;
    int M = U.column;
    double a;
    double b;
    for (int i=0; i!=N; ++i)
    {
        if (U[i][i] == 0)
        {
            int k = i;
            while (U[k][i] == 0 && k != N) k++;
            if (k == N+1) break;
            U.swap(i, k);
        }
        else if (U[i][i] != 0)
        {
            a = U[i][i];
            for (int j=i+1; j!=M; ++j)
            {
                b = U[j][i];
                L[j][i] = b/a;
                for (int k=i; k!=M; ++k)
                    U[j][k] -= U[i][k]*b/a;
            }
        }

    }
}

int main() 
{
    int N = 4;
    // cout << endl << -3 << endl;

    // Matrix G(N, N, 'g');
    // cout << endl << -2 << endl;
    // Matrix L(N, N, 'e');
    // cout << endl << -1 << endl;

    Matrix L(N, N);


    // Matrix U(N, N);
    // cout << endl << 0 << endl;

    // U.copy(G);

    // cout << endl << 1 << endl;

    // LU(U, L);
    // cout << endl << 2 << endl;

    // // U.print();
    // // L.print();

    // Matrix C = mul(L, U);
    // cout << endl << 3 << endl;

    // cout << distinction_max(G, C) << endl;

    // A.print();
    // B.print();
    // A *= 1.5;
    // A.print();

    // Matrix C(3, 3, 'i'), G(3, 3, 'g');
    // C.print();
    // G.print();

    // Matrix C = mul(A, Matrix(2, 2));
    // C.print();

    // A.mul(B);
    // A.print();

    // cout << distinction_L2(A, B);
    // cout << A.distinction_L2(B);

    return 0;
}
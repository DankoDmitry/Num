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
    double& operator[] (int i) { return elem[i]; }
    // void print()
    // {
    //     for (int i = 0; i!=sz; i++) cout<<elem[i]<<"    ";
    //     cout << endl;
    // }
    // Очистка памяти
    ~Vector()
    {
        delete[] elem;
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
    Matrix(int r, int c) :vec{new Vector(r)}, row{r}, column{c}
    {
        for (int i=0; i!=row; i++)
            vec[i]=Vector(column);        
    }
    Vector operator[] (int i) { return vec[i]; }
    // Вывод/ввод матрицы
    // void print() const
    // {
    //     for (int i=0; i!=row; i++)
    //         vec[i].print();
    //     cout << endl;
    // }
};

int main() 
{
    int N = 5;

    Matrix L(N, N);

    return 0;
}
#include <iostream>
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
    Vector& operator+ (Vector v1) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]+=v1[i]; 
        return *this;
    }
    Vector& operator+= (Vector v1) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]+=v1[i]; 
        return *this;
    }  
    Vector& operator- (Vector v1) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]-=v1[i]; 
        return *this;
    }
    Vector& operator-= (Vector v1) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]-=v1[i]; 
        return *this;
    }
    Vector& operator+ (int k) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]+=k; 
        return *this;
    }    
    Vector& operator+= (int k) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]+=k; 
        return *this;
    }
    Vector& operator- (int k) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]-=k; 
        return *this;
    }
    Vector& operator-= (int k) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]-=k; 
        return *this;
    }
    Vector& operator- () 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]=-elem[i]; 
        return *this;
    }
    Vector& operator* (int k) 
    { 
        for (int i=0; i!=sz; ++i) // Инициализация элементов 
            elem[i]*=k; 
        return *this;
    }
    Vector& operator*= (int k) 
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
        for (int i = 0; i!=sz; i++) cout<<elem[i]<<" ";
        cout << endl;
    }
private:
    double* elem;
    int  sz;
};


int main()
{
    Vector v1 {1,2.3,4};
    v1.print();

    return 0;
}
#include <iostream> 
#include <vector>
using namespace std; 

double square(double x)                                                 // double - число с плавающей точкой двойной точности
{
    return x*x; 
}

void print_square(double x)                                             // void - не возвращает никакого значения
{ 
    cout << "Квадрат " << x << " равен "<< square(x) << " \n"; 
}

void print_sizeof(char x)                                             // void - не возвращает никакого значения
{ 
    cout << sizeof(x) << " \n"; 
}

void print_type()                                             // void - не возвращает никакого значения
{ 
    cout << "\n" << "Типы переменных:" << "\n";
    cout << sizeof(char) << " - Размер char" << '\n';
    cout << sizeof(int) << " - Размер int"  << '\n';
    cout << sizeof(float) << " - Размер float"  << '\n';
    cout << sizeof(long) << " - Размер long"  << '\n';
    cout << sizeof(double) << " - Размер double"  << '\n';
}

void print_notation()                                             // void - не возвращает никакого значения
{ 
    cout << "\n" << "Нотация и система исчисления:" << "\n";
    cout << 534*10 << " - Произведение 534*10" << '\n';
    cout << 0534*010 << " - Произведение 0534*010 в восьмиричной системе"  << '\n';
    cout << 0x534*0x10 << " - Произведение 0x534*0x10 в шестнадцатиричной системе"  << '\n';
    cout << 0b1011*0b10 << " - Произведение 0b1011*0b10 в бинарной сиситеме"  << '\n';
}

void print_arifmetic()
{
    cout << "\n" << "Арифметика:" << endl;
    cout << "x+y, x-y, x*y, x/y - Стандартные" << endl;
    cout << "+x, -x - Унарные" << endl;
    cout << "x%y - Остаток от деления" << endl;
    cout << "\n" << "Операторы сравнения:" << endl;
    cout << "x==y, x!=y, x<y, x>y, x<=y, x>=y" << endl;
    cout << "\n" << "Логические операторы:" << endl;
    cout << "x&y - Побитовое and" << endl;
    cout << "x|y - Побитовое or" << endl;
    cout << "x^y - Побитовое исключающее или" << endl;
    cout << "~x - Побитовое дополнение" << endl;
    cout << "x&&y - and" << endl;
    cout << "x||y - or" << endl;
    cout << "!x - not" << endl;
}

void print_initialization()
{
    cout << "\n" << "Инициализация:" << endl;
    cout << "double d1 = 2.3;" << endl;
    cout << "double d2 {2.3};"<< endl;
    cout << "double d3 = {2.3};" << endl;
    cout << "complex<double> z1 = 1;" << endl;
    cout << "complex<int> z2 {d1,d2};" << endl;
    cout << "complex<double> z3 = {d1,d2};" << endl;
    cout << "vector<int> v {1,2,3,4,5,6};" << endl;
    cout << "Можно не вводить тип переменной," << endl;
    cout << "если он может быль выведен из инициализатора:" << endl;
    cout << "auto b = true;" << endl;
    cout << "auto ch = 'x';" << endl;
    cout << "auto i = 123;" << endl;
    cout << "auto bb {true};" << endl;
}

void copy_fct()
{
    int v1[5] = {0,1,2,3,4};
    int v2[5];
    for (auto i=0; i!=5; i++)
        v2[i] = v1[i];

    cout << *v2 << endl;
}

void print_mass()
{
    int v[5] = {0,1,2,3,4};
    for (auto x : v)
        cout << x;
    for (auto y : {1,3,6,1,63,61,43,2})
        cout << y;
}

void increment()
{
    int v[] = {0,1,2,3,4,5,6,7,8,9};
    for (auto& x : v){
        cout << x << " ";
        ++x; ++x;
        cout << x << endl;
    }
}

int count_x(const char* p, char x)
{
    if (p==nullptr) return 0;
    int count = 0;
    for (; *p!=0; ++p) if (*p==x) ++count;
    return count;
}

bool accept_y_n()
{
    cout << "Работаем дальше (y или n)?\n";
    char answer;

    cin >> answer;
    if (answer == 'y') return true;
    return false;
}

bool accept_y_n_2()
{
    cout << "Работаем дальше (y или n)?\n";
    char answer;

    cin >> answer;
    switch (answer)
    {
        case 'y':
        return true;
        case 'n':
        return false;
        default:
        cout << "Считаю это за нет\n";
        return false;
    }
}

int main () 
{
    // print_square(1.1);
    // print_type();
    // print_notation();
    // print_arifmetic();
    // print_initialization();
    // copy_fct();
    // print_mass();
    // increment();
    // cout << count_x("", 'g');
    // cout << accept_y_n_2();








}
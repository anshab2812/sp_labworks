// SP_labwork0.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <limits.h>
using namespace std;

int main()
{
    cout << "\tCHAR:"<<endl;
    cout << "Number of bits = " <<CHAR_BIT<<" = 1 byte"<< endl;
    cout << "Minimum for a signed char = " << SCHAR_MIN << endl;
    cout << "Maximum for a signed char = " << SCHAR_MAX << endl;
    cout << endl;
    cout << "Minimum for a unsigned char = 0 "<< endl;
    cout << "Maximum for a unsigned char = " << UCHAR_MAX  << endl;
    cout << endl;
    cout << "\tSHORT:" << endl;
    cout << "Number of bits = " << sizeof(short) << " byte" << endl;
    cout << "Minimum for a signed short = " << SHRT_MIN << endl;
    cout << "Maximum for a signed short = " << SHRT_MAX << endl;
    cout << endl;
    cout << "Minimum for a unsigned short = 0 " << endl;
    cout << "Maximum for a unsigned short = " << USHRT_MAX << endl;
    cout << endl;
    cout << "\tINT:" << endl;
    cout << "Number of bits = " << sizeof(short) << " byte" << endl;
    cout << "Minimum for a signed int = " << INT_MIN << endl;
    cout << "Maximum for a signed int = " << INT_MAX << endl;
    cout << endl;
    cout << "Minimum for a unsigned int = 0 " << endl;
    cout << "Maximum for a unsigned int = " << UINT_MAX << endl;
    cout << endl;
    cout << "\tLONG:" << endl;
    cout << "Number of bits = " << sizeof(long) << " byte" << endl;
    cout << "Minimum for a signed long = " << LONG_MIN << endl;
    cout << "Maximum for a signed long = " << LONG_MAX << endl;
    cout << endl;
    cout << "Minimum for a unsigned long = 0 " << endl;
    cout << "Maximum for a unsigned long = " << ULONG_MAX << endl;
    cout << endl;
    cout << "\tLONG LONG:" << endl;
    cout << "Number of bits = " << sizeof(long long) << " byte" << endl;
    cout << "Minimum for a signed long long = " << LLONG_MIN << endl;
    cout << "Maximum for a signed long long = " << LLONG_MAX << endl;
    cout << endl;
    cout << "Minimum for a unsigned long long = 0 " << endl;
    cout << "Maximum for a unsigned long long = " << ULLONG_MAX << endl;
    cout << endl;
    cout << "\tDOUBLE:" << endl;
    cout << "Number of bits = " << sizeof(double) << " byte" << endl;
    cout << "Minimum for a double = " << numeric_limits<double>::min()<< endl;
    cout << "Maximum for a double = " << numeric_limits<double>::max()<< endl;
    cout << endl;
    cout << "\tFLOAT:" << endl;
    cout << "Number of bits = " << sizeof(float) << " byte" << endl;
    cout << "Minimum for a double = " << numeric_limits<float>::min() << endl;
    cout << "Maximum for a double = " << numeric_limits<float>::max() << endl;
    cout << endl;
    

    system("pause");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

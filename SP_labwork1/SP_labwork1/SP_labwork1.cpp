#include <iostream>
#include <windows.h>
#include <fstream>

#define DIV 1024

using namespace std;

string GetLastErrorAsString();


string GetLastErrorAsString()
{
    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        0, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, 0);

    std::string message(messageBuffer, size);

    LocalFree(messageBuffer);

    return message;
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    string input = "";
    if (argc != 2) {
        cin >> input;
    }
    else input = (string)argv[argc-1];

    
    MEMORYSTATUS mem;
    mem.dwLength - sizeof(mem);
    GlobalMemoryStatus(&mem);
    SYSTEM_INFO sys;
    GetSystemInfo(&sys);

    if (input == "-e")
    {
        LocalAlloc(LMEM_FIXED, 7444444444448888);
        cout << "Ошибка: " << GetLastErrorAsString() << endl;
    }
    else if (input == "-s") {
        cout<< "\tИнформация о памяти:" <<endl;
        cout << "Используется " << mem.dwMemoryLoad << "% памяти" << endl;
        cout << "Общий объем физической памяти : " << mem.dwTotalPhys / DIV << " KB" << endl;
        cout << "Доступно физической памяти:" << mem.dwAvailPhys / DIV << " KB" << endl;
        cout << "Общий объем виртуальной памяти: " << mem.dwTotalVirtual / DIV << " KB" << endl;
        cout << "Доступно виртуальной памяти:" << mem.dwAvailVirtual / DIV << " KB" << endl;
        cout << "\tИнформация о процессоре:" << endl;
        cout << "OEM ID:"<< sys.dwOemId << endl;
        cout << "Число процессоров: " << sys.dwNumberOfProcessors << endl;
        cout << "Размер страницы: " << sys.dwPageSize << endl;
        cout << "Тип процессора: " << sys.dwProcessorType << endl;
        cout << "Минимальые адреса приложений: " << sys.lpMinimumApplicationAddress << endl;
        cout << "Максимальные адреса приложений: " << sys.lpMaximumApplicationAddress << endl;
        cout << "Маска процессора:" << sys.dwActiveProcessorMask << endl;
    }
    else cout << "Неправильный ключ" << endl;
    system("pause");
        
}

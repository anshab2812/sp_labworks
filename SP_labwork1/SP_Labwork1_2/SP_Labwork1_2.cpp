#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

void clearBuff();
string GetLastErrorAsString();
bool OpenCreate(LPCWSTR OpenFile, LPCWSTR CreateNew);
CHAR MultiByteBuffer[MAXBYTE * sizeof(CHAR)];
WCHAR WideCharBuffer[MAXBYTE * sizeof(WCHAR)];
DWORD ReadC = 0;
DWORD WriteC = 0;
WORD Changed = 0;
HANDLE RF;
HANDLE WF;
LPCWSTR WidetoMulti = L"ascii2.txt";
LPCWSTR MultitoWide = L"unicode2.txt";
LPCWSTR MultiFile = L"ascii.txt";
LPCWSTR WideFile = L"unicode.txt";

string GetLastErrorAsString()
{
    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        0, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, 0);

    std::string message(messageBuffer, size);

    LocalFree(messageBuffer);

    return message;
}

bool OpenCreate(LPCWSTR OpenFile, LPCWSTR CreateNew)
{
    RF = CreateFile(OpenFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (RF == INVALID_HANDLE_VALUE) {
        cout << "Ошибка: " << GetLastErrorAsString() << endl;
    }
    WF = CreateFile(CreateNew, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (WF == INVALID_HANDLE_VALUE) {
        cout << "Ошибка: " << GetLastErrorAsString() << endl;
    }
    return true;
}

void clearBuff() {
    for (int i = 0; i < (MAXBYTE) * sizeof(CHAR); i++)
    {
        MultiByteBuffer[i] = 0;
    }

    for (int i = 0; i < (MAXBYTE) * sizeof(WCHAR); i++) {
        WideCharBuffer[i] = 0;
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");


    string input = "";
    string key = "";
    if (argc != 2) {
        cin >> key;
    }
    else {
        key = (string)argv[argc - 1];
    }

    if (key == "-a") {
        if (OpenCreate(MultiFile, MultitoWide))
        {
            ReadC = 0;
            WriteC = 0;
            Changed = 0;
            while (true)
            {
                clearBuff();
                if (!ReadFile(RF, MultiByteBuffer, MAXBYTE, &ReadC, NULL))
                {
                    cout << "Ошибка: " << GetLastErrorAsString() << endl;
                    break;
                }
                Changed = MultiByteToWideChar(CP_UTF8, 0, MultiByteBuffer, -1, WideCharBuffer, ReadC * sizeof(WCHAR));
                if (!WriteFile(WF, WideCharBuffer, (Changed - 1) * sizeof(WCHAR), &WriteC, NULL))
                {
                    cout << "Ошибка: " << GetLastErrorAsString() << endl;
                    break;
                }
                cout << "Перекодировкам произошла успешно!"<<endl;
                break;
            }

        }

    }
    else if (key == "-u") {
        if (OpenCreate(WideFile, WidetoMulti))
        {
            ReadC = 0;
            WriteC = 0;
            Changed = 0;

            while (true)
            {
                clearBuff();
                if (!ReadFile(RF, WideCharBuffer, (MAXBYTE - 1) * sizeof(WCHAR), &ReadC, NULL))
                {
                    cout << "Ошибка: " << GetLastErrorAsString() << endl;
                    break;
                }
                Changed = WideCharToMultiByte(CP_ACP, 0, WideCharBuffer, -1, MultiByteBuffer, ReadC, NULL, NULL);
                if (!WriteFile(WF, MultiByteBuffer, Changed, &WriteC, NULL))
                {
                    cout << "Ошибка: " << GetLastErrorAsString() << endl;
                    break;
                }
                cout << "Перекодировкам произошла успешно!"<<endl;
                break;
            }
        }
        else cout << "Неправильный ключ" << endl;
    }
    system("pause");
}
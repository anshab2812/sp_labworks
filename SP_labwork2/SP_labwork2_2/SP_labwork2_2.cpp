#define _CRT_SECURE_NO_WARNINGS
#define EXIT 0
#define CHANGE 1
#define DELETE 2
#define ADD 3
#define PRINT 4
#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;
LPCWSTR RECB = L"records.txt";

struct rec {
	UINT number;
	FILETIME creationTime;
	TCHAR data[81];
	UINT changesCounter;
};
struct header {
	UINT not_Null;
	UINT SizeFile;
};

header ReadCounts() {
	HANDLE hFile1 = CreateFile(RECB, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(hFile1, NULL, NULL, FILE_BEGIN);
	header h;
	DWORD jk;
	ReadFile(hFile1, &h, sizeof(header), &jk, NULL);
	if (jk == 0) {
		h.not_Null = 0;
		h.SizeFile = 0;
	}
	CloseHandle(hFile1);
	return h;
}

vector<rec> ReadRecs() {
	HANDLE hFile1 = CreateFile(RECB, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(hFile1, sizeof(header), NULL, FILE_BEGIN);
	vector<rec> datas(0);

	rec i;
	DWORD jk = 0;
	for (;;) {
		bool k = ReadFile(hFile1, &i, sizeof(rec), &jk, NULL);
		if (jk == 0) break;
		datas.push_back(i);
	}
	CloseHandle(hFile1);

	return datas;
}
void PrintAllInformation() {
	SYSTEMTIME cm;
	vector <rec> datas = ReadRecs();
	header count = ReadCounts();
	cout << "Размер файла: " << count.SizeFile << " bytes; Не пустых записей: " << count.not_Null << endl;
	for (int i = 0; i < datas.size(); i++) {
		FileTimeToSystemTime(&datas[i].creationTime, &cm);
		cout << "Номер = " << datas[i].number << endl;
		cout << cm.wDay << "." << cm.wMonth << "." << cm.wYear << " " << cm.wHour << ":" << cm.wMinute << endl;
		cout << "Данные = ";
		wcout << datas[i].data << endl;
		cout << "Счетчик изменений = " << datas[i].changesCounter << endl;
		cout << "------------------------------" << endl;
		cout << endl;
	}
}

void Add_rec() {
	header count = ReadCounts();
	vector <rec> data = ReadRecs();
	SYSTEMTIME k, s;
	GetLocalTime(&k);

	FILETIME ft;
	rec f;
	SystemTimeToFileTime(&k, &ft);
	FileTimeToSystemTime(&ft, &s);
	cout << "Введите строку: ";
	scanf("%80S", f.data);

	if (lstrcmp(f.data, L"*") == 0) {
		f.number = data.size();
		f.creationTime = ft;
		lstrcpy(f.data, L"");
		f.changesCounter = 0;
	}
	else {
		f.number = data.size();
		f.creationTime = ft;
		f.changesCounter = 0;
		count.not_Null++;
	}

	data.push_back(f);

	count.SizeFile = sizeof(count) + sizeof(rec) * data.size();
	HANDLE hFile1 = CreateFile(RECB, GENERIC_WRITE, NULL, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	LPDWORD temp = NULL;
	SetFilePointer(hFile1, NULL, NULL, FILE_BEGIN);
	WriteFile(hFile1, &count, sizeof(header), temp, NULL);
	SetFilePointer(hFile1, NULL, NULL, FILE_END);
	for (int i = 0; i < data.size(); i++) {
		WriteFile(hFile1, &data[i], sizeof(rec), temp, NULL);
	}
	CloseHandle(hFile1);
}
void Change_rec() {
	SYSTEMTIME cm;
	header count = ReadCounts();
	vector <rec> data = ReadRecs();
	UINT n;
	cout << "Введите номер записи для изменения: " << endl;
	cin >> n;
	cout << "\nЭто ваша запись" << endl;

	FileTimeToSystemTime(&data[n].creationTime, &cm);

	cout << "Номер = " << data[n].number << endl;
	cout << cm.wDay << "." << cm.wMonth << "." << cm.wYear << " " << cm.wHour << ":" << cm.wMinute << endl;
	cout << "Данные = ";
	wcout << data[n].data << endl;
	cout << "Счетчик изменений = " << data[n].changesCounter << endl;
	cout << "------------------------------" << endl;
	cout << endl;

	cout << "\nВведите новую строку:";
	cout << "\nДля пустой строки введите '*'): ";
	TCHAR str[81];

	lstrcpy(str, data[n].data);
	scanf("%80S", data[n].data);
	if (lstrcmp(data[n].data, L"*") == 0) {
		lstrcpy(data[n].data, L"");
	}
	if (lstrcmp(str, L"") == 0 && lstrcmp(data[n].data, L"") != 0) {
		count.not_Null++;
	}
	if (lstrcmp(str, L"") != 0 && lstrcmp(data[n].data, L"") == 0) {
		count.not_Null--;
	}
	data[n].changesCounter++;
	HANDLE hFile1 = CreateFile(RECB, GENERIC_WRITE, NULL, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	LPDWORD musor = NULL;

	SetFilePointer(hFile1, NULL, NULL, FILE_BEGIN);
	WriteFile(hFile1, &count, sizeof(header), musor, NULL);
	SetFilePointer(hFile1, NULL, NULL, FILE_END);

	for (int i = 0; i < data.size(); i++) {
		WriteFile(hFile1, &data[i], sizeof(rec), musor, NULL);
	}
	CloseHandle(hFile1);

}
void delete_rec() {
	header count = ReadCounts();
	vector <rec> data = ReadRecs();
	int i;
	cout << "Введите номер записи для удаления: ";
	cin >> i;

	if (lstrcmp(data[i].data, L"") != 0)
		count.not_Null--;

	data.erase(data.begin() + i);
	vector<rec>(data).swap(data);
	for (int k = 0; k < data.size(); k++) {
		data[k].number = k;
	}
	count.SizeFile = sizeof(count) + sizeof(rec) * data.size();
	HANDLE hFile1 = CreateFile(RECB, GENERIC_WRITE, NULL, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	LPDWORD musor = NULL;

	SetFilePointer(hFile1, NULL, NULL, FILE_BEGIN);
	WriteFile(hFile1, &count, sizeof(header), musor, NULL);
	SetFilePointer(hFile1, NULL, NULL, FILE_END);

	for (int i = 0; i < data.size(); i++) {
		WriteFile(hFile1, &data[i], sizeof(rec), musor, NULL);
	}
	CloseHandle(hFile1);
}
int main() {
	setlocale(LC_ALL, "rus");
	int key;
	while (true) {
		cout << "Программа для работы с записями" << endl;
		cout << "\t\tМеню:" << endl;
		cout << "1 - Изменить запись" << endl;
		cout << "2 - Удалить запись" << endl;
		cout << "3 - Добавить запись" << endl;
		cout << "4 - Вывести все записи" << endl;
		cout << "0 - Выход" << endl;
		cout << "Выберите действие: ";
		cin >> key;
		switch (key) {
		case EXIT:
			exit(EXIT_SUCCESS);
			break;
		case CHANGE:
			Change_rec();
			break;
		case DELETE:
			delete_rec();
			break;
		case ADD:
			Add_rec();
			break;
		case PRINT:
			PrintAllInformation();
			break;
		default:
			cout << "Change your choice" << endl;
			Sleep(100);
			system("cls");
		}
		system("pause");
		system("cls");
	}
}

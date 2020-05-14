#define _CRT_SECURE_NO_WARNINGS
#define EXIT 0
#define PRINT 1
#define COPY 2
#define CREATE 3
#define FULL 4
#define DELETE 5
#include <windows.h>;
#include <iostream>
#include <locale.h>

using namespace std;

void SetDirectory(TCHAR* buffer) {
	for (;;) {
		cout << "Введите полный путь к директории" << endl;
		cout << "Используйте двойные слеши как эти - C://" << endl;
		TCHAR temp[MAX_PATH];
		cin.get();
		scanf("%80S", temp);
		BOOL res = SetCurrentDirectory(temp);
		if (!res)
			cout << "\nНе корректное имя директории!" << endl;
		else {
			GetCurrentDirectory(sizeof(temp), temp);
			cout << "Текущая директория: ";
			wcout << temp << endl;
			lstrcpy(buffer, L"");
			lstrcpy(buffer, temp);
			return;
		}
	}
}

void PrintDirectory(TCHAR* buffer) {
	cout << "Файлы в текущей директории: " << endl;
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	TCHAR find[MAX_PATH];
	lstrcpy(find, buffer);
	lstrcat(find, L"\\*");
	hf = FindFirstFile((LPCWSTR)find, &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			SYSTEMTIME systime;
			FILETIME localfiletime;
			FileTimeToLocalFileTime(&FindFileData.ftCreationTime, &localfiletime);
			FileTimeToSystemTime(&localfiletime, &systime);
			LONGLONG size = (FindFileData.nFileSizeHigh * (MAXDWORD + 1)) + FindFileData.nFileSizeLow;
			wcout << FindFileData.cFileName << "\t" << size << " bytes " << "\t" << systime.wDay << "." << systime.wMonth << "." << systime.wYear << " " << systime.wHour << ":" << systime.wMinute << endl;
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
}

void CopyFileInCurDir(TCHAR* buffer) {
	BOOL k = true;
	for (;;) {
		cout << "Введите имя файла в текущей директории: ";
		TCHAR find[MAX_PATH], s[MAX_PATH], newDirectory[MAX_PATH];
		lstrcpy(find, buffer);
		cin.get();
		scanf("%80S", s);
		lstrcat(find, L"\\");
		lstrcat(find, s);
		cout << "\nВведите директорию для копирования (E://...): ";
		//cin.get();
		scanf("%80S", newDirectory);
		lstrcat(newDirectory, L"\\");
		lstrcat(newDirectory, s);
		k = CopyFile(find, newDirectory, false);
		if (k) return;
		else cout << "Не корректное имя!(s)\n";
	}
}
void MyCreateDirectory(TCHAR* buffer) {
	TCHAR newDir[MAX_PATH], way[MAX_PATH];
	cout << "Введите новое имя директории: ";
	cin.get();
	scanf("%80S", newDir);
	lstrcpy(way, buffer);
	lstrcat(way, L"\\");
	lstrcat(way, newDir);
	if (CreateDirectory(way, NULL))
		cout << "Создание произошло успешно!" << endl;
	else
		cout << "Ошибка при создании директории!" << endl;
}

void FullInformation(TCHAR* buffer) {
	TCHAR file[MAX_PATH], way[MAX_PATH];
	cout << "Введите имя файла в текущей директории: ";
	cin.get();
	scanf("%80S", file);
	lstrcpy(way, buffer);
	lstrcat(way, L"\\");
	lstrcat(way, file);
	HANDLE hFile1 = CreateFile(way, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	BY_HANDLE_FILE_INFORMATION infa;
	BOOL f = GetFileInformationByHandle(hFile1, &infa);
	CloseHandle(hFile1);
	if (!f) {
		cout << "Не корректное имя файла\n";
	}
	else {
		cout << "Это ";
		if (infa.dwFileAttributes == FILE_ATTRIBUTE_HIDDEN)
			cout << "скрыт";
		if (infa.dwFileAttributes == FILE_ATTRIBUTE_SYSTEM)
			cout << "системный";
		if (infa.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE)
			cout << "архивный";
		if (infa.dwFileAttributes == FILE_ATTRIBUTE_COMPRESSED)
			cout << "сжатый";
		if (infa.dwFileAttributes == FILE_ATTRIBUTE_NORMAL)
			cout << "нормальный";
		cout << " файл.\n";
		SYSTEMTIME systime;
		FILETIME localfiletime;
		FileTimeToLocalFileTime(&infa.ftCreationTime, &localfiletime);
		FileTimeToSystemTime(&localfiletime, &systime);
		cout << "Дата создания - " << systime.wDay << "." << systime.wMonth << "." << systime.wYear << " " << systime.wHour << ":" << systime.wMinute << endl;

		FileTimeToLocalFileTime(&infa.ftLastWriteTime, &localfiletime);
		FileTimeToSystemTime(&localfiletime, &systime);
		cout << "Последние изменения - " << systime.wDay << "." << systime.wMonth << "." << systime.wYear << " " << systime.wHour << ":" << systime.wMinute << endl;
	}
}
void MyDelete(TCHAR* buffer) {
	TCHAR file[MAX_PATH], way[MAX_PATH];
	cout << "Введите имя файла для удаления: ";
	cin.get();
	scanf("%80S", file);
	lstrcpy(way, buffer);
	lstrcat(way, L"\\");
	lstrcat(way, file);
	BOOL g = DeleteFile(way), k;
	if (!g) {
		k = RemoveDirectory(way);
		cout << "Файл удален!";
	}
	if (!g && !k) {
		DWORD lastErrorCode = GetLastError();
		void* cstr;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&cstr,
			0,
			NULL
		);
		PTCHAR res((LPTSTR)cstr);
		printf("%s", res);
	}
}

int main() {

	setlocale(LC_ALL, "rus");

	while (true) {
		TCHAR buffer[MAX_PATH];
		GetCurrentDirectory(sizeof(buffer), buffer);

		int choice;

		system("cls");
		cout << "Текущая директория: ";
		wcout << buffer << endl;
		cout << "\t\tМеню:" << endl;
		cout << "0 - Выбрать директорию" << endl;
		cout << "1 - Вывести содержимое директории" << endl;
		cout << "2 - Копирование файла" << endl;
		cout << "3 - Создание директории" << endl;
		cout << "4 - Подробная информация о файле" << endl;
		cout << "5 - Удаление файла  или пустой директории" << endl;
		cout << "Выберите действие: ";

		cin >> choice;

		switch (choice) {
		case EXIT:
			SetDirectory(buffer);
			break;
		case PRINT:
			PrintDirectory(buffer);
			break;
		case COPY:
			CopyFileInCurDir(buffer);
			break;
		case CREATE:
			MyCreateDirectory(buffer);
			break;
		case FULL:
			FullInformation(buffer);
			break;
		case DELETE:
			MyDelete(buffer);
			break;
		}
		system("pause");
	}
}

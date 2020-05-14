#include <stdio.h>
#include <Windows.h>
#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");
	HANDLE mutex = CreateMutexA(NULL, FALSE, "MyMutex");

	if (WaitForSingleObject(mutex, 0) == WAIT_OBJECT_0)
	{
		std::cout << "Запущен" << std::endl;
		std::cout << "Нажмите любую клавишу" << std::endl;
		getchar();
		ReleaseMutex(mutex);
	}
	else
	{
		printf("Не могу начать программу!");
		getchar();
	}

	CloseHandle(mutex);
	return 0;
}
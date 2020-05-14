#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define TimeToSleep 1
#define NumberOfThread 0

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <iostream>

HANDLE semaphore;

int random_int(int min, int max);
DWORD WINAPI thread_function(LPVOID param);
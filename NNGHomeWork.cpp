// NNGHomeWork.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Project includes
#include "Task.h"

// Standard library includes
#include <locale>
#include <iostream>


int main(const int argc, const wchar_t* argv[])
{
	setlocale(LC_ALL, "Hungarian_Hungary.1250"); 

	auto task = Task();
	std::wstring file_path;
	if (   !(argc > 1 && task.Read(argv[1]))
		&& !(task.Read(L"network.csv"))
		&& !(std::wcin >> file_path && task.Read(file_path.c_str()))) 
	{
		return static_cast<int>(task.GetLastError());
	}

	if (!task.Solve()) 
	{
		return static_cast<int>(task.GetLastError());
	}

	return 0;
}
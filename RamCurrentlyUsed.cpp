#include "windows.h"
#include "psapi.h"
#include "stdio.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <locale>
#include <iomanip>
#include <time.h>
#include <stdio.h>

using namespace std;

int main() {
	for (size_t i = 0; i < 100000; i++)
	{
		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);
		DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;

		DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

		PROCESS_MEMORY_COUNTERS_EX pmc;

		GetProcessMemoryInfo(GetCurrentProcess(),

			reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), sizeof(pmc));

		SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

		DWORDLONG totalPhysMem = memInfo.ullTotalPhys;

		DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

		cout << "total ram: " << totalPhysMem << "   ram used:   " << physMemUsed << "    ram used by this program:  " << physMemUsedByMe << endl;

	}

};


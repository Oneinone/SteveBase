#pragma once

#pragma warning(disable: 4996) // The POSIX name for this item is deprecated

#if RELEASE
	#pragma warning(disable: 4530) // C++ exception handler used, but unwind semantics are not enabled.
	#pragma warning(disable: 4577) // 'noexcept' used with no exception handling mode specified; termination on exception is not guaranteed.
	
	#define FMT_EXCEPTIONS 0
	#define FMT_USE_NOEXCEPT 1
	#define JSON_NOEXCEPTION 1

#endif

#ifdef _MSC_VER
	#define VC_EXTRALEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#define _USE_MATH_DEFINES
#define NOMINMAX

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "shlwapi.lib")

#include <WinSock2.h> 
#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <psapi.h>
#include <d3d9.h>
#include <tchar.h>
#include <process.h>

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <experimental/generator>
#include <locale>
#include <codecvt>
#include <future>
#include <random>
#include <ctime>
#include <limits>
#include <thread>
#include <memory>

#include <bandit/bandit.h>

using namespace std;
using namespace bandit;
using namespace experimental;
using namespace snowhouse;

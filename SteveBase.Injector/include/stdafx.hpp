#pragma once

#pragma warning(disable: 4996) // The POSIX name for this item is deprecated
#pragma warning(disable: 4554)
#pragma warning(disable: 4307) // integer overflow
#pragma warning(disable: 4244)
#pragma warning(disable: 4146)
#pragma warning(disable: 4305) // truncation from 'bigger' to 'smaller' 
#pragma warning(disable: 4309) // truncation of constant value
#pragma warning(disable: 4307) // integral constant overflow
#pragma warning(disable: 4308) // negative integral constant converted to unsigned type

#ifdef _MSC_VER
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define _USE_MATH_DEFINES
#define NOMINMAX

#define FollowMathConcepts 1

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "shlwapi.lib")

#include <d3d9.h>
#include <process.h>
#include <psapi.h>
#include <shlwapi.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <windows.h>
#include <WinSock2.h>

#include <algorithm>
#include <any>
#include <cmath>
#include <codecvt>
#include <cstdint>
#include <cstdlib>
#include <ctime>
// #include <experimental/generator>
#include <fstream>
#include <functional>
// #include <future>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <variant>
#include <vector>

#include <vendor/debugbreak/debugbreak.h>
#include <vendor/ggformat/ggformat.h>
#include <vendor/hash/hash.h>
#include <vendor/rang/include/rang.hpp>
#include <vendor/XorStr/XorStr.h>

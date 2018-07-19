#pragma once

#include <windows.h>
#include <winternl.h>
#include <psapi.h>

#include <array>
#include <string>

#undef or // <ciso646> wtf?

namespace SteveBase::Utility {
    // RelinkModuleToPEB, UnlinkModuleFromPEB, RemovePeHeader
    // _UNICODE_STRING, _PEB_LDR_DATA, _PEB, _LDR_MODULE, _UNLINKED_MODULE 
    // => https://gist.github.com/Fonger/15268efb19eb328431b0de7560ddcb53


    typedef struct _PEB_LDR_DATA {
        ULONG      Length;
        BOOLEAN    Initialized;
        PVOID      SsHandle;
        LIST_ENTRY InLoadOrderModuleList;
        LIST_ENTRY InMemoryOrderModuleList;
        LIST_ENTRY InInitializationOrderModuleList;
    } PEB_LDR_DATA, *PPEB_LDR_DATA;

    typedef struct _PEB {
#ifdef _WIN64
        UINT8 _PADDING_[24];
#else
        UINT8 _PADDING_[12];
#endif
        PEB_LDR_DATA* Ldr;
    } PEB, *PPEB;

    typedef struct _LDR_MODULE {
        LIST_ENTRY      InLoadOrderModuleList;
        LIST_ENTRY      InMemoryOrderModuleList;
        LIST_ENTRY      InInitializationOrderModuleList;
        PVOID           BaseAddress;
        PVOID           EntryPoint;
        ULONG           SizeOfImage;
        UNICODE_STRING  FullDllName;
        UNICODE_STRING  BaseDllName;
        ULONG           Flags;
        SHORT           LoadCount;
        SHORT           TlsIndex;
        LIST_ENTRY      HashTableEntry;
        ULONG           TimeDateStamp;
    } LDR_MODULE, *PLDR_MODULE;

    typedef struct _UNLINKED_MODULE {
        HMODULE hModule;
        PLIST_ENTRY RealInLoadOrderLinks;
        PLIST_ENTRY RealInMemoryOrderLinks;
        PLIST_ENTRY RealInInitializationOrderLinks;
        PLDR_MODULE Entry; // =PLDR_DATA_TABLE_ENTRY
    } UNLINKED_MODULE;

#define UNLINK(x)					\
	(x).Flink->Blink = (x).Blink;	\
	(x).Blink->Flink = (x).Flink;

#define RELINK(x, real)			\
	(x).Flink->Blink = (real);	\
	(x).Blink->Flink = (real);	\
	(real)->Blink = (x).Blink;	\
	(real)->Flink = (x).Flink;

    // some generic functions for the lulz
    class SystemUtility {
    public:
        // darkstorm copypasted
        static HMODULE SafeGetModuleHandle(const char *name);
        static MODULEINFO GetModuleInfo(const char *moduleName);
        // learn_more copypasted
        static PBYTE FindPattern(PBYTE dwAddress, DWORD dwLength, const char *pattern);
        static PBYTE FindModulePattern(const char *moduleDll, const char *pattern);
        /*
        // copypasted
        static string GetLastErrorAsString() {
            //Get the error message, if any.
            auto errorMessageID = GetLastError();
            if (errorMessageID == 0) {
                return string(); //No error message has been recorded
            }

            LPSTR messageBuffer = nullptr;
            size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                nullptr, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, nullptr);

            string message(messageBuffer, size);

            //Free the buffer.
            LocalFree(messageBuffer);

            return message;
        }
        */

        static std::string ProduceModulePath(HINSTANCE dllHandle);

        static PPEB GetPEB();

        static void RelinkModuleToPEB(HMODULE hModule);
        static bool UnlinkModuleFromPEB(HMODULE hModule);

        static bool RemovePeHeader(HANDLE GetModuleBase);

        static std::array<int, 4> GetCPUID();

        // copypasted
        static bool IsTrapFlagRaised();

        // copypasted
        static bool IsDebuggerFound();
    };
}
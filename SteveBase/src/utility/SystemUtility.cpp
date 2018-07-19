#include <GlobalDefines.hpp>
#include <utility/SystemUtility.hpp>

#include <intrin.h>
#include <shlwapi.h>
#include <vector>
#include <array>

namespace SteveBase::Utility {
    std::vector<UNLINKED_MODULE> UnlinkedModules;

    // darkstorm copypasted
    HMODULE SystemUtility::SafeGetModuleHandle(const char * name) {
        HMODULE hModule;
        for (hModule = nullptr; hModule == nullptr; Sleep(1)) {
            hModule = GetModuleHandle(name);
        }
        return hModule;
    }

    MODULEINFO SystemUtility::GetModuleInfo(const char * moduleName) {
        MODULEINFO modinfo;
        const auto moduleHandle = SafeGetModuleHandle(moduleName);
        GetModuleInformation(GetCurrentProcess(), moduleHandle, &modinfo, sizeof(MODULEINFO));
        return modinfo;
    }

    // learn_more copypasted
    PBYTE SystemUtility::FindPattern(PBYTE dwAddress, DWORD dwLength, const char * pattern) {
#define INRANGE(x,a,b)		(x >= a && x <= b) 
#define getBits( x )		(INRANGE(x,'0','9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xa))
#define getByte(x) (getBits(x[0]) << 4 | getBits(x[1]))
        auto oldStr = pattern;
        auto pat = oldStr;
        PBYTE firstMatch = nullptr;
        for (auto pCur = dwAddress; pCur < dwAddress + dwLength; pCur++) {
            if (!*pat) return firstMatch;
            if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
                if (!firstMatch) firstMatch = pCur;
                if (!pat[2]) return firstMatch;
                if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
                else pat += 2;
            } else {
                pat = oldStr;
                firstMatch = nullptr;
            }
        }
        return nullptr;
    }

    PBYTE SystemUtility::FindModulePattern(const char * moduleDll, const char * pattern) {
        const auto info = GetModuleInfo(moduleDll);
        return FindPattern((PBYTE)info.lpBaseOfDll, info.SizeOfImage, pattern);
    }

    std::string SystemUtility::ProduceModulePath(HINSTANCE dllHandle) {
        char buffer[4096];
        GetModuleFileName(dllHandle, buffer, 4096);
        PathRemoveFileSpec(buffer);
        int len = strlen(buffer);

        buffer[len] = '\\';
        buffer[len + 1] = '\0';
        return std::string(buffer);
    }

    PPEB SystemUtility::GetPEB() {
#ifdef _WIN64
        return (PPEB)__readgsqword(0x60);
#else
        return (PPEB)__readfsdword(0x30);
#endif
    }

    // copypasted
	void SystemUtility::RelinkModuleToPEB(HMODULE hModule) {
		auto it = std::find_if(UnlinkedModules.begin(), UnlinkedModules.end(), [&](UNLINKED_MODULE val) { return val.hModule == hModule; });

		if (it == UnlinkedModules.end()) {
			//DBGOUT(TEXT("Module Not Unlinked Yet!);
			return;
		}
		auto m = *it;
		RELINK(m.Entry->InLoadOrderModuleList, m.RealInLoadOrderLinks);
		RELINK(m.Entry->InInitializationOrderModuleList, m.RealInInitializationOrderLinks);
		RELINK(m.Entry->InMemoryOrderModuleList, m.RealInMemoryOrderLinks);
		UnlinkedModules.erase(it);
	}

	// copypasted
	bool SystemUtility::UnlinkModuleFromPEB(HMODULE hModule) {
		auto it = std::find_if(UnlinkedModules.begin(), UnlinkedModules.end(), [&](UNLINKED_MODULE val) { return val.hModule == hModule; });
		if (it != UnlinkedModules.end()) {
			//DBGOUT(TEXT("Module Already Unlinked!);
			return false;
		}

		auto pPEB = GetPEB();
		auto CurrentEntry = pPEB->Ldr->InLoadOrderModuleList.Flink;

		for (; CurrentEntry != &pPEB->Ldr->InLoadOrderModuleList && CurrentEntry != nullptr; CurrentEntry = CurrentEntry->Flink) {
			PLDR_MODULE Current = CONTAINING_RECORD(CurrentEntry, LDR_MODULE, InLoadOrderModuleList);
			if (Current->BaseAddress == hModule) {
				UNLINKED_MODULE CurrentModule;
				CurrentModule.hModule = hModule;
				CurrentModule.RealInLoadOrderLinks = Current->InLoadOrderModuleList.Blink->Flink;
				CurrentModule.RealInInitializationOrderLinks = Current->InInitializationOrderModuleList.Blink->Flink;
				CurrentModule.RealInMemoryOrderLinks = Current->InMemoryOrderModuleList.Blink->Flink;
				CurrentModule.Entry = Current;
				UnlinkedModules.push_back(CurrentModule);

				UNLINK(Current->InLoadOrderModuleList);
				UNLINK(Current->InInitializationOrderModuleList);
				UNLINK(Current->InMemoryOrderModuleList);

				return true;
			}
		}

		return false;
	}

    bool SystemUtility::RemovePeHeader(HANDLE GetModuleBase) {
        const auto pDosHeader = (PIMAGE_DOS_HEADER)GetModuleBase;
        const auto pNTHeader = (PIMAGE_NT_HEADERS)((PBYTE)pDosHeader + (DWORD)pDosHeader->e_lfanew);

        if (pNTHeader->Signature != IMAGE_NT_SIGNATURE) {
            return false;
        }

        if (pNTHeader->FileHeader.SizeOfOptionalHeader) {
            DWORD Protect;
            auto Size = pNTHeader->FileHeader.SizeOfOptionalHeader;
            VirtualProtect((void*)GetModuleBase, Size, PAGE_EXECUTE_READWRITE, &Protect);
            SecureZeroMemory((void*)GetModuleBase, Size);
            VirtualProtect((void*)GetModuleBase, Size, Protect, &Protect);
        }
        return true;
    }

    std::array<int, 4> SystemUtility::GetCPUID() {
        std::array<int, 4> ret;
        __cpuid(ret.data(), 0);
        return ret;
    }

    // copypasted

    bool SystemUtility::IsTrapFlagRaised() {
        BOOL isDebugged = TRUE;
        __try {
            __asm
            {
                pushfd
                or dword ptr[esp], 0x100 // set the Trap Flag 
                popfd                    // Load the value into EFLAGS register
                nop
}
            } __except (EXCEPTION_EXECUTE_HANDLER) {
                // If an exception has been raised – debugger is not present
                isDebugged = FALSE;
            }
            return isDebugged == TRUE; // may be reduntant but BOOL and bool are definitely two different types so i added a check
                                       // BOOL is 32 bits and bool is 8 bits in winapi only BOOLEAN is 8 bits
        }

    // copypasted

    bool SystemUtility::IsDebuggerFound() {
        BOOL debuggerPresent = FALSE;
        CheckRemoteDebuggerPresent(GetCurrentProcess(), &debuggerPresent);
        return IsDebuggerPresent() || debuggerPresent || IsTrapFlagRaised();
    }
	
#if 0
	// copypasted
#pragma section(".CRT$XLY", long, read)
	__declspec(thread) int var = 0xDEADBEEF;
	VOID NTAPI TlsCallback(PVOID DllHandle, DWORD Reason, VOID *Reserved) {
		var = 0xB15BADB0; // Required for TLS Callback call
		if (IsDebuggerPresent()) {
			TerminateProcess(GetCurrentProcess(), 0);
		}
	}
	__declspec(allocate(".CRT$XLY")) PIMAGE_TLS_CALLBACK g_tlsCallback = TlsCallback;
#endif
}

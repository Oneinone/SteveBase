#include <stdafx.hpp>
#include <LoadLibrary.hpp>
#include <SmartHandle.hpp>

namespace SteveBase::Injector {
    const auto fpLoadLibrary = (LPVOID)GetProcAddress(GetModuleHandle(text("kernel32.dll")), text("LoadLibraryA"));

    void LoadLibrary::Inject(Process process, string dllPath) {
        const auto mem = VirtualAllocEx(process, nullptr, dllPath.length() + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        if (mem == nullptr) {
            throw runtime_error{ text("Library name cannot be allocated") };
        }

        ggprint(text("[=] Library Name Allocated...\n"));

        process.WriteMemory((uintptr_t)mem, (uintptr_t)dllPath.c_str(), (size_t)dllPath.length() + 1);
        ggprint(text("[=] Library Name Written...\n"));

        SmartHandle thread = CreateRemoteThread(process, nullptr, 0, (LPTHREAD_START_ROUTINE)fpLoadLibrary, mem, 0, nullptr);
        ggprint(text("[=] Thread created...\n"));

        WaitForSingleObject(thread, INFINITE);
        ggprint(text("[=] Success!\n"));

        VirtualFreeEx(process, mem, dllPath.length() + 1, MEM_RELEASE);
        ggprint(text("[=] DLL path memory freed.\n"));
    }
}

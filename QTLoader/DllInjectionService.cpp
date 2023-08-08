#include "DllInjectionService.h"


DllInjectionService& DllInjectionService::getInstance(const char* dllPath)
{
    static DllInjectionService instance(dllPath);
    return instance;
}

DllInjectionService::DllInjectionService(const char* dllPath) : dllPath_(dllPath), hProcess_(NULL), remoteMem_(NULL)
{
}

DllInjectionService::~DllInjectionService()
{
    if (remoteMem_)
        VirtualFreeEx(hProcess_, remoteMem_, 0, MEM_RELEASE);
    if (hProcess_)
        CloseHandle(hProcess_);
}

bool DllInjectionService::Inject(DWORD processId)
{
    if (!OpenTargetProcess(processId))
        return false;

    if (!AllocateRemoteMemory())
        return false;

    if (!WriteDllPathToMemory())
        return false;

    return CreateRemoteThreadAndInject();
}

bool DllInjectionService::OpenTargetProcess(DWORD processId)
{
    hProcess_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (!hProcess_)
    {
        std::cerr << "Failed to open target process." << std::endl;
        return false;
    }
    return true;
}

bool DllInjectionService::AllocateRemoteMemory()
{
    remoteMem_ = VirtualAllocEx(hProcess_, NULL, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!remoteMem_)
    {
        std::cerr << "Failed to allocate remote memory." << std::endl;
        CloseHandle(hProcess_);
        return false;
    }
    return true;
}

bool DllInjectionService::WriteDllPathToMemory()
{
    if (!WriteProcessMemory(hProcess_, remoteMem_, dllPath_, strlen(dllPath_) + 1, NULL))
    {
        std::cerr << "Failed to write to remote process memory." << std::endl;
        VirtualFreeEx(hProcess_, remoteMem_, 0, MEM_RELEASE);
        CloseHandle(hProcess_);
        return false;
    }
    return true;
}

bool DllInjectionService::CreateRemoteThreadAndInject()
{
    LPVOID loadLibraryAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    HANDLE hThread = CreateRemoteThread(hProcess_, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, remoteMem_, 0, NULL);

    if (!hThread)
    {
        std::cerr << "Failed to create remote thread." << std::endl;
        VirtualFreeEx(hProcess_, remoteMem_, 0, MEM_RELEASE);
        CloseHandle(hProcess_);
        return false;
    }

    

    std::cout << "DLL injected successfully." << std::endl;
    return true;
}


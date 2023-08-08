#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <TlHelp32.h>


class DllInjectionService
{
public:
    static DllInjectionService& getInstance(const char* dllPath);
    ~DllInjectionService();

    bool Inject(DWORD processId);
    DWORD GetProcessIdByName(const std::wstring& processName)
    {
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Failed to create process snapshot." << std::endl;
            return 0;
        }

        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        if (!Process32First(hSnapshot, &entry))
        {
            CloseHandle(hSnapshot);
            std::cerr << "Failed to get the first process." << std::endl;
            return 0;
        }

        do
        {
            std::wstring processFileName = entry.szExeFile;
            if (processFileName.find(processName) != std::wstring::npos)
            {
                CloseHandle(hSnapshot);
                return entry.th32ProcessID;
            }
        } while (Process32Next(hSnapshot, &entry));

        CloseHandle(hSnapshot);
        return 0; // Return 0 if the process name is not found
    }

private:
    DllInjectionService(const char* dllPath);
    DllInjectionService(const DllInjectionService&) = delete;
    DllInjectionService& operator=(const DllInjectionService&) = delete;

    bool OpenTargetProcess(DWORD processId);
    bool AllocateRemoteMemory();
    bool WriteDllPathToMemory();
    bool CreateRemoteThreadAndInject();

    const char* dllPath_;
    HANDLE hProcess_;
    LPVOID remoteMem_;
};

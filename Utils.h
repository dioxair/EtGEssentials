#pragma once

#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

inline bool is_process_running(const wchar_t* processName)
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    const HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry))
        while (Process32Next(snapshot, &entry))
            if (!_wcsicmp(entry.szExeFile, processName))
                exists = true;

    CloseHandle(snapshot);
    return exists;
}

inline void check_window_focus()
{
    // if EtGEssentials is focused
    if (GetConsoleWindow() == GetForegroundWindow())
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            exit(0);
        }
    }
}

inline void infinite_health(Memory::External memory, Address health_addr)
{
    while (true)
    {
        Sleep(100);
        memory.write<float>(health_addr, 50, true);
        check_window_focus();
    }
}

inline void infinite_blanks(Memory::External memory, Address blanks_addr)
{
    while (true)
    {
        Sleep(100);
        memory.write<int>(blanks_addr, 10, true);
        check_window_focus();
    }
}

int WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPTSTR lpszCmdLine, int nCmdShow);
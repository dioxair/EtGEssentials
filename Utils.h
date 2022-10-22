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

inline bool check_window_focus()
{
    // if EtGEssentials is focused
    if (GetConsoleWindow() == GetForegroundWindow())
    {
        return true;
    }
    return false;
}

inline void press_q_key()
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.wVk = 0x51; // virtual key code for Q
    ip.ki.dwFlags = 0; // Key press flag
    SendInput(1, &ip, sizeof(INPUT)); // Send Q key press input

    ip.ki.wVk = 0x51; // virtual key code for Q
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // Release Q key flag
    SendInput(1, &ip, sizeof(INPUT)); // Send Q key release input
}

inline void infinite_health(Memory::External memory, Address health_addr)
{
    while (true)
    {
        Sleep(100);
        if (memory.read<float>(health_addr) != 50) // unsafe, will fix later (hopefully)
        {
            memory.write<float>(health_addr, 50, true);
        }
        if (check_window_focus())
        {
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                exit(0);
            }
        }
    }
}

inline void infinite_blanks(Memory::External memory, Address blanks_addr)
{
    while (true)
    {
        Sleep(100);
        if (memory.read<int>(blanks_addr) != 10)
        {
        		memory.write<int>(blanks_addr, 10, true);
        }
        if (check_window_focus())
        {
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                exit(0);
            }
        }
    }
}

inline void auto_blank_spam(Memory::External memory, Address blanks_addr)
{
    HWND etg_hwnd = FindWindowA(NULL, "Enter the Gungeon");

	while (true)
	{
        if (check_window_focus())
        {
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                exit(0);
            }
        }

        Sleep(100);
        if (etg_hwnd == GetForegroundWindow())
        {
            if (memory.read<int>(blanks_addr) != 10)
            {
                memory.write<int>(blanks_addr, 10, true);
            }

            press_q_key();
        }
	}
}

int WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPTSTR lpszCmdLine, int nCmdShow);
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>
#include "CasualLibrary.hpp"

using namespace std;

bool is_process_running(const wchar_t* processName)
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

int WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPTSTR lpszCmdLine, int nCmdShow);

int main()
{
    int choice;

    const wstring name(L"EtG.exe");
    const wchar_t* etg_process_name = name.c_str();

    if (is_process_running(etg_process_name) == false)
    {
        MessageBox(0, _T("Enter the Gungeon isn't open! Please open Enter the Gungeon and then restart the program!"), _T("Error"), 0);
        return 0;
    }

    Memory::External memory = Memory::External("EtG.exe", true);

    Address health_base_addr = memory.getModule("UnityPlayer.dll");
    Address health_addr = memory.getAddress(health_base_addr + 0x0146FCC8, { 0x120, 0x10, 0x30, 0x30, 0x38, 0x28, 0x118 });

    Address shells_base_addr = memory.getModule("mono.dll");
    Address shells_addr = memory.getAddress(shells_base_addr + 0x00264A68, { 0xC0, 0xE90, 0xA8, 0x198, 0x1C });
    // shells are the currency used in EtG runs if you didn't know

    float current_health = memory.read<float>(health_addr);
    float current_shells = memory.read<int>(shells_addr);

    while (true) {
        cout << "EtG Essentials\n";
        cout << " 1 - Infinite Health\n";
        cout << " 2 - Infinite Shells\n";
        cout << " 3 - Exit.\n";
        cout << " Enter your choice and press return: ";

        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nGave Player infinite health!\n\n";
            // write to health pointer in a loop
            break;
        case 2:
            cout << "\nGave Player 100 million shells!\n\n";
            // write to shells pointer once
            break;
        case 3:
            cout << "\nExiting..";
            Sleep(2000);
            return 0;
        default:
            cout << "Not a valid choice, choose again.";
            break;
        }
    }
}
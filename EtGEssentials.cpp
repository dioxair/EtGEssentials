#include <iostream>
#include "CasualLibrary.hpp"

using namespace std;

int main()
{
    int choice;
    bool loop_running = true;

    Memory::External memory = Memory::External("EtG.exe", true);

    Address health_base_addr = memory.getModule("UnityPlayer.dll");
    Address health_addr = memory.getAddress(health_base_addr + 0x0146FCC8, { 0x120, 0x10, 0x30, 0x30, 0x38, 0x28, 0x118 });

    Address shells_base_addr = memory.getModule("mono.dll");
    Address shells_addr = memory.getAddress(shells_base_addr + 0x00264A68, { 0xC0, 0xE90, 0xA8, 0x198, 0x1C });
    // shells are the currency used in EtG runs if you didn't know

    float current_health = memory.read<float>(health_addr);
    float current_shells = memory.read<int>(shells_addr);

    while (loop_running != false) {
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
            loop_running = false;
            return 0;
            break;
        default:
            cout << "Not a valid choice, choose again.";
            break;
        }

    }
    return 0;
}
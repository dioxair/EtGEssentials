#include <iostream>
#include "CasualLibrary.hpp"

int main()
{
    Memory::External memory = Memory::External("EtG.exe", true);

    Address health_base_addr = memory.getModule("UnityPlayer.dll");
    Address health_addr = memory.getAddress(health_base_addr + 0x0146FCC8, { 0x120, 0x10, 0x30, 0x30, 0x38, 0x28, 0x118 });

    Address shells_base_addr = memory.getModule("mono.dll");
    Address shells_addr = memory.getAddress(shells_base_addr + 0x00264A68, { 0xC0, 0xE90, 0xA8, 0x198, 0x1C });
    // shells are the currency used in EtG runs if you didn't know
}
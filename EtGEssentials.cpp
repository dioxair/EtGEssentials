#include <iostream>
#include "CasualLibrary.hpp"

int main()
{
    Memory::External memory = Memory::External("EtG.exe", true);

    Address base_addr = memory.getModule("UnityPlayer.dll");
    Address health_addr = memory.getAddress(base_addr + 0x0146FCC8, { 0x120, 0x10, 0x30, 0x30, 0x38, 0x28, 0x118 });
}
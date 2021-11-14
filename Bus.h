//
// Created by zep on 11/13/21.
//
#pragma once
#include <cstdint>
#include "CPU6502.h"
#include <array>

class Bus
{
public:
    Bus();
    ~Bus();

public:
    CPU6502 cpu;

    // Fake RAM
    std::array<uint8_t, 64 * 1024> ram;

public:
    // Bus Read & Write
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool bReadOnly = false);
};

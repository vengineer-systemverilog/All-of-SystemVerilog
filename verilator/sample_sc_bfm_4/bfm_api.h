#pragma once

#include <cstdint>
#include <iostream>

using namespace std;

uint32_t read(uint32_t addr);
void write(uint32_t addr, uint32_t data);

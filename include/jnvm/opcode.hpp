#pragma once
#include <cstdint>

namespace jnvm::Opcode
{
    constexpr std::int8_t BIPUSH = 0x1;
    constexpr std::int8_t ISTORE = 0x2;
    constexpr std::int8_t ILOAD = 0x3;
    constexpr std::int8_t IADD = 0x4;
}
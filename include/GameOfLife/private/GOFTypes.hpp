#ifndef GOF_TYPES_HPP
#define GOF_TYPES_HPP

#include <cstdint>

namespace GameOfLife
{

using index_t = uint64_t;

enum class cell_t : uint8_t 
{
    DEAD =  0b00001000,
    ALIVE = 0b00001100
};

}

#endif
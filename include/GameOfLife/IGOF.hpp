#ifndef I_GOF_HPP
#define I_GOF_HPP

#include <cstddef>

#include "ICheckBoard.hpp"

namespace GameOfLife
{

class IGOF
{
public:
    virtual ~IGOF() = default;

    const ICheckBoard& GetCheckBoard() const;
    const ICheckBoard& NextStep();
    std::size_t GetCurrentStep() const;
protected:
    std::size_t m_step = 0;
};

}

#endif
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

    virtual const ICheckBoard& GetCheckBoard() const = 0;
    virtual const ICheckBoard& NextStep() = 0;
    inline std::size_t GetCurrentStep() const
    {
        return m_step;
    }
protected:
    std::size_t m_step = 0;
};

}

#endif
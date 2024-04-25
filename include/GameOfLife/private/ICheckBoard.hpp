#ifndef I_CHECK_BOARD_HPP
#define I_CHECK_BOARD_HPP

#include "GOFTypes.hpp"

namespace GameOfLife
{

class ICheckBoard
{
public:
    inline ICheckBoard(index_t length, index_t heigh) 
    : m_checkboard_length(length), m_checkboard_heigh(heigh) 
    {
        
    }

    virtual ~ICheckBoard() = default;

    virtual cell_t Get(index_t i, index_t j) = 0;
    virtual void Set(index_t i, index_t j, cell_t value) = 0;

protected:
    index_t m_checkboard_length;
    index_t m_checkboard_heigh;
};

class IBorderCheckBoard : public ICheckBoard
{
public:
    inline IBorderCheckBoard(index_t length, index_t heigh) 
    : ICheckBoard(length, heigh), 
    m_big_checkboard_length(length + 2), m_big_checkboard_height(heigh + 2),
    INDEXING_OFFSET(m_big_checkboard_length + 1)
    {

    }

    virtual cell_t BigGet(index_t i, index_t j) = 0;
    virtual void BigSet(index_t i, index_t j, cell_t value) = 0;

protected:
    const index_t INDEXING_OFFSET;
    index_t m_big_checkboard_length;
    index_t m_big_checkboard_height;
};

}

#endif
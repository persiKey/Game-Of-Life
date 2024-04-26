#ifndef I_CHECK_BOARD_HPP
#define I_CHECK_BOARD_HPP

#include "GOFTypes.hpp"

namespace GameOfLife
{

class ICheckBoard
{
public:
    inline ICheckBoard(index_t length, index_t height) 
    : m_checkboard_length(length), m_checkboard_height(height) 
    {
        
    }

    virtual ~ICheckBoard() = default;

    virtual cell_t Get(index_t i, index_t j) const = 0;
    virtual void Set(index_t i, index_t j, cell_t value)= 0;

    inline index_t Length() const
    {
        return m_checkboard_length;
    }

    inline index_t Height() const
    {
        return m_checkboard_height;
    }
protected:
    index_t m_checkboard_length;
    index_t m_checkboard_height;
};

class IBorderCheckBoard : public ICheckBoard
{
public:
    inline IBorderCheckBoard(index_t length, index_t height) 
    : ICheckBoard(length, height), 
    m_big_checkboard_length(length + 2), m_big_checkboard_height(height + 2)
    {

    }

    virtual cell_t BigGet(index_t i, index_t j) const = 0;
    virtual void BigSet(index_t i, index_t j, cell_t value) = 0;

    inline index_t BigLength() const
    {
        return m_big_checkboard_length;
    }

    inline index_t BigHeight() const
    {
        return m_big_checkboard_height;
    }
    
protected:
    index_t m_big_checkboard_length;
    index_t m_big_checkboard_height;
};

}

#endif
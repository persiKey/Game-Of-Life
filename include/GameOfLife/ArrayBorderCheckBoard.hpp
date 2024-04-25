#ifndef ARRAY_CHECK_BOARD_HPP
#define ARRAY_CHECK_BOARD_HPP

#include "ICheckBoard.hpp"

namespace GameOfLife
{

class ArrayBorderCheckBoard : public IBorderCheckBoard
{
public:
    ArrayBorderCheckBoard(index_t length, index_t height);
    ~ArrayBorderCheckBoard() override;

    virtual cell_t Get(index_t i, index_t j) const override;
    virtual void Set(index_t i, index_t j, cell_t value) override;

    virtual cell_t BigGet(index_t i, index_t j) const override;
    virtual void BigSet(index_t i, index_t j, cell_t value) override;    

private:
    cell_t* m_data;
};

}

#endif
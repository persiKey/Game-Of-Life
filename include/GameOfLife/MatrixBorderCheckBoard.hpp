#ifndef MATRIX_BORDER_CHECK_BOARD_HPP
#define MATRIX_BORDER_CHECK_BOARD_HPP

#include "ICheckBoard.hpp"

namespace GameOfLife
{

class  MatrixBorderCheckBoard : public IBorderCheckBoard
{
public:
    MatrixBorderCheckBoard(index_t length, index_t height);
    ~MatrixBorderCheckBoard() override;

    virtual cell_t Get(index_t i, index_t j) const override;
    virtual void Set(index_t i, index_t j, cell_t value) override;

    virtual cell_t BigGet(index_t i, index_t j) const override;
    virtual void BigSet(index_t i, index_t j, cell_t value) override;    

private:
    cell_t** m_data;
};

}

#endif
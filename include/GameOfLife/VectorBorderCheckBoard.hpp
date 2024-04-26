#ifndef VECTOR_BORDER_CHECK_BOARD_HPP
#define VECTOR_BORDER_CHECK_BOARD_HPP

#include "ICheckBoard.hpp"

namespace GameOfLife
{

class VectorBorderCheckBoard : public IBorderCheckBoard
{
    friend class SequentialVectorTorusGOFAlgorithm;
public:
    VectorBorderCheckBoard(index_t length, index_t height);
    ~VectorBorderCheckBoard() override;

    virtual cell_t Get(index_t i, index_t j) const override;
    virtual void Set(index_t i, index_t j, cell_t value) override;

    virtual cell_t BigGet(index_t i, index_t j) const override;
    virtual void BigSet(index_t i, index_t j, cell_t value) override;   

private:
    cell_t* m_data;
    const index_t SMALL_TO_BIG_INDEXING_OFFSET;
    const index_t UP_LEFT_INDEXING_OFFSET;
    const index_t DOWN_LEFT_INDEXING_OFFSET;
};

}

#endif
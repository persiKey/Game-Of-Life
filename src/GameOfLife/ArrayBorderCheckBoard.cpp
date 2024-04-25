#include "ArrayBorderCheckBoard.hpp"

namespace GameOfLife
{
ArrayBorderCheckBoard::ArrayBorderCheckBoard(index_t length, index_t height)
: IBorderCheckBoard(length, height)
{
    m_data = new cell_t[m_big_checkboard_height * m_big_checkboard_length];
}

ArrayBorderCheckBoard::~ArrayBorderCheckBoard()
{
    delete[] m_data;
}

cell_t ArrayBorderCheckBoard::Get(index_t i, index_t j) const
{
    return m_data[INDEXING_OFFSET + i * m_big_checkboard_length + j];
}

void ArrayBorderCheckBoard::Set(index_t i, index_t j, cell_t value)
{
    m_data[INDEXING_OFFSET + i * m_big_checkboard_length + j] = value;
}

cell_t ArrayBorderCheckBoard::BigGet(index_t i, index_t j) const
{
    return m_data[i * m_big_checkboard_length + j];
}

void ArrayBorderCheckBoard::BigSet(index_t i, index_t j, cell_t value)
{
    m_data[i * m_big_checkboard_length + j] = value;
}
}
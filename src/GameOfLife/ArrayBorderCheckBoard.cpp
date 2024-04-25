#include "ArrayBorderCheckBoard.hpp"

namespace GameOfLife
{
ArrayBorderCheckBoard::ArrayBorderCheckBoard(index_t length, index_t heigh)
: IBorderCheckBoard(length, heigh)
{
}

ArrayBorderCheckBoard::~ArrayBorderCheckBoard()
{
    
}

cell_t ArrayBorderCheckBoard::Get(index_t i, index_t j)
{
    return cell_t();
}

void ArrayBorderCheckBoard::Set(index_t i, index_t j, cell_t value)
{
    
}

cell_t ArrayBorderCheckBoard::BigGet(index_t i, index_t j)
{
    return cell_t();
}

void ArrayBorderCheckBoard::BigSet(index_t i, index_t j, cell_t value)
{
    
}
}
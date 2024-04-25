#include "GameOfLife.hpp"

#include "ArrayBorderCheckBoard.hpp"


namespace GameOfLife
{
GameOfLife::GameOfLife(index_t length, index_t height, std::unique_ptr<IBorderGOFAlgorithm> &&solver)
    : m_checkboard(std::make_shared<ArrayBorderCheckBoard>(length, height)),
    m_checkboard_buffer(std::make_shared<ArrayBorderCheckBoard>(length, height)),
    m_step(0),
    m_solver(std::move(solver))
{
    
}

const ICheckBoard& GameOfLife::GetCheckBoard() const
{
    return *m_checkboard;
}

const ICheckBoard& GameOfLife::NextStep()
{
    m_solver->Compute(m_checkboard, m_checkboard_buffer);
    m_checkboard.swap(m_checkboard_buffer);
    ++m_step;
    return *m_checkboard;
}

std::size_t GameOfLife::GetCurrentStep() const
{
    return m_step;
}
}

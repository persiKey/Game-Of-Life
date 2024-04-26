#include "GameOfLife.hpp"

#include "ArrayBorderCheckBoard.hpp"


namespace GameOfLife
{
BorderCheckBoardGOF::BorderCheckBoardGOF(index_t length,
                       index_t height,
                       std::unique_ptr<IBorderGOFAlgorithm> &&solver,
                       std::unique_ptr<ICheckBoardFiller> filler)

    : m_checkboard(std::make_shared<ArrayBorderCheckBoard>(length, height)),
    m_checkboard_buffer(std::make_shared<ArrayBorderCheckBoard>(length, height)),
    m_solver(std::move(solver))
{
    auto value = m_checkboard_buffer->BigLength();
    filler->Fill(m_checkboard);
}

const ICheckBoard& BorderCheckBoardGOF::GetCheckBoard() const
{
    return *m_checkboard;
}

const ICheckBoard& BorderCheckBoardGOF::NextStep()
{
    m_solver->Compute(m_checkboard, m_checkboard_buffer);
    m_checkboard.swap(m_checkboard_buffer);
    ++m_step;
    return *m_checkboard;
}

std::size_t BorderCheckBoardGOF::GetCurrentStep() const
{
    return m_step;
}
}

#include "GameOfLife.hpp"

#include "ArrayBorderCheckBoard.hpp"


namespace GameOfLife
{
GOF::GOF(index_t length,
                       index_t height,
                       std::unique_ptr<IBorderGOFAlgorithm> &&solver,
                       std::unique_ptr<ICheckBoardFiller> filler)

    : m_checkboard(std::make_shared<ArrayBorderCheckBoard>(length, height)),
    m_checkboard_buffer(std::make_shared<ArrayBorderCheckBoard>(length, height)),
    m_step(0),
    m_solver(std::move(solver))
{
    auto value = m_checkboard_buffer->BigLength();
    filler->Fill(m_checkboard);
}

const ICheckBoard& GOF::GetCheckBoard() const
{
    return *m_checkboard;
}

const ICheckBoard& GOF::NextStep()
{
    m_solver->Compute(m_checkboard, m_checkboard_buffer);
    m_checkboard.swap(m_checkboard_buffer);
    ++m_step;
    return *m_checkboard;
}

std::size_t GOF::GetCurrentStep() const
{
    return m_step;
}
}

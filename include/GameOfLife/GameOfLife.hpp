#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <memory>

#include "IGOF.hpp"
#include "ICheckBoardFiller.hpp"

namespace GameOfLife
{

template <typename checkboard_t, typename algorithm_t>
class GOF : public IGOF
{
public:
    GOF(index_t length, 
        index_t height,
        std::unique_ptr<ICheckBoardFiller> filler)
    : m_checkboard(std::make_shared<checkboard_t>(length, height)),
    m_checkboard_buffer(std::make_shared<checkboard_t>(length, height)),
    m_solver(std::make_unique<algorithm_t>())
    {
        auto value = m_checkboard_buffer->BigLength();
        filler->Fill(m_checkboard);
    }           

    const ICheckBoard& GetCheckBoard() const override
    {
        return *m_checkboard;
    }

    const ICheckBoard& NextStep() override
    {
        m_solver->Compute(m_checkboard, m_checkboard_buffer);
        m_checkboard.swap(m_checkboard_buffer);
        ++m_step;
        return *m_checkboard;
    }

private:
    std::shared_ptr<checkboard_t> m_checkboard;
    std::shared_ptr<checkboard_t> m_checkboard_buffer;
    std::unique_ptr<algorithm_t> m_solver;
};

}

#endif
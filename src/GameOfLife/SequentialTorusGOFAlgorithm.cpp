#include "SequentialTorusGOFAlgorithm.hpp"

namespace GameOfLife
{

inline void CellChecker(uint8_t& index, cell_t cell)
{
    index = index << ((static_cast<uint8_t>(cell) & static_cast<uint8_t>(ALIVE_FLAG)) >> 2);
}
    
void SequentialTorusGOFAlgorithm::Compute(std::shared_ptr<IBorderCheckBoard> m_current_state, std::shared_ptr<IBorderCheckBoard> m_next_state)
{
    FillBorder(m_current_state);

    for (index_t j = 0; j < m_current_state->Height(); ++j)
    {
        for (index_t i = 0; i < m_current_state->Length(); ++i)
        {
            uint8_t index = 1;

            CellChecker(index, m_current_state->Get(i-1, j-1));
            CellChecker(index, m_current_state->Get(i, j-1));
            CellChecker(index, m_current_state->Get(i+1, j-1));

            CellChecker(index, m_current_state->Get(i-1, j+1));
            CellChecker(index, m_current_state->Get(i, j+1));
            CellChecker(index, m_current_state->Get(i+1, j+1));

            CellChecker(index, m_current_state->Get(i-1, j));
            CellChecker(index, m_current_state->Get(i+1, j));

            m_next_state->Set(i,j,
                              (index & static_cast<uint8_t>(m_current_state->Get(i,j))) ? cell_t::ALIVE : cell_t::DEAD);
        }
    }

}


void SequentialTorusGOFAlgorithm::FillBorder(std::shared_ptr<IBorderCheckBoard> m_current_state)
{
    for(index_t i = 1; i < m_current_state->Length() + 1; ++i)
    {
        m_current_state->BigSet(i,0, m_current_state->BigGet(i, m_current_state->Height()));
        m_current_state->BigSet(i,m_current_state->BigHeight() - 1, m_current_state->BigGet(i,1));
    }
    for(index_t i = 1; i < m_current_state->Height() + 1; ++i)
    {
        m_current_state->BigSet(0, i, m_current_state->BigGet(m_current_state->Length(), i));
        m_current_state->BigSet(m_current_state->BigLength() - 1, i, m_current_state->BigGet(1, i));
    }

    m_current_state->BigSet(0,0,
        m_current_state->Get(m_current_state->Length() - 1, m_current_state->Height() - 1));
    
    m_current_state->BigSet(m_current_state->BigLength() - 1, m_current_state->BigHeight() - 1,
        m_current_state->Get(0, 0));

    m_current_state->BigSet(0,m_current_state->BigHeight() - 1,
        m_current_state->Get(m_current_state->Length() - 1, 0));
    
    m_current_state->BigSet(m_current_state->BigLength() - 1,0,
        m_current_state->Get(0, m_current_state->Height() - 1));
    
}
}

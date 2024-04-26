#include "SequentialVectorTorusGOFAlgorithm.hpp"

namespace GameOfLife
{
void SequentialVectorTorusGOFAlgorithm::Compute(std::shared_ptr<VectorBorderCheckBoard> m_current_state, 
                                                std::shared_ptr<VectorBorderCheckBoard> m_next_state)
{
    FillBorder(m_current_state);
    for(index_t i = 0; i < m_current_state->BigLength() * m_current_state->BigHeight(); ++i)
    {
        uint8_t neighbors_counter = 1;
        
        index_t index = i + m_current_state->UP_LEFT_INDEXING_OFFSET;
        
        CellChecker(neighbors_counter, m_current_state->m_data[index++]);
        CellChecker(neighbors_counter, m_current_state->m_data[index++]);
        CellChecker(neighbors_counter, m_current_state->m_data[index++]);

        index = i + m_current_state->DOWN_LEFT_INDEXING_OFFSET;
        CellChecker(neighbors_counter, m_current_state->m_data[index++]);
        CellChecker(neighbors_counter, m_current_state->m_data[index++]);
        CellChecker(neighbors_counter, m_current_state->m_data[index++]);

        CellChecker(neighbors_counter, m_current_state->m_data[i-1]);
        CellChecker(neighbors_counter, m_current_state->m_data[i+1]);

        m_next_state->m_data[i] = 
                            (neighbors_counter & static_cast<uint8_t>(m_current_state->m_data[i])) ? cell_t::ALIVE : cell_t::DEAD;        
    }
}
}
#include "SequentialVectorTorusGOFAlgorithm.hpp"

namespace GameOfLife
{
void SequentialVectorTorusGOFAlgorithm::Compute(std::shared_ptr<VectorBorderCheckBoard> m_current_state, 
                                                std::shared_ptr<VectorBorderCheckBoard> m_next_state)
{
    FillBorder(m_current_state);
    
    ComputeVectorChunk(0, m_current_state->Length() * m_current_state->Height(), m_current_state, m_next_state);
}

void SequentialVectorTorusGOFAlgorithm::ComputeVectorChunk(index_t begin, index_t end,
    std::shared_ptr<VectorBorderCheckBoard> m_current_state, std::shared_ptr<VectorBorderCheckBoard> m_next_state)
{
    --end;
    const auto i_begin = (begin / m_current_state->Length()) * m_current_state->BigLength() + begin % m_current_state->Length() + m_current_state->SMALL_TO_BIG_INDEXING_OFFSET;
    const auto i_end = (end / m_current_state->Length()) * m_current_state->BigLength() + end % m_current_state->Length() + m_current_state->SMALL_TO_BIG_INDEXING_OFFSET;

    const auto data =  m_current_state->m_data;

    for(index_t i = i_begin; i <= i_end; ++i)
    {
        uint8_t neighbors_counter = 1;
        
        index_t index = i - m_current_state->UP_LEFT_INDEXING_OFFSET;
        
        CellChecker(neighbors_counter, data[index++]);
        CellChecker(neighbors_counter, data[index++]);
        CellChecker(neighbors_counter, data[index]);

        index = i + m_current_state->DOWN_LEFT_INDEXING_OFFSET;
        CellChecker(neighbors_counter, data[index++]);
        CellChecker(neighbors_counter, data[index++]);
        CellChecker(neighbors_counter, data[index]);

        CellChecker(neighbors_counter, data[i-1]);
        CellChecker(neighbors_counter, data[i+1]);

        m_next_state->m_data[i] = 
                            (neighbors_counter & static_cast<uint8_t>(data[i])) ? cell_t::ALIVE : cell_t::DEAD;  
    }    
}
}

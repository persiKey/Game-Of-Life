#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <cstddef>


namespace GameOfLife
{
 
class IGOF
{
public:
    virtual ~IGOF() = default;
    virtual CheckBoard& Solve(CheckBoard& state,
                    uint64_t start_x,
                    uint64_t start_y,
                    uint64_t length_x,
                    uint64_t height_y); 
};
    
class GameOfLife
{
public:
    CheckBoard& GetCheckBoard();
    CheckBoard& NextStep();
    std::size_t GetCurrentStep();
private:
    CheckBoard m_checkboard;
    CheckBoard m_checkboard_buffer;
    std::size_t m_step;

};

}

#endif
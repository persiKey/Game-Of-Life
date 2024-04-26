#include <iostream>
#include <thread>


#include "GameOfLife.hpp"
#include "SequentialTorusGOFAlgorithm.hpp"
#include "FromFileFiller.hpp"
#include "VectorBorderCheckBoard.hpp"

void PrintCheckboard(const GameOfLife::ICheckBoard& checkboard)
{
    for (GameOfLife::index_t j = 0; j < checkboard.Height(); ++j)
    {
        for (GameOfLife::index_t i = 0; i < checkboard.Length(); ++i)
        {
            std::cout << ((checkboard.Get(i,j) == GameOfLife::cell_t::ALIVE) ? '*' : '.');
        }
        std::cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    using namespace GameOfLife;

    GOF<VectorBorderCheckBoard, SequentialTorusGOFAlgorithm> GameOfLife( 10,
                    8,
                    std::make_unique<FromFileFiller>(argv[1]));

    std::cout << "Generated\n";
    
    while (true)
    {

        PrintCheckboard(GameOfLife.GetCheckBoard());
        std::cout << "Step " << GameOfLife.GetCurrentStep() << '\n';
        //std::getchar();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);
        auto begin = std::chrono::system_clock::now();
        GameOfLife.NextStep();
        auto end = std::chrono::system_clock::now();
        std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds >(end - begin).count() << " ms \n";
    }

    return 0;
}
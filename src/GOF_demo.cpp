#include "GameOfLife.hpp"
#include <iostream>
#include <thread>
#include "SequentialTorusGOFAlgorithm.hpp"

#include "GameOfLife.hpp"

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

int main()
{
    using namespace GameOfLife;

    GOF GameOfLife( 70000,
                    20000,
                   std::move(std::unique_ptr<IBorderGOFAlgorithm>(new SequentialTorusGOFAlgorithm())),
                   std::unique_ptr<ICheckBoardFiller>(new RandomFiller(0.5)));

    std::cout << "Generated\n";
    while (true)
    {

        //PrintCheckboard(GameOfLife.GetCheckBoard());
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
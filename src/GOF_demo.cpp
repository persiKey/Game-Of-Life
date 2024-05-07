#include <iostream>
#include <thread>


#include "GameOfLife.hpp"
#include "SequentialTorusGOFAlgorithm.hpp"
#include "SequentialVectorTorusGOFAlgorithm.hpp"
#include "ParallelTorusAlgorithm.hpp"
#include "FromFileFiller.hpp"
#include "RandomFiller.hpp"
#include "VectorBorderCheckBoard.hpp"
#include "MatrixBorderCheckBoard.hpp"

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
    // SequentialVectorTorusGOFAlgorithm
    // ParallelTorusAlgorithm
    GOF<VectorBorderCheckBoard, ParallelTorusAlgorithm> GameOfLife(20000,
                    70000,
                    std::make_unique<RandomFiller>(0.3)
                    //std::make_unique<FromFileFiller>("F:/KPI/6th Sem/Parallel Computation Course Work/Game-Of-Life/GOF Patterns/glider.txt")
                    );

    std::cout << "Generated\n";
    
    while (true)
    {
        //system("cls");
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
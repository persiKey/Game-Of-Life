#include "GameOfLife.hpp"
#include "ParallelTorusAlgorithm.hpp"
#include "SequentialVectorTorusGOFAlgorithm.hpp"
#include "RandomFiller.hpp"
#include <iostream>
#include <chrono>
#include <array>

using namespace GameOfLife;

inline constexpr size_t WARMUP_ITERAIONS = 10'000'000'000;
inline constexpr size_t MEASURES = 20;

struct measure_t
{
    double mean;
    double deviation;
};

class LocalBenchmark
{
public:
    static void WarmUpAllLogicalCores()
    {
        std::cout << "Warm Up start\n";
        std::vector<std::thread> threads(std::thread::hardware_concurrency());

        for (auto& thread : threads)
        {
            thread = std::thread([]() {
                volatile size_t counter = 0;
                for (volatile size_t i = 0; i < WARMUP_ITERAIONS; i++)
                {
                    counter++;
                }
                });
        }


        for (auto& thread : threads)
        {
            thread.join();
        }
        std::cout << "Warm Up finished\n";
    }


    static measure_t Measure(std::unique_ptr<IVectorBorderGOFAlgorithm> algorithm,
                            std::shared_ptr<VectorBorderCheckBoard>& current_state,
                            std::shared_ptr<VectorBorderCheckBoard>& next_state)
    {
        measure_t result{};
        std::array<long long, MEASURES> measures{};
        
        double sum = 0;

        WarmUpAllLogicalCores();

        for(auto& measure : measures)
        {
            auto begin = std::chrono::system_clock::now();
            algorithm->Compute(current_state, next_state);
            auto end = std::chrono::system_clock::now();
            measure = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
            std::cout << "Measure finished: " << measure << " ms\n";
            sum += measure;
        }
        result.mean = sum / MEASURES;

        double differences_sum = 0;
        for(auto& measure : measures)
        {
            differences_sum += pow(result.mean - measure, 2);
        }
        result.deviation = sqrt(differences_sum/MEASURES);

        return result;
    }
};

int main()
{
    auto current_state = std::make_shared<VectorBorderCheckBoard>(20000, 70000);
    auto filler = std::make_unique<RandomFiller>(0.3);
    filler->Fill(current_state);
    auto next_state = std::make_shared<VectorBorderCheckBoard>(20000, 70000);

    auto measure = LocalBenchmark::Measure(std::make_unique<ParallelTorusAlgorithm>(5),
    current_state, next_state);

    std::cout << "Mean: " << measure.mean << " ms\n"
    << "Deviation: " << measure.deviation << " ms\n";
}


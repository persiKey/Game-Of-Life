#include "GameOfLife.hpp"
#include "ParallelTorusAlgorithm.hpp"
#include "SequentialVectorTorusGOFAlgorithm.hpp"
#include "RandomFiller.hpp"
#include <iostream>
#include <chrono>
#include <array>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <iterator>

using namespace GameOfLife;

inline constexpr size_t WARMUP_ITERATIONS = 2'000'000'000;
inline constexpr size_t MEASURES = 20;
inline constexpr size_t MINIMUM_MATRIX_SIZE = 1024ull * 1024ull * 1ull;
inline constexpr size_t MAXIMUM_MATRIX_SIZE = 1024ull * 1024ull * 1024ull * 4ull;

inline constexpr size_t CELL_WIDTH = 12;
inline constexpr size_t FIRST_COLUMN_WIDHT = 12;

inline constexpr char FILL = ' ';
inline constexpr char FIRST_COLUMN_SEPARATOR = ':';
inline constexpr char FIRST_ROW_SEPARATOR = '-';
inline constexpr char CELL_SEPARATOR = '|';
inline constexpr char INTERSECT = '+';

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
        //std::cout << "Warm Up start\n";
        std::vector<std::thread> threads(std::thread::hardware_concurrency());

        for (auto& thread : threads)
        {
            thread = std::thread([]() {
                volatile size_t counter = 0;
                for (volatile size_t i = 0; i < WARMUP_ITERATIONS; i++)
                {
                    counter++;
                }
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }
        //std::cout << "Warm Up finished\n";
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
            //std::cout << "Measure finished: " << measure << " ms\n";
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

class GlobalBenchmark
{
public:
    struct algorithm_info_t
    {
        std::unique_ptr<IVectorBorderGOFAlgorithm> implementation;
        std::string name;

        algorithm_info_t(std::unique_ptr<IVectorBorderGOFAlgorithm>&& implementation, std::string&& name)
        {
            this->implementation = std::move(implementation);
            this->name = std::move(name);
        }

        algorithm_info_t(algorithm_info_t&& other) = default;

        algorithm_info_t& operator=(algorithm_info_t&& other) = default;
    };

    static void Measure(std::initializer_list<algorithm_info_t> algorithms, std::vector<index_t> sizes)
    {
        using std::cout;
        for (auto& algorithm : algorithms)
        {
            cout << algorithm.name << '\n';

            cout << std::setfill(FILL);
            cout << std::setw(FIRST_COLUMN_WIDHT) << "" << FIRST_COLUMN_SEPARATOR;
            for ( const auto lenght : sizes )
            {
                cout << std::setw(CELL_WIDTH) << lenght << CELL_SEPARATOR;
            }
            cout << '\n';

            cout << std::setfill(FIRST_ROW_SEPARATOR) << std::setw(FIRST_COLUMN_WIDHT) << "" <<  INTERSECT;
            for ( const auto lenght : sizes )
            {
                cout << std::setw(CELL_WIDTH) << "" << FIRST_ROW_SEPARATOR;
            }
            cout << '\n';

            cout << std::setfill(FILL);
            for ( const auto height : sizes )
            {
                cout << std::setw(FIRST_COLUMN_WIDHT) << height << FIRST_COLUMN_SEPARATOR;
                for ( const auto lenght : sizes )
                {
                    cout << std::setw(CELL_WIDTH) << ((height * lenght <= MAXIMUM_MATRIX_SIZE) &&  (height * lenght >= MINIMUM_MATRIX_SIZE)  ? height * lenght : -0) << CELL_SEPARATOR;
                }
                cout << '\n';              
            }
            
        }
        
    }
};

int main()
{
    GlobalBenchmark::Measure(
        {
            {
                std::make_unique<SequentialVectorTorusGOFAlgorithm>(),
                std::string("Sequential")
            },
            {
                std::make_unique<ParallelTorusAlgorithm>(2),
                std::string("Parralel 2 t")
            }
        },
        {4, 100, 1000, 3'000, 20'000, 65'536, 70'000, 100'000, 250'000, 1'000'000'000}
    );

    return 0;
    auto current_state = std::make_shared<VectorBorderCheckBoard>(20000, 70000);
    auto filler = std::make_unique<RandomFiller>(0.3);
    filler->Fill(current_state);
    auto next_state = std::make_shared<VectorBorderCheckBoard>(20000, 70000);

    auto measure = LocalBenchmark::Measure(std::make_unique<ParallelTorusAlgorithm>(),
    current_state, next_state);

    std::cout << "Mean: " << measure.mean << " ms\n"
    << "Deviation: " << measure.deviation << " ms\n";
}


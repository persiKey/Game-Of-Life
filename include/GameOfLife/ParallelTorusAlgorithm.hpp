#ifndef PARALLEL_TORUS_ALGORITHM
#define PARALLEL_TORUS_ALGORITHM

#include "IGOFAlgorithm.hpp"
#include "SequentialVectorTorusGOFAlgorithm.hpp"
#include "VectorBorderCheckBoard.hpp"

#include <thread>
#include <atomic>
#include <vector>
#include <condition_variable>

namespace GameOfLife
{
    
inline index_t BLOCK_SIZE = 10;

class ParallelTaskExecutionPool
{
public:
    ParallelTaskExecutionPool(int thread_num);
    ~ParallelTaskExecutionPool();

    void Start(std::shared_ptr<VectorBorderCheckBoard>& current_state, 
                         std::shared_ptr<VectorBorderCheckBoard>& next_state);
    void Join();
private:
    void Worker(bool& is_finished);
    
    int m_threads_num;
    struct Task
    {
        std::thread task_thread;
        bool is_finished;
    };
    std::vector<Task> m_thread_pool;
    
    std::atomic<index_t> m_thread_task_index;
    
    volatile bool m_is_executing;
    std::mutex m_new_task_mutex;
    std::condition_variable m_new_task;

    std::mutex m_finish_mutex;
    std::condition_variable m_finish_task;

    int m_tasks_num;
    std::shared_ptr<VectorBorderCheckBoard> m_current_state;
    std::shared_ptr<VectorBorderCheckBoard> m_next_state;
};

class ParallelTorusAlgorithm : public SequentialVectorTorusGOFAlgorithm
{
public:
    ParallelTorusAlgorithm();
    ParallelTorusAlgorithm(int threads_num);
    ~ParallelTorusAlgorithm() override = default;

    void Compute(std::shared_ptr<VectorBorderCheckBoard>& m_current_state,
                 std::shared_ptr<VectorBorderCheckBoard>& m_next_state);
    
private:
    ParallelTaskExecutionPool m_pool;
};



} // namespace GameOfLife


#endif
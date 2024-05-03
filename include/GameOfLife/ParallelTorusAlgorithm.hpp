#ifndef PARALLEL_TORUS_ALGORITHM
#define PARALLEL_TORUS_ALGORITHM

#include "IGOFAlgorithm.hpp"
#include "SequentialVectorTorusGOFAlgorithm.hpp"
#include "VectorBorderCheckBoard.hpp"

#include <thread>
#include <atomic>
#include <vector>
#include <condition_variable>
#include <shared_mutex>

namespace GameOfLife
{
 
inline constexpr index_t L1_CACHE_SIZE = 1024 * 380;
inline constexpr index_t BLOCK_SIZE = L1_CACHE_SIZE;

class ParallelTaskExecutionPool
{
public:
    struct ITask
    {
        virtual ~ITask() = default;
        virtual void Execute() = 0;
    };

    ParallelTaskExecutionPool(int threads_num);
    ~ParallelTaskExecutionPool();

    void Start(std::unique_ptr<ITask> task);
    void Join();
private:
    void Worker(bool& is_finished);
    
    int m_threads_num;
    struct Executor
    {
        std::thread executor_thread;
        bool is_finished;
    };


    std::vector<Executor> m_thread_pool;
        
    volatile bool m_is_executing;
    std::shared_mutex m_new_task_mutex;
    std::condition_variable_any m_new_task;

    std::mutex m_finish_mutex;
    std::condition_variable m_finish_task;

    std::unique_ptr<ITask> m_task;
};

struct ParralelComputeTask : public ParallelTaskExecutionPool::ITask
{
    std::atomic<index_t> m_thread_task_index;

    int m_tasks_num;
    std::shared_ptr<VectorBorderCheckBoard> m_current_state;
    std::shared_ptr<VectorBorderCheckBoard> m_next_state;

    ParralelComputeTask(std::shared_ptr<VectorBorderCheckBoard> current_state,
        std::shared_ptr<VectorBorderCheckBoard> next_state)
        : m_thread_task_index(0),
        m_current_state(std::move(current_state)),
        m_next_state(std::move(next_state))
    {
        m_tasks_num = (m_current_state->Length() * m_current_state->Height()) / BLOCK_SIZE;
    }

    virtual void Execute() override
    {
        index_t current_index;
        while ((current_index = ++m_thread_task_index) <= m_tasks_num)
        {
            //std::cout << current_index << std::endl;
            const auto end = current_index * BLOCK_SIZE;
            const auto begin = end - BLOCK_SIZE;

            SequentialVectorTorusGOFAlgorithm::ComputeVectorChunk(begin, end, m_current_state, m_next_state);
        }
    }

};

class ParallelTorusAlgorithm : public IBorderGOFAlgorithm
{
public:
    ParallelTorusAlgorithm();
    ParallelTorusAlgorithm(int threads_num);
    ~ParallelTorusAlgorithm() override = default;

    void Compute(std::shared_ptr<VectorBorderCheckBoard>& m_current_state,
                 std::shared_ptr<VectorBorderCheckBoard>& m_next_state);

    virtual void Compute(std::shared_ptr<IBorderCheckBoard> m_current_state,
        std::shared_ptr<IBorderCheckBoard> m_next_state) override;
private:
    ParallelTaskExecutionPool m_pool;
};



} // namespace GameOfLife


#endif
#ifndef PARALLEL_TORUS_ALGORITHM
#define PARALLEL_TORUS_ALGORITHM

#include "IGOFAlgorithm.hpp"

#include "VectorBorderCheckBoard.hpp"

#include <thread>
#include <atomic>
#include <vector>
#include <semaphore>

namespace GameOfLife
{
 
inline constexpr index_t CHUNK_SIZE = 1024 * 1;

class ParallelTaskExecutionPool
{
public:
    class ITask
    {
    public:
        virtual ~ITask() = default;
        virtual void Execute() = 0;
    };

    ParallelTaskExecutionPool(int threads_num);
    ~ParallelTaskExecutionPool();

    void Start(std::unique_ptr<ITask> task);
    void Join();
private:
    void Worker();
    
    int m_threads_num;
    struct Executor
    {
        std::thread executor_thread;
    };

    std::vector<Executor> m_thread_pool;
       
    std::counting_semaphore<> m_working_threads;
    std::counting_semaphore<> m_finished_threads;

    std::atomic_bool m_is_executing;

    std::unique_ptr<ITask> m_task;
};

class ParralelComputeTask : public ParallelTaskExecutionPool::ITask
{
public:
    ParralelComputeTask(std::shared_ptr<VectorBorderCheckBoard> current_state,
        std::shared_ptr<VectorBorderCheckBoard> next_state, int tasks_num, index_t task_block);

    virtual void Execute() override;

private:
    std::shared_ptr<VectorBorderCheckBoard> m_current_state;
    std::shared_ptr<VectorBorderCheckBoard> m_next_state;
    int m_tasks_num;
    index_t m_task_block;
    std::atomic<index_t> m_thread_task_index;
};

class ParralelFillRowTask : public ParallelTaskExecutionPool::ITask
{
public:
    ParralelFillRowTask(std::shared_ptr<VectorBorderCheckBoard> current_state, int tasks_num, index_t task_block);
    virtual void Execute() override;

private:
    std::shared_ptr<VectorBorderCheckBoard> m_current_state;
    int m_tasks_num;
    index_t m_task_block;
    std::atomic<index_t> m_task_index;
};

class ParralelFillColumnTask : public ParallelTaskExecutionPool::ITask
{
public:
    ParralelFillColumnTask(std::shared_ptr<VectorBorderCheckBoard> current_state, int tasks_num, index_t task_block);
    virtual void Execute() override;

private:
    std::shared_ptr<VectorBorderCheckBoard> m_current_state;
    int m_tasks_num;
    index_t m_task_block;
    std::atomic<index_t> m_task_index;
};

class ParallelTorusAlgorithm : public IVectorBorderGOFAlgorithm
{
public:
    ParallelTorusAlgorithm();
    ParallelTorusAlgorithm(int threads_num);
    ~ParallelTorusAlgorithm() = default;

    virtual void Compute(std::shared_ptr<VectorBorderCheckBoard>& m_current_state,
                 std::shared_ptr<VectorBorderCheckBoard>& m_next_state) override;

private:
    ParallelTaskExecutionPool m_pool;
    int m_threads_num;
};



} // namespace GameOfLife

#endif
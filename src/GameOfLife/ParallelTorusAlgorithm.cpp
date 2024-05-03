#include "ParallelTorusAlgorithm.hpp"

#include <utility>

#include <iostream>

namespace GameOfLife
{

ParallelTaskExecutionPool::ParallelTaskExecutionPool(int threads_num)
: m_threads_num(threads_num),
  m_thread_task_index(0),
  m_thread_pool(threads_num),
  m_is_executing(false)
{
    for (int i = 0; i < m_threads_num; ++i)
    {
        m_thread_pool[i].task_thread = std::thread(&ParallelTaskExecutionPool::Worker, this,
                                                   std::ref(m_thread_pool[i].is_finished));
    }
}

ParallelTaskExecutionPool::~ParallelTaskExecutionPool()
{
    m_is_executing = false;
    m_new_task.notify_all();
}

void ParallelTaskExecutionPool::Start(std::shared_ptr<VectorBorderCheckBoard>& current_state,
    std::shared_ptr<VectorBorderCheckBoard>& next_state)
{
    m_current_state = current_state;
    m_next_state = next_state;
    
    m_thread_task_index = 0;
    m_tasks_num = (m_current_state->Length() * m_current_state->Height()) / BLOCK_SIZE;

    for (int i = 0; i < m_threads_num; ++i)
    {
        m_thread_pool[i].is_finished = false;
    }
    m_is_executing = true;
    m_new_task.notify_all();
}

void ParallelTaskExecutionPool::Join()
{
    for (int i = 0; i < m_threads_num; ++i)
    {
        std::unique_lock lk(m_finish_mutex);
        m_finish_task.wait(lk, [&]() {return m_thread_pool[i].is_finished; });
    }    
}

void ParallelTaskExecutionPool::Worker(bool& is_finished)
{
    index_t current_index;
    while (true)
    {
        std::shared_lock lk(m_new_task_mutex);
        m_new_task.wait(lk);

        if(!m_is_executing)
        {
            break;
        }

        while ((current_index = ++m_thread_task_index) <= m_tasks_num)
        {
            //std::cout << current_index << std::endl;
            const auto end = current_index * BLOCK_SIZE;
            const auto begin = end - BLOCK_SIZE;

            SequentialVectorTorusGOFAlgorithm::ComputeVectorChunk(begin, end, m_current_state, m_next_state);
        }

        is_finished = true;
        m_finish_task.notify_all();
    }
}

ParallelTorusAlgorithm::ParallelTorusAlgorithm()
: ParallelTorusAlgorithm(20
    //std::max(1u, std::thread::hardware_concurrency() - 2)
    )
{
    
}

ParallelTorusAlgorithm::ParallelTorusAlgorithm(int threads_num)
    : m_pool(threads_num)
{

}

void ParallelTorusAlgorithm::Compute(std::shared_ptr<VectorBorderCheckBoard>& m_current_state,
                                     std::shared_ptr<VectorBorderCheckBoard>& m_next_state)
{
    FillBorder(m_current_state);

    m_pool.Start(m_current_state, m_next_state);
    const auto tasks_num = (m_current_state->Length() * m_current_state->Height()) / BLOCK_SIZE;
    std::cout << tasks_num << std::endl;
    const auto end = m_current_state->Length() * m_current_state->Height();
    const auto begin = tasks_num * BLOCK_SIZE;

    SequentialVectorTorusGOFAlgorithm::ComputeVectorChunk(begin, end, m_current_state, m_next_state);
    
    m_pool.Join();
}

void ParallelTorusAlgorithm::Compute(std::shared_ptr<IBorderCheckBoard> m_current_state,
    std::shared_ptr<IBorderCheckBoard> m_next_state)
{
    std::cout << "I shouldn't be printed\n";
}

}

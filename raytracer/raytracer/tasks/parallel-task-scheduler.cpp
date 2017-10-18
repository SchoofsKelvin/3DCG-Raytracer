#include "tasks/parallel-task-scheduler.h"
#include <atomic>
#include <thread>
#include <vector>

using namespace tasks;


namespace
{
    /// <summary>
    /// Performs tasks one after the other (i.e. not in parallel).
    /// </summary>
    class ParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:
        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
			std::vector<std::thread> workers;
			for (auto task : tasks) {
				workers.push_back(std::thread([task]()
				{
					task->perform();
				}));
			}

			for (std::vector<std::thread>::iterator it = workers.begin(); it != workers.end(); ++it) {
				(*it).join();
			}
        }
    };
}

TaskScheduler tasks::schedulers::parallel()
{
    return TaskScheduler(std::make_shared<ParallelTaskScheduler>());
}

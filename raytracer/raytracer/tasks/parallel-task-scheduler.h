#pragma once

#include "tasks/task-scheduler.h"


namespace tasks
{
    namespace schedulers
    {
        /// <summary>
        /// Creates a scheduler that performs several tasks at once.
        /// </summary>
        TaskScheduler parallel();
    }
}
#pragma once

#include <array>
#include <cstdint>
#include <functional>

class Scheduler
{
public:
    struct Task
    {
        std::function<void()> callback;
        uint32_t intervalMs;
        uint32_t lastRunMs;
        bool active;
    };

    static constexpr std::size_t MAX_TASKS = 8;

    bool addTask(std::function<void()> callback, uint32_t intervalMs)
    {
        for (auto& task : m_tasks)
        {
            if (!task.active)
            {
                task = {std::move(callback), intervalMs, 0, true};
                return true;
            }
        }
        return false;
    }

    void run(uint32_t currentMs)
    {
        for (auto& task : m_tasks)
        {
            if (task.active && (currentMs - task.lastRunMs >= task.intervalMs))
            {
                task.callback();
                task.lastRunMs = currentMs;
            }
        }
    }

private:
    std::array<Task, MAX_TASKS> m_tasks{};
};
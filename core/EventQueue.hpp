#pragma once

#include <functional>
#include <variant>
#include <queue>
#include <cstddef>
#include <string_view>

struct ButtonPressed {};
struct UartMessage { std::string_view text; };

using Event = std::variant<ButtonPressed, UartMessage>;

class EventQueue
{
public:
    void push(Event event)
    {
        m_queue.push(std::move(event));
    }

    template<typename Handler>
    void process(Handler&& handler)
    {
        while (!m_queue.empty())
        {
            std::visit(handler, m_queue.front());
            m_queue.pop();
        }
    }

    std::size_t size() const
    {
        return m_queue.size();
    }

    bool empty() const
    {
        return m_queue.empty();
    }

private:
    std::queue<Event> m_queue;
};
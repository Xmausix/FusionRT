#include <gtest/gtest.h>
#include "../core/EventQueue.hpp"

TEST(EventQueue, InitiallyEmpty)
{
    EventQueue q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
}

TEST(EventQueue, PushButtonPressed)
{
    EventQueue q;
    q.push(ButtonPressed{});
    EXPECT_EQ(q.size(), 1u);
}

TEST(EventQueue, PushUartMessage)
{
    EventQueue q;
    q.push(UartMessage{"OK"});
    EXPECT_EQ(q.size(), 1u);
}

TEST(EventQueue, PushMultiple)
{
    EventQueue q;
    q.push(ButtonPressed{});
    q.push(UartMessage{"hello"});
    q.push(ButtonPressed{});
    EXPECT_EQ(q.size(), 3u);
}

TEST(EventQueue, ProcessClearsQueue)
{
    EventQueue q;
    q.push(ButtonPressed{});
    q.push(UartMessage{"test"});

    q.process([](const auto&) {});

    EXPECT_TRUE(q.empty());
}

TEST(EventQueue, ProcessCallsCorrectHandler)
{
    EventQueue q;
    q.push(ButtonPressed{});

    bool called = false;

    q.process([&](const auto& event)
    {
        using T = std::decay_t<decltype(event)>;
        if constexpr (std::is_same_v<T, ButtonPressed>)
        {
            called = true;
        }
    });

    EXPECT_TRUE(called);
}

TEST(EventQueue, ProcessUartMessage)
{
    EventQueue q;
    q.push(UartMessage{"hello"});

    std::string_view received;

    q.process([&](const auto& event)
    {
        using T = std::decay_t<decltype(event)>;
        if constexpr (std::is_same_v<T, UartMessage>)
        {
            received = event.text;
        }
    });

    EXPECT_EQ(received, "hello");
}

TEST(EventQueue, ProcessOrder)
{
    EventQueue q;
    q.push(ButtonPressed{});
    q.push(UartMessage{"first"});
    q.push(UartMessage{"second"});

    std::vector<std::string> order;

    q.process([&](const auto& event)
    {
        using T = std::decay_t<decltype(event)>;
        if constexpr (std::is_same_v<T, ButtonPressed>)
        {
            order.push_back("button");
        }
        else if constexpr (std::is_same_v<T, UartMessage>)
        {
            order.push_back(std::string(event.text));
        }
    });

    ASSERT_EQ(order.size(), 3u);
    EXPECT_EQ(order[0], "button");
    EXPECT_EQ(order[1], "first");
    EXPECT_EQ(order[2], "second");
}
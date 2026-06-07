#pragma once

#include <string_view>

class Uart;

class Logger
{
public:
    static void init(Uart& uart)
    {
        s_uart = &uart;
    }

    static void info(std::string_view msg)
    {
        log("[INFO] ", msg);
    }

    static void warn(std::string_view msg)
    {
        log("[WARN] ", msg);
    }

    static void error(std::string_view msg)
    {
        log("[ERROR] ", msg);
    }

private:
    static void log(std::string_view prefix, std::string_view msg)
    {
        if (s_uart == nullptr) return;

        s_uart->send(prefix);
        s_uart->send(msg);
        s_uart->send("\r\n");
    }

    static inline Uart* s_uart = nullptr;
};
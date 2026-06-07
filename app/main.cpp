#include "core/EventQueue.hpp"
#include "core/Logger.hpp"
#include "drivers/Led.hpp"
#include "drivers/Uart.hpp"
#include "drivers/Gpio.hpp"
#include "stm32f4xx_hal.h"

struct ButtonPressed {};
struct UartMessage { std::string_view text; };

int main()
{
    HAL_Init();

    EventQueue queue;
    Led statusLed(GPIOA, GPIO_PIN_5);
    Uart uart(115200);
    Gpio button(GPIOC, GPIO_PIN_13, Gpio::Mode::Input);

    Logger::init(uart);
    Logger::info("System started");

    uart.onReceive([&](std::string_view msg)
    {
        queue.push(UartMessage{msg});
    });

    while (true)
    {
        if (button.read() == Gpio::State::Low)
        {
            queue.push(ButtonPressed{});
            HAL_Delay(50);
        }

        queue.process([&](const auto& event)
        {
            using T = std::decay_t<decltype(event)>;

            if constexpr (std::is_same_v<T, ButtonPressed>)
            {
                Logger::info("Button pressed");
                statusLed.toggle();
                uart.send("Button event\r\n");
            }
            else if constexpr (std::is_same_v<T, UartMessage>)
            {
                Logger::info("UART received");
                uart.send("Echo: ");
                uart.send(event.text);
            }
        });
    }
}
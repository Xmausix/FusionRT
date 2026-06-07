#pragma once

#include "Gpio.hpp"

class Led
{
public:
    Led(GPIO_TypeDef* port, uint16_t pin)
        : m_gpio(port, pin, Gpio::Mode::Output)
    {
    }

    void on()
    {
        m_gpio.write(Gpio::State::High);
    }

    void off()
    {
        m_gpio.write(Gpio::State::Low);
    }

    void toggle()
    {
        m_gpio.toggle();
    }

private:
    Gpio m_gpio;
};
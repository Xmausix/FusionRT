#pragma once

#include "stm32f4xx_hal.h"

class Gpio
{
public:
    enum class Mode
    {
        Input,
        Output
    };

    enum class State
    {
        Low,
        High
    };

    Gpio(GPIO_TypeDef* port, uint16_t pin, Mode mode)
        : m_port(port)
        , m_pin(pin)
    {
        GPIO_InitTypeDef init{};
        init.Pin  = pin;
        init.Mode = (mode == Mode::Output) ? GPIO_MODE_OUTPUT_PP : GPIO_MODE_INPUT;
        init.Pull = GPIO_NOPULL;
        init.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(port, &init);
    }

    void write(State state)
    {
        HAL_GPIO_WritePin(m_port, m_pin,
            (state == State::High) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    State read() const
    {
        return (HAL_GPIO_ReadPin(m_port, m_pin) == GPIO_PIN_SET)
            ? State::High
            : State::Low;
    }

    void toggle()
    {
        HAL_GPIO_TogglePin(m_port, m_pin);
    }

private:
    GPIO_TypeDef* m_port;
    uint16_t      m_pin;
};
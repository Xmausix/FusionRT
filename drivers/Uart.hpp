#pragma once

#include "stm32f4xx_hal.h"
#include <functional>
#include <string_view>
#include <cstring>

class Uart
{
public:
    explicit Uart(uint32_t baudrate)
    {
        m_handle.Instance        = USART2;
        m_handle.Init.BaudRate   = baudrate;
        m_handle.Init.WordLength = UART_WORDLENGTH_8B;
        m_handle.Init.StopBits   = UART_STOPBITS_1;
        m_handle.Init.Parity     = UART_PARITY_NONE;
        m_handle.Init.Mode       = UART_MODE_TX_RX;
        m_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        HAL_UART_Init(&m_handle);
    }

    void send(std::string_view data)
    {
        HAL_UART_Transmit(&m_handle,
            reinterpret_cast<const uint8_t*>(data.data()),
            static_cast<uint16_t>(data.size()),
            HAL_MAX_DELAY);
    }

    void onReceive(std::function<void(std::string_view)> callback)
    {
        m_callback = std::move(callback);
        HAL_UART_Receive_IT(&m_handle, &m_rxByte, 1);
    }

    void handleIRQ()
    {
        HAL_UART_IRQHandler(&m_handle);
    }

    void rxComplete()
    {
        if (m_rxIndex < RX_BUFFER_SIZE - 1)
        {
            if (m_rxByte == '\n')
            {
                m_rxBuffer[m_rxIndex] = '\0';

                if (m_callback)
                {
                    m_callback(std::string_view(m_rxBuffer, m_rxIndex));
                }

                m_rxIndex = 0;
            }
            else
            {
                m_rxBuffer[m_rxIndex++] = m_rxByte;
            }
        }
        else
        {
            m_rxIndex = 0;
        }

        HAL_UART_Receive_IT(&m_handle, &m_rxByte, 1);
    }

private:
    static constexpr std::size_t RX_BUFFER_SIZE = 128;

    UART_HandleTypeDef                   m_handle{};
    std::function<void(std::string_view)> m_callback;
    uint8_t                              m_rxByte{};
    char                                 m_rxBuffer[RX_BUFFER_SIZE]{};
    std::size_t                          m_rxIndex{0};
};
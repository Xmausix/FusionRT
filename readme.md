# FusionRT

Modern C++ Embedded Framework for STM32 Microcontrollers

## Overview

EmbeddedCore is a lightweight embedded framework written in modern C++20 designed for STM32 microcontrollers. The project focuses on clean architecture, hardware abstraction, event-driven communication, and testability.

The goal of the project is to provide reusable building blocks for embedded applications while demonstrating modern C++ techniques commonly used in professional firmware development.

## Features

### Core Components

* Event Queue
* Logger
* Scheduler
* Hardware Abstraction Layer (HAL Wrappers)

### Drivers

* GPIO Driver
* LED Driver
* UART Driver

### Development Features

* Modern C++20
* Unit Testing Support
* CMake Build System
* Modular Architecture
* Platform Independent Core Logic

## Architecture

```text
Application
    │
    ▼
 Event Queue
    │
    ▼
 Drivers Layer
    │
    ▼
 STM32 HAL
    │
    ▼
 Hardware
```

The application communicates through events rather than direct dependencies between modules.

## Example

```cpp
Led statusLed(GPIOA, GPIO_PIN_5);

statusLed.on();

Logger::info("System started");

eventQueue.push(ButtonPressed{});
```

## Project Structure

```text
EmbeddedCore/
│
├── app/
│   └── main.cpp
│
├── core/
│   ├── EventQueue.hpp
│   ├── Logger.hpp
│   └── Scheduler.hpp
│
├── drivers/
│   ├── Gpio.hpp
│   ├── Led.hpp
│   └── Uart.hpp
│
├── tests/
│
├── docs/
│
└── CMakeLists.txt
```

## Current MVP Scope

* [x] GPIO abstraction
* [x] LED driver
* [x] UART wrapper
* [x] Event Queue
* [x] Logger
* [ ] Scheduler
* [ ] Unit Tests
* [ ] FreeRTOS Integration
* [ ] SPI Driver
* [ ] I2C Driver

## Build

```bash
mkdir build
cd build

cmake ..
cmake --build .
```

## Future Roadmap

### Version 0.2

* Scheduler
* State Machine Module
* Dependency Injection

### Version 0.3

* FreeRTOS Integration
* Message Bus
* Software Timers

### Version 0.4

* SPI Driver
* I2C Driver
* DMA Support

### Version 1.0

* Complete Embedded Framework
* Documentation
* Unit Test Coverage > 80%
* CI/CD Pipeline

## Motivation

This project is part of my embedded software engineering portfolio and serves as a playground for experimenting with firmware architecture, embedded design patterns, and modern C++ development practices.

## License

MIT License

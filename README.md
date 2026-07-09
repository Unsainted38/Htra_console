# Htra_console

C++/Qt console service for spectrum analyzer control, telemetry publishing and command processing.

## Overview

`Htra_console` is a console service for controlling a spectrum analyzer device and exposing measurement data to external systems.

The service is designed for hardware-oriented applications where a C++/Qt application communicates with measurement equipment, processes device data, builds telemetry packets and provides command/control interfaces for integration with other software components.

The project can be reviewed as an example of Qt-based service architecture for hardware control, telemetry, device abstraction and mock-based development without physical hardware.

## Features

* Spectrum analyzer device initialization and configuration
* Periodic measurement and control logic
* Telemetry data collection and publishing
* Command processing for external control
* Device abstraction through interface-based design
* Mock device mode for development without real hardware
* Qt-based console service architecture
* Integration with external hardware SDK/API
* Reusable components from `common_lib`

## Tech Stack

* C++17
* Qt Core
* Qt Network
* Qt SerialPort
* qmake
* Linux
* Windows
* External spectrum analyzer SDK/API
* FFTW / Liquid DSP dependencies for hardware-specific builds

## Project Structure

```text
Htra_console/
├── builders/                  # Telemetry packet builders
├── devices/                   # Device interfaces and mock device implementation
├── dto/                       # Data transfer objects
├── providers/                 # Telemetry data providers
├── telemetry/                 # Telemetry server components
├── third_party/
│   └── common_lib/             # Shared C++/Qt library as a git submodule
├── htra_proxy_server.*         # Proxy/server layer
├── htra_server_main_timer.*    # Timer-based service control flow
├── switcher_processor.*        # Switching and processing logic
├── main.cpp                   # Application entry point
├── htra_console.pro            # qmake project file
└── README.md
```

## Architecture

```text
External client / control system
        ↓
Proxy server / command layer
        ↓
Service control flow
        ↓
Telemetry provider / packet builder
        ↓
Device abstraction
        ↓
Real spectrum analyzer device or mock device
```

Main components:

* `htra_proxy_server` — proxy/server layer for external interaction.
* `htra_server_main_timer` — timer-based control flow for periodic service operations.
* `switcher_processor` — switching and measurement workflow logic.
* `devices/i_htra_device` — common interface for real and mock device implementations.
* `devices/mock_htra_device` — mock implementation for development without hardware.
* `providers/htra_telemetry_provider` — telemetry data provider.
* `builders/htra_packet_builder` — telemetry packet builder.
* `telemetry/htra_telemetry_server` — telemetry publishing component.

## Dependency: common_lib

This repository uses `common_lib` as a git submodule.

`common_lib` provides reusable C++/Qt components for:

* network transport;
* serial transport;
* request/response processing;
* command parsing;
* device abstractions;
* telemetry-related utilities;
* protocol-related helpers.

Expected repository structure after cloning with submodules:

```text
Htra_console/
├── third_party/
│   └── common_lib/
└── htra_console.pro
```

## Clone

Clone the repository with submodules:

```bash
git clone --recurse-submodules https://github.com/Unsainted38/Htra_console.git
cd Htra_console
```

If the repository was already cloned without submodules, initialize them manually:

```bash
git submodule update --init --recursive
```

## Mock Mode

The project supports mock mode for development and code review without access to the real hardware SDK.

When `htra_mock` is enabled, the project uses `MockHtraDevice` instead of the real device implementation. This allows the service architecture, telemetry flow and command processing logic to be reviewed without a connected spectrum analyzer.

Enable mock mode with:

```bash
qmake "CONFIG+=htra_mock" htra_console.pro
```

When mock mode is enabled, the build defines:

```qmake
DEFINES += HTRA_MOCK
```

Mock mode is the recommended build mode for portfolio review if the real hardware SDK is not available.

## Build

### Common Dependencies

* Qt 5 or Qt 6
* C++17-compatible compiler
* qmake

### Hardware-Specific Dependencies

Real hardware mode may require:

* HTRA / spectrum analyzer SDK
* FFTW
* Liquid DSP
* libusb

The exact dependency set depends on the target platform and whether the project is built with the real hardware API or in mock mode.

## Build in Mock Mode

### 1. Build common_lib

```bash
cd third_party/common_lib
qmake common_lib.pro
make
```

### 2. Build Htra_console

```bash
cd ../..
qmake "CONFIG+=htra_mock" htra_console.pro
make
```

## Build with Real Hardware SDK

Real hardware mode requires the spectrum analyzer SDK/API and related dependencies to be installed locally.

The project may require an `INC_PATH` variable or equivalent local SDK configuration depending on the development environment.

Example:

```bash
qmake htra_console.pro
make
```

If the hardware SDK is not available, use mock mode instead:

```bash
qmake "CONFIG+=htra_mock" htra_console.pro
make
```

## Configuration Notes

The project is intended to be used as part of a larger hardware-oriented software stack. Some paths to shared libraries and SDK files may need to be adjusted for a local development environment.

Production configuration files and hardware-specific deployment settings are not included in this repository.

For portfolio/code review purposes, the most important parts of the project are:

* service architecture;
* device abstraction;
* telemetry data flow;
* mock device support;
* Qt-based command/control structure;
* integration with reusable `common_lib` components.

## Example Usage Scenario

A typical use case:

1. The service starts as a console Qt application.
2. The device layer initializes either a real spectrum analyzer or a mock implementation.
3. The timer-based control flow periodically requests or updates measurement data.
4. The telemetry provider collects current device state and measurement values.
5. The packet builder converts telemetry data into an output format.
6. The telemetry server publishes data to an external system.
7. External commands are processed through the proxy/server layer.

## What I Implemented

* Designed the Qt-based console service structure.
* Implemented the hardware control flow around a spectrum analyzer device.
* Added device abstraction to separate real hardware access from mock implementation.
* Implemented telemetry provider and telemetry packet builder components.
* Added timer-based service logic for periodic control and measurement operations.
* Integrated external hardware API calls into the service architecture.
* Added mock mode to allow development and review without physical hardware.
* Integrated the project with reusable components from `common_lib`.

## Known Limitations

* The project currently uses qmake.
* Some hardware-specific dependencies are not included in the repository.
* Real hardware mode requires access to the spectrum analyzer SDK/API.
* Build paths may need to be adapted for a local environment.
* Mock mode is intended for architecture review and development without hardware.
* CMake support and a standalone demo configuration may be added later.

## Repository Purpose

This repository demonstrates experience with:

* C++/Qt service development;
* hardware control software;
* telemetry architecture;
* command processing;
* Linux-oriented console applications;
* external hardware SDK integration;
* mock-based hardware abstraction;
* separating production hardware logic from test/demo implementations;
* integration with reusable C++/Qt libraries.

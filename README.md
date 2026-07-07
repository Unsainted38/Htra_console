# Htra_console

C++/Qt console service for spectrum analyzer control, telemetry publishing and command processing.

## Overview

`Htra_console` is a console service for controlling a spectrum analyzer device and exposing measurement data to external systems.

The service is designed for hardware-oriented applications where a C++/Qt application communicates with measurement equipment, processes device data, builds telemetry packets and provides command/control interfaces for integration with other software components.

The project can be reviewed as an example of a Qt-based service architecture for hardware control, telemetry and device abstraction.

## Features

* Spectrum analyzer device initialization and configuration
* Periodic measurement and control logic
* Telemetry data collection and publishing
* Command processing for external control
* Device abstraction through interface-based design
* Mock device mode for development without real hardware
* Qt-based console service architecture
* Integration with external hardware SDK/API

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
├── builders/              # Telemetry packet builders
├── devices/               # Device interfaces and mock device implementation
├── dto/                   # Data transfer objects
├── providers/             # Telemetry data providers
├── telemetry/             # Telemetry server components
├── htra_proxy_server.*    # Proxy/server layer
├── htra_server_main_timer.* # Timer-based service control flow
├── switcher_processor.*   # Switching and processing logic
├── main.cpp               # Application entry point
└── htra_console.pro       # qmake project file
```

## Architecture

The service is split into several logical layers:

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
* `switcher_processor` — processing logic for switching and measurement workflow.
* `devices/i_htra_device` — common interface for real and mock device implementations.
* `devices/mock_htra_device` — mock implementation for development without hardware.
* `providers/htra_telemetry_provider` — telemetry data provider.
* `builders/htra_packet_builder` — telemetry packet builder.
* `telemetry/htra_telemetry_server` — telemetry publishing component.

## Mock Mode

The project supports mock mode for development and code review without access to the real hardware SDK.

When `htra_mock` is enabled, the project uses `MockHtraDevice` instead of the real device implementation. This allows the service architecture, telemetry flow and command processing logic to be reviewed without a connected spectrum analyzer.

In the current qmake configuration, mock mode is enabled for macOS builds and can also be enabled manually by adding:

```qmake
CONFIG += htra_mock
```

When mock mode is enabled, the build defines:

```qmake
DEFINES += HTRA_MOCK
```

## Build

### Dependencies

Common dependencies:

* Qt 5 or Qt 6
* C++17-compatible compiler
* qmake

Hardware-specific dependencies:

* HTRA / spectrum analyzer SDK
* FFTW
* Liquid DSP
* libusb

The exact set of dependencies depends on the target platform and whether the project is built with the real hardware API or in mock mode.

### Build with qmake

```bash
qmake htra_console.pro
make
```

### Mock build

If the hardware SDK is not available, build the project in mock mode:

```bash
qmake "CONFIG+=htra_mock" htra_console.pro
make
```

## Configuration Notes

The project is intended to be used as part of a larger hardware-oriented software stack. Some paths to shared libraries and SDK files may need to be adjusted for a local development environment.

For portfolio/code review purposes, the most important parts of the project are:

* service architecture;
* device abstraction;
* telemetry data flow;
* mock device support;
* Qt-based command/control structure.

## What I Implemented

* Designed the Qt-based console service structure.
* Implemented the hardware control flow around a spectrum analyzer device.
* Added device abstraction to separate real hardware access from mock implementation.
* Implemented telemetry provider and telemetry packet builder components.
* Added timer-based service logic for periodic control and measurement operations.
* Integrated external hardware API calls into the service architecture.
* Added mock mode to allow development and review without physical hardware.

## Known Limitations

* The project currently uses qmake.
* Some hardware-specific dependencies are not included in the repository.
* Real hardware mode requires access to the spectrum analyzer SDK/API.
* Build paths may need to be adapted for a local environment.
* CMake support and a standalone demo configuration may be added later.

## Repository Purpose

This repository demonstrates experience with:

* C++/Qt service development;
* hardware control software;
* telemetry architecture;
* command processing;
* Linux-oriented console applications;
* working with external hardware SDKs;
* separating production hardware logic from mock implementations.

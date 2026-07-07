# Htra_console

C++/Qt console service for controlling a spectrum analyzer device, processing measurement data and exposing telemetry/RPC command interfaces.

## Overview

The service communicates with measurement hardware, processes device data and provides command/telemetry interfaces for integration with external systems.

## Features

- Device initialization and configuration
- Periodic measurement processing
- RPC command handling
- Telemetry publishing
- Timer-based control logic
- Integration with external device API

## Tech Stack

- C++
- Qt Core
- Qt Network
- Qt SerialPort
- Device API integration
- Linux

## Architecture

- `htra_proxy_server` — proxy server layer.
- `hrtta_processor` — measurement processing logic.
- `signalhound_telemetry_server` — telemetry interface.
- `signalhound_server_main_timer` — timer-based control flow.
- `signalhaund_server_rpc_cmd_server` — RPC command handling.

## What I implemented

- Implemented the service structure and device control logic.
- Added telemetry server components.
- Implemented RPC command processing.
- Added timer-based measurement flow.
- Integrated external device API calls into Qt-based service logic.

## Dependencies

Some hardware-specific APIs are required to build and run the project. If the hardware SDK is unavailable, the project can be reviewed as an example of Qt-based service architecture for device control and telemetry.

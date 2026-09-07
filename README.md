# Pomodoro

A lightweight, always-on-top desktop Pomodoro timer built with C++ and SFML, featuring a transparent, borderless, click-through overlay window.

## Table of Contents
- [Overview](#overview)
- [TechStack](#techstack)
- [Features](#features)
- [Requirements](#requirements)
    - [Installation](#installation)

## Overview
Pomodoro is a minimal desktop widget that sits on top of your other windows and helps you run work/break cycles using the Pomodoro technique. It's built as a frameless, transparent overlay that only intercepts mouse clicks over its own UI, so it stays out of your way otherwise. It includes a Timer screen for running the countdown and a Settings screen for configuring work/break durations, autostart behavior, and alert volume.

## TechStack
<p align="center"> <img src=https://skillicons.dev/icons?i=cpp,cmake /> </p>

## Features
- **Countdown Timer**: Tracks work and break sessions down to the second, using a real-time accumulator so it stays accurate even when the app is idle in the background.
- **Work/Break Cycling**: Automatically switches between work and break phases when the countdown reaches zero.
- **Configurable Settings**: Adjustable work duration, break duration, autostart toggles for each phase, and an audio volume slider.
- **Audio Alerts**: Plays a sound when a session ends, respecting the configured volume.
- **Transparent Overlay Window**: Frameless, always-on-top, click-through window that only captures input over its own buttons and controls.
- **Draggable UI**: Move the widget anywhere on screen via a dedicated move handle.
- **Hide Toggle**: Collapse the widget down to a minimal state when you don't need the full UI visible.

## Requirements
- A C++ compiler with C++17 (or later) support
- [SFML 3](https://www.sfml-dev.org/)
- CMake (or your preferred build system configured to link `sfml-graphics`, `sfml-window`, `sfml-system`, and `sfml-audio`)
- Windows (the overlay/transparency and click-through behavior rely on the Win32 API and `dwmapi.lib`)
### Installation
1. Clone the repository:
```bash
    git clone https://github.com/yourusername/pomodoro.git
    cd pomodoro
```
2. Make sure SFML 3 is installed and discoverable by your build system (via `find_package(SFML ...)` or your linker's library paths).
3. Configure and build:
```bash
    cmake -B build
    cmake --build build
```
4. Run the executable from the build output directory. The app will appear as a small overlay in the top-right corner of your screen.

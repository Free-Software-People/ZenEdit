# ZenEdit Developer Guide

## Architecture
ZenEdit is a single-window application inheriting from `QMainWindow`. It uses a `QTextEdit` as the central widget for text manipulation.

## Build System
The project uses **Meson** and **Ninja**.
- `meson.build`: Defines the project configuration, dependencies (Qt5), and build targets.
- `src/main.cpp`: Entry point of the application.
- `src/zenedit.h/cpp`: Main application logic and UI setup.

## Contributing
1. Implement the feature.
2. Ensure the code follows the existing minimalist style.
3. Verify the build using `ninja -C build`.

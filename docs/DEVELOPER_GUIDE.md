# ZenEdit Developer Guide

ZenEdit is a minimalist, distraction-free text editor built with C++ and the Qt Framework. This guide provides a comprehensive technical deep dive into its architecture, build system, and development workflow.

## Project Structure

```text
ZenEdit/
├── build/              # Build artifacts (objects, moc files, binary)
├── docs/               # Documentation
│   ├── DEVELOPER_GUIDE.md
│   └── USER_GUIDE.md
├── src/                # Source code
│   ├── main.cpp        # Application entry point
│   ├── zenedit.h       # ZenEdit class declaration
│   └── zenedit.cpp     # ZenEdit class implementation
└── Makefile            # Build configuration
```

## Architecture

### Core Component: `ZenEdit` Class
The application is centered around the `ZenEdit` class, which inherits from `QMainWindow`.

- **UI Layout**: It uses a `QVBoxLayout` within a central `QWidget` to hold a `QTextEdit` instance. The margins and spacing are set to zero to ensure the editor occupies the entire window, providing a seamless "Zen" experience.
- **The Editor**: `QTextEdit` is used for the main text area. It provides built-in support for plain text editing and maintains its own undo/redo stack, which ZenEdit exposes via the Edit menu.
- **State Management**: The class tracks the `currentFile` as a `QString`. If this string is empty, the editor is considered to be in an "unsaved" state.

### Signal and Slot Mechanism
ZenEdit relies on Qt's Signal and Slot mechanism for event-driven communication.
- **Signals**: Emitted by Qt widgets (e.g., `QAction::triggered`).
- **Slots**: Member functions of `ZenEdit` that respond to signals.
- **Connection**: The `connect()` function binds a signal to a slot. For example:
  `connect(openAction, &QAction::triggered, this, &ZenEdit::openFile);`
  This means whenever the `openAction` is triggered, the `openFile` method of the current `ZenEdit` instance is executed.

### Memory Management
ZenEdit utilizes Qt's parent-child object hierarchy for automatic memory management.
- **Ownership**: When a `QObject` (or derivative like `QWidget`) is created with another `QObject` as its parent, the parent takes ownership.
- **Automatic Deletion**: When the parent object is deleted, it automatically deletes all its children. In `ZenEdit`, the `QMainWindow` is the top-level parent; most widgets created within its constructor (like `centralWidget` and `editor`) are passed `this` as the parent, ensuring they are cleaned up when the window is closed.

### Key Functionalities
- **File I/O**: 
    - `openFile()`: Uses `QFileDialog` to select a file and `QTextStream` to read its contents into the editor.
    - `saveFile()`: Writes the current editor text to `currentFile`. If no file is open, it redirects to `saveAsFile()`.
    - `saveAsFile()`: Prompts the user for a filename and saves the content, updating the `currentFile` state.
    - `revertFile()`: Reloads the `currentFile` from disk, effectively discarding all unsaved changes since the last save/open.
- **Undo/Redo**: These are thin wrappers around `QTextEdit::undo()` and `QTextEdit::redo()`.
- **Styling**: `applyStyle()` uses Qt Style Sheets (QSS), a CSS-like syntax, to define the visual appearance of the window, menus, and editor. This ensures a consistent, minimalist aesthetic across platforms.

### Error Handling
Error handling is currently implemented using modal dialogs via `QMessageBox::critical`. This provides immediate, blocking feedback to the user when critical operations (like opening or saving a file) fail.

## Build System

The project uses a standard **Makefile** and depends on **Qt 5** and **pkg-config**.

### The Qt MOC Process
Because `ZenEdit` uses the `Q_OBJECT` macro (required for signals and slots), it must be processed by the **Meta-Object Compiler (moc)**.
1. `moc` reads `zenedit.h` and generates a C++ source file (`moc_zenedit.cpp`).
2. This generated file is compiled into an object file (`moc_zenedit.o`).
3. The object file is linked with the rest of the application.

### Makefile Targets
- `make build`: Performs a full compilation.
    - Compiles `main.cpp` and `zenedit.cpp`.
    - Runs `moc` on `zenedit.h`.
    - Links all objects and Qt libraries (`Qt5Widgets`, `Qt5Gui`, `Qt5Core`) into the `ZenEdit` binary.
- `make run`: Builds the project (if necessary) and executes the binary.
- `make clean`: Removes the `build/` directory and the final binary.
- `make test`: Current placeholder for automated tests.

### Dependencies
- **Compiler**: `g++` (C++17 support required).
- **Libraries**: Qt 5 Widgets, Gui, and Core.
- **Tools**: `make`, `pkg-config`, and `moc`.

## Development Workflow

### Adding a New Feature
To add a new feature (e.g., a new menu action):
1. **Declare the Slot**: Add a `private slot` function declaration in `zenedit.h`.
2. **Implement the Logic**: Write the function implementation in `zenedit.cpp`.
3. **Update the UI**: 
    - In `createMenus()` or `createEditMenu()`, create a new `QAction`.
    - Connect the action's `triggered` signal to your new slot using `connect()`.
    - Assign a shortcut using `setShortcut(QKeySequence::...)` if applicable.
4. **Build and Verify**: Run `make build` and launch the application to test.

### Styling Guidelines
To modify the look and feel, edit the `applyStyle()` method. Focus on maintaining the minimalist palette:
- Backgrounds: Soft whites/greys (`#f5f5f5`, `#fdfdfd`).
- Text: Dark greys (`#333333`).
- Borders: Subtle lines (`#ddd`).
- Font: Monospaced for the editor (e.g., 'Courier New').

## Future Roadmap
Suggested areas for improvement:
- **Syntax Highlighting**: Integrate `QSyntaxHighlighter` to support various programming languages.
- **Tabbed Interface**: Replace the single `QTextEdit` with a `QTabWidget` to allow editing multiple files simultaneously.
- **Line Numbers**: Implement a side gutter to display line numbers.
- **Auto-Save**: Add a timer-based auto-save mechanism to prevent data loss.
- **Search and Replace**: Implement a search dialog using `QTextDocument::find`.

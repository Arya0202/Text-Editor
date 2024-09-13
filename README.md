# Text Editor in C++

## Overview
This project is a **Text Editor** developed in C++ that allows users to perform various text editing operations, such as inserting, deleting, swapping, and replacing lines. The application also provides functionalities to undo and redo changes, and save the text to a file. The editor is secured with a password and runs in a command-line interface (CLI) environment with a menu-driven approach.

## Features
- **Password Protection**: Ensures only authorized access to the editor.
- **Text Editing Options**:
  - Insert text into a specific line.
  - Delete a specific line.
  - Swap two lines.
  - Replace text in a specific line.
  - Print all text.
  - Save text to a file.
- **Undo/Redo Functionality**: Supports undo and redo of operations.
- **Console Customization**: Custom colors and title for the console window.
- **User-Friendly Interface**: Simple, menu-driven interaction.

## Implementation Details
The project is implemented using:
- **C++ Standard Library**: For standard input/output and data structures.
- **Windows Console Functions**: For custom cursor positioning (`gotoxy`), setting console colors, and clearing the screen.
- **Linked List**: Used to store and manage the text lines dynamically.
- **Stack**: Used to implement undo and redo functionality.

## Code Structure
- **`printChar(char ch, int n)`**: Function to print a character `ch`, `n` times.
- **`title()`**: Function to display the title screen.
- **`gotoxy(int x, int y)`**: Function to position the cursor at `(x, y)` coordinates in the console.
- **`undoCmd` Class**: Defines the structure for undo commands.
- **`node` Class**: Represents each line of text as a node in a linked list.
- **`linked_list` Class**: Implements the linked list for storing text lines, and supports various text operations like insertion, deletion, swapping, and replacing.

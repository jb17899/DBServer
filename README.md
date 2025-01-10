# DBServer

**Overview**

This project is a lightweight key-value pair database written in C. It is designed to provide basic functionality for storing, retrieving, and managing data efficiently. The implementation is suitable for learning purposes, embedded systems, or small-scale applications that require fast and simple data storage.

**Features**

- **In-Memory Storage**: Stores key-value pairs in memory for quick access.
- **Persistence**: Option to save data to a file for persistence across sessions.
- **CRUD Operations**: Support for Create, Read, Update, and Delete operations.
- **Customizable Data Types**: Keys and values can be strings or integers.
- **Efficient Lookup**: Uses hash tables for fast retrieval.
- **Thread-Safe**: Optional thread-safety mechanisms (e.g., mutex locks).

# Getting Started

## Prerequisites

To build and run this project, you will need:

- A C compiler (e.g., GCC, Clang).
- A POSIX-compliant system (Linux, macOS) or Windows with a compatible development environment.
- A tree-based structure built in `tree.c` for advanced operations.
- Server functionality for handling client requests.
- A custom query language supporting `insert`, `select`, `delete`, and `create`.

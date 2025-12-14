# Indexed-File-Database-Management-System-with-Cpp-Templates

This project implements a simple, template-based C++ database system that manages records stored in a binary file. It uses an in-memory index (a vector of file positions) to allow for efficient record retrieval, sorting, and manipulation without reading the entire data file into memory.

The records are managed using classes in an inheritance hierarchy (e.g, Personal and Student), demonstrating object-oriented principles applied to file I/O. The database utilizes binary search on the sorted index for fast lookups (find operation).

# Features
- Template-Based Database (Database<T>): Allows the database to store any record type (T) that implements the required file I/O, sizing, and comparison methods.

- Inheritance Hierarchy: Currently Implements Personal (base class) and Student (derived class) to handle different data structures while reusing base functionality.

- Indexed Access: Uses a vector<streampos> to build an index mapping record positions in the file to a sorted order (based on SSN/key).

- Efficient Search: Implements binary search (find) on the in-memory index for fast record lookup.

- CRUD Operations: Supports Create (add), Read (find, print), Update (modify), and Delete (remove).

- Physical Deletion (on destructor): Records are soft-deleted by marking them as null (e.g., changing the SSN) during remove. A cleanup/compacting operation is performed in the Database destructor (~Database) to remove null/marked records and rebuild a clean data file.

- Binary File I/O: Records are written to and read from a binary file to maintain a compact, persistent storage format.

# Key Classes and Files
- personal.h/personal.cpp: Base class for a person's record, defining basic attributes, comparison logic (based on SSN), and binary/console I/O methods.

- student.h/student.cpp: Derived class from Personal, adding a major field and extending the I/O and comparison logic.

- database.h/database.cpp: The template class Database<T> that manages the file, the index, and all core operations. It includes the main function to run the application with Database<Student>.

# How To Run
1. Compile all .cpp files (personal.cpp, student.cpp, database.cpp).

2. Execute the resulting binary.

3. The application will prompt for a filename and then present a menu for operations (Add, Find, Modify, Remove, Exit).

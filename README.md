# Encrpytion/Decryption Application

# Encoder
1) insert msg into square grid
2) follow specific diamond traversal pattern:
    - starting @ middle cel of leftmost col,
    - msg is written diagonally downwards to the right edge, forming a diamond shape.
3) once the outermost diamond is filled, process repeats inwardly with successfively smaller diamonds until the msg ends.
4) any remaining empty cells (either outside or isnide the final diamond) are filled with random uppercase letters [A-Z] to mask the actual content.
5) the encrypted message is produced by concatenating all characters column by column from left to right and top to bottom within each column.


- There should be support for multi-round encryption.
- To indicate end of original plain message, a fullstop should be appended if not already there. This should only be done in the first round.


# Week 1 - Basic C++ Coding
The whole assignment is written in C++.

# Week 2 - STL (Container, Iterator, Vector, Set)

# Week 3 - STL (Container - Map Class, Algorithms (min/max, sort, search, copying/moving, swap, shuffle, set, merge, generate, etc..))

# Week 4 - Classes (Intro, Defining a Class Instance, Constructors & Destructors, this Pointer, Operator Overloading, Class Templates)

# Week 5 - Classes & OOP Design 1 (Static Members & Friend Functions), Copying Objects (Copy Constructer/Assignment, Lvalue & Rvalue, Move Constructor/Assignment), UML, Class Aggregation

# Week 6 - OOP Design 2 (Inheritance, Polymorphism, Abstract Base Class)

# Week 7 - Exceptions & Lambda Functions
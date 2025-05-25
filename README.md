# Encrpytion/Decryption Application

## Compilation Instructions
```g++ -std=c++14 -Iinclude src/Menu.cpp src/Decoder.cpp src/Encoder.cpp src/MessageHandler.cpp main.cpp -o encryption-decryption```

## Encoder
- Inserts a message into a square grid and encrypts it using a diamond traversal pattern.
- Grid size can be manually or automatically defined. 
- The encrypted message is produced by concatenating all characters column by column from left to right and top to bottom within each column.
- Encoder can automatically append a full stop at the end of the message if it is not already present, but only in the first round of encryption. The fullstop is used to locate the end of a message if it does not end perfectly in the centre of the grid.
- It can also handle multi-round encryption by feeding the output of one encryption round into the input, and adjusting the grid size based on the length of the new message.
## Decoder
- Given an encrypted message, the Decoder reconstructs the original message by reversing the diamond traversal pattern used in the Encoder. 
- It fills a square grid with characters from the encrypted message and then reads them in a specific order to produce the original message.
- If multiround encryption was used, the Decoder adjusts the grid size to be the square root of the length of the encrypted message after each round.
    - If it is not the final encryption round and the resulting encrypted message is not a perfect square of an odd number, Decoder will remove characters from the end of the message until it is. 
## Menu
- The menu class provides a user interface for interacting with the Encoder and Decoder.
- It is implemented as a finite state machine (FSM).
- It allows users to choose between encoding and decoding messages, set grid sizes, and view the results of their operations.

## UML Diagram
![UML Diagram](uml-diagram.png)

# OOP/C++ Concepts Used
## Basic C++ Coding
- Vectors are used for the grid and for storing state transitions
- auto is used in multiple places for simplifying syntax,
- setGrid() and constructors are overloaded in the MessageHandler class family,
- range based for-loops are used to iterate over strings,
- initializer lists are used in some constructors,
- reference variables are used to take in the unencrypted message and encrypted message strings.
## STL (Container, Iterator, Vector, Set)
- Vectors are used for the grid,
- iterators are used to count the number of full-stops in a message.
## STL (Container - Map Class, Algorithms (min/max, sort, search, copying/moving, swap, shuffle, set, merge, generate, etc..))
- std::count is used for counting number of fullstops in a message,
- std::find is used to find if there is a fullstop in a message,
- std::generate is used to fill the grid with random chars,
- std::remove_if is used to remove whitespace from strings.
## Classes (Intro, Defining a Class Instance, Constructors & Destructors, this Pointer, Operator Overloading, Class Templates)
- Each class has members with appropriate access specifiers, 
- const is used for getters/accessors, 
- mutators/setters are used, 
- specification is separated from implementation via header files & .cpp files, 
- some inline member functions are defined in class declarations for simple class members, 
- some member functions are overloaded (setGrid(), constructors), 
- some members are initialized in place, 
- default constructors are defined for each class, 
- constructors in MessageHandler family are overloaded, 
- constructor delegation is used in the MessageHandler family, 
- initializer lists are used in some constructors, 
- this pointer is used for accessing the transitions.
## Classes & OOP Design 1 (Static Members & Friend Functions), Copying Objects (Copy Constructer/Assignment, Lvalue & Rvalue, Move Constructor/Assignment), UML, Class Aggregation
- Helper functions that don’t modify or access any non-static member variables are declared as static,
- UML diagram outlines OOP architecture.
## OOP Design 2 (Inheritance, Polymorphism, Abstract Base Class)
- MessageHandler is the base class from which Encoder and Decoder are derived (inheritance), 
- MessageHandler uses protected & public access whereas Encoder and Decoder utilise private & public because Encoder & Decoder are final classes, meaning they cannot be further derived from and thus have no use for protected members. 
- constructor & function overloading and overriding virtual functions are examples of polymorphism, 
- MessageHandler is an abstract base class with pure virtual functions that are overridden by Encoder and Decoder. 
## Exceptions & Lambda Functions
- Many exceptions are thrown for invalid circumstances, mostly invalid_argument, with custom messages.  
- Try/catch blocks are used in the Menu class to catch exceptions thrown by the Encoder and Decoder classes,
- an anonymous function is used when filling the grid using std::generate.

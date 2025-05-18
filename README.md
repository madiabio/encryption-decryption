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


# Status

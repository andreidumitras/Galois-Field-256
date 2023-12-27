# Galois-Field-256
 - (c) November 2023
 - Year 2, SICS

# Description
Galois Field 256 is a project made in the 1st semester of the 2nd year of SICS (Security of Information and Computing Systems) Master Degree. The project performs a cryptographic operation between 2 bytes to generate a new obfuscated byte.
First it does a multiplication of the two bytes, obtaining a word. Then the word is divided by a given word divider (100011011 in this case). The division is performed like the polynomial division, obtaining a reminder which is the resulted obfuscated byte.

The project was written in C++ as a console application with teaching purposes. It performs step-by-step all the operations involved in the Galois Field 256.

# Usage:
To build the project use make, which will build with g++, the executable galoisField.exe.
```bash
PS> make
g++ -I./headers/ -o galoisField.exe src/bits.cpp src/box.cpp src/gf256.cpp src/matrix.cpp src/screen.cpp src/main.cpp
```

To run the program, use the command line again. It must receives 2 bytes as command line arguments:
```bash
.\galoisField.exe 11001010 01010011
```

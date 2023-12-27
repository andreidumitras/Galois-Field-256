NAME = galoisField.exe

SRC = src/bits.cpp \
	src/box.cpp \
	src/gf256.cpp \
	src/matrix.cpp \
	src/screen.cpp \
	src/main.cpp

all:
	g++ -I./headers/ -o $(NAME) $(SRC)

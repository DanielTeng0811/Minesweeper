# Grid.o: Grid.cpp
# 	g++ -c Grid.cpp
# Minesweeper.o: Minesweeper.cpp
# 	g++ -c Minesweeper.cpp
# main.o: main.cpp
# 	g++ -c main.cpp
# main: main.o Grid.o Minesweeper.o
# 	g++ -o main main.o Grid.o Minesweeper.o
# clean:
# # remove .o files in VSC
# 	del --file main.o
# 	del --file Grid.o
# 	del --file Minesweeper.o
# cla:
# # clean all in VSC
# 	del --file main.o
# 	del --file Grid.o
# 	del --file Minesweeper.o
# 	del --file main.exe
# clear:
# # remove .o files in Mobaxterm
# 	rm -f main.o
# 	rm -f Grid.o
# 	rm -f Minesweeper.o
# clr:
# # clean all in Mobaxterm
# 	rm -f main.o
# 	rm -f Grid.o
# 	rm -f Minesweeper.o
# 	rm -f main.exe

# Compiler and flags
CXX = g++
CXXFLAGS = -c

# Source files
SRCS = Grid.cpp Minesweeper.cpp main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable target
TARGET = main

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean .o files in VS Code
clean-vsc:
	del /f main.o Grid.o Minesweeper.o 2>nul || echo No .o files to delete.

# Clean all in VS Code
cla-vsc: clean-vsc
	del /f ex4.exe 2>nul || echo No ex4.exe to delete.

# General clean
clean: clean-vsc

.PHONY: clean-vsc cla-vsc clean

### Linux
# Nome do executável
EXECUTABLE = main

# Diretórios
BUILD_DIR = build
INCLUDE_DIR = include

# Arquivos fonte
SOURCES = $(wildcard *.cpp)

# Arquivos objeto
OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -I$(INCLUDE_DIR) -std=c++11

# Bibliotecas SFML
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Regra padrão
all: $(BUILD_DIR) $(EXECUTABLE)

# Regra para criar o diretório de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regra para compilar o executável
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LIBS)

# Regra para compilar os arquivos objeto
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para rodar o programa
run: $(EXECUTABLE)
	 ./$(EXECUTABLE)

# Regra para limpar os arquivos gerados
clean: rm -rf $(BUILD_DIR) $(EXECUTABLE)

# Regra de limpeza completa
distclean: clean

.PHONY: all clean distclean run




# ## WINDOWS
# # Compiler
# CXX = g++

# # Directories
# INCDIR = C:/SFML-2.6.1/include
# LIBDIR = C:/SFML-2.6.1/lib

# # Libraries
# LIBS = -lsfml-graphics -lsfml-system -lsfml-window

# # Compiler flags
# CXXFLAGS = -I$(INCDIR)
# LDFLAGS = -L$(LIBDIR)

# # Source and object files
# SRCS = $(wildcard *.cpp)
# OBJS = $(SRCS:.cpp=.o)

# # Executable
# EXEC = main.exe

# # Default target
# all: compile link run

# # Compilation
# compile: $(OBJS)

# # Linking
# link: $(EXEC)

# # Run
# run:
# 	./$(EXEC)

# # Linking command
# $(EXEC): $(OBJS)
# 	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LIBS)

# # Compilation command
# %.o: %.cpp
# 	$(CXX) -c $< -o $@ $(CXXFLAGS)

# # Clean up
# clean:
# 	rm -f $(OBJS) $(EXEC)

# # Phony targets
# .PHONY: all compile link run clean
# ###





### OLD WINDOWS
# all: compile link run

# compile:
# 	g++ -c main.cpp Game.cpp -IC:/SFML-2.6.1/include

# link:
# 	g++ main.o Game.o -o main.exe -LC:/SFML-2.6.1/lib -lsfml-graphics -lsfml-system -lsfml-window

# run:
# 	./main.exe
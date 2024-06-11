### Linux
# Nome do executável
# EXECUTABLE = main

# # Diretórios
# BUILD_DIR = build
# SRC_DIR = src/sources
# INCLUDE_DIR = src/headers

# # Arquivos fonte
# SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# # Arquivos objeto
# OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# # Compilador e flags
# CXX = g++
# CXXFLAGS = -Wall -Wextra -I$(INCLUDE_DIR) -std=c++11

# # Bibliotecas SFML
# LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# # Regra padrão
# all: $(BUILD_DIR) $(EXECUTABLE)

# # Regra para criar o diretório de build
# $(BUILD_DIR):
# 	mkdir -p $(BUILD_DIR)

# # Regra para compilar o executável
# $(EXECUTABLE): $(OBJECTS)
# 	$(CXX) $(OBJECTS) -o $@ $(LIBS)

# # Regra para compilar os arquivos objeto
# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Regra para rodar o programa
# run: $(EXECUTABLE)
# 	 ./$(EXECUTABLE)

# # Regra para limpar os arquivos gerados
# clean:
# 	rm -rf $(BUILD_DIR) $(EXECUTABLE)

# # Regra de limpeza completa
# distclean: clean

# .PHONY: all clean distclean run
########






# ## WINDOWS
# # Compiler
CXX = g++

# Directories
INCDIR = C:/SFML-2.6.1/include
LIBDIR = C:/SFML-2.6.1/lib
SRCDIR = src/sources
BUILDDIR = build

# Libraries
LIBS = -lsfml-graphics -lsfml-system -lsfml-window

# Compiler flags
CXXFLAGS = -I$(INCDIR)
LDFLAGS = -L$(LIBDIR)

# Source and object files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# Executable
EXEC = $(BUILDDIR)/main.exe

# Default target
all: $(EXEC) run

# Create build directory if it doesn't exist
$(BUILDDIR):
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)

# Compilation
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Linking
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LIBS)

# Run
run: $(EXEC)
	$(EXEC)

# Clean up
clean:
	if exist $(BUILDDIR) (rmdir /S /Q $(BUILDDIR))

# Phony targets
.PHONY: all compile link run clean
###





### OLD WINDOWS
# all: compile link run

# compile:
# 	g++ -c main.cpp Game.cpp -IC:/SFML-2.6.1/include

# link:
# 	g++ main.o Game.o -o main.exe -LC:/SFML-2.6.1/lib -lsfml-graphics -lsfml-system -lsfml-window

# run:
# 	./main.exe
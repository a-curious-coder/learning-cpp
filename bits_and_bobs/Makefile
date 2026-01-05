# --- Makefile for Dear ImGui + GLFW/OpenGL on Arch Linux ---

# Compiler and Flags

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS =

# Include Paths: Point to the ImGui core and backends folders

INC_PATHS = -I. -Iimgui -Iimgui/backends

# Source Files

# 1. Main Application Source

APP_SRC = main.cpp

# 2. Dear ImGui Core Sources

IMGUI_CORE_SRC = imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_tables.cpp

# 3. Dear ImGui Backend Sources (for GLFW and OpenGL3)

IMGUI_BACKEND_SRC = imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp

# All Sources

SRCS = $(APP_SRC) $(IMGUI_CORE_SRC) $(IMGUI_BACKEND_SRC)

# Output Executable Name

TARGET = roller_derby_sim

# Libraries (Using pkg-config to find GLFW and OpenGL)

# Linking flags for GLFW and OpenGL/GLEW on Arch/Linux

LIBS = $(shell pkg-config --libs glfw3) -lGL -lGLEW -lm

# --- Build Rules ---

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INC_PATHS) $^ -o $@ $(LIBS)

clean:
	rm -f $(TARGET)


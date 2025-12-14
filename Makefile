# Makefile for Hostel Outing & Leave Management System

CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = hostel_management
SOURCE = main.cpp

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)
	@echo "Build successful! Run ./$(TARGET) to start the program."

# Clean build artifacts
clean:
	rm -f $(TARGET) $(TARGET).exe
	@echo "Clean complete."

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

